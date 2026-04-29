#include "ti_msp_dl_config.h"
#include "Usart.h"
#include "Step_Motor.h"
#include "Delay.h"
#include "string.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
// #define BufferSize 256          //缓冲区大小
// #define CommandMiniSize 4       //最小命令长度
// #define CommandStartByte 0xAA   //命令起始字节
// #define CommandEndByte 0x55     //命令结束字节

// uint8_t ReadIndex = 0;
// uint8_t WriteIndex = 0;
// uint8_t Buffer[BufferSize];
// uint8_t Receive[10];

#define MAX_PARAMS              5U
#define UART_RX_RING_SIZE       256U
#define UART_TX_TIMEOUT_MS      10U
#define UART_FRAME_TIMEOUT_MS   100U
#define UART0_RX_STALL_MS       200U
#define UART0_RECOVER_GAP_MS    50U
#define UART2_RX_STALL_MS       200U
#define UART2_RECOVER_GAP_MS    50U

typedef struct
{
    volatile uint8_t data[UART_RX_RING_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
    volatile uint32_t overflow_cnt;
} UartRxRing;

typedef struct
{
    uint8_t state;
    float buffer[MAX_PARAMS];
    uint8_t data_num;
    int8_t sign;
    uint8_t frac_digits;
    int32_t calib;
    uint8_t calib_count;
    uint32_t last_tick;
} UartParser;

volatile static uint8_t uart0_data = 0;
volatile static uint8_t uart2_data = 0;
static UartRxRing uart0_rx = {0};
static UartRxRing uart2_rx = {0};
static UartParser uart0_parser = {0};
static UartParser uart2_parser = {0};
static uint32_t uart0_last_rx_ms = 0;
static uint32_t uart0_last_recover_ms = 0;
static uint32_t uart2_last_rx_ms = 0;
static uint32_t uart2_last_recover_ms = 0;

static uint16_t UartRxRing_Next(uint16_t idx)
{
    return (uint16_t)((idx + 1U) & (UART_RX_RING_SIZE - 1U));
}

static void UartRxRing_Reset(UartRxRing *ring)
{
    ring->head = 0;
    ring->tail = 0;
    ring->overflow_cnt = 0;
}

static uint8_t UartRxRing_Push(UartRxRing *ring, uint8_t ch)
{
    uint16_t next = UartRxRing_Next(ring->head);
    if(next == ring->tail)
    {
        ring->overflow_cnt++;
        return 0;
    }

    ring->data[ring->head] = ch;
    ring->head = next;
    return 1;
}

static uint8_t UartRxRing_Pop(UartRxRing *ring, uint8_t *ch)
{
    if(ring->head == ring->tail)
    {
        return 0;
    }

    *ch = ring->data[ring->tail];
    ring->tail = UartRxRing_Next(ring->tail);
    return 1;
}

static void UartParser_Reset(UartParser *parser, uint32_t now)
{
    parser->state = IDLE;
    parser->data_num = 0;
    parser->sign = 1;
    parser->frac_digits = 0;
    parser->calib = 0;
    parser->calib_count = 0;
    parser->last_tick = now;
    for(uint8_t i = 0; i < MAX_PARAMS; i++)
    {
        parser->buffer[i] = 0.0f;
    }
}

static void UartParser_StartFrame(UartParser *parser, uint32_t now)
{
    UartParser_Reset(parser, now);
    parser->state = BUSY;
}

static void UartParser_FinishParam(UartParser *parser)
{
    parser->buffer[parser->data_num] *= (float)parser->sign;
    parser->sign = 1;
    parser->frac_digits = 0;
}

static void UartParser_CheckTimeout(UartParser *parser, uint32_t now)
{
    if(parser->state == IDLE)
    {
        return;
    }

    if((uint32_t)(now - parser->last_tick) > UART_FRAME_TIMEOUT_MS)
    {
        UartParser_Reset(parser, now);
    }
}

static void UartParser_ProcessByte(UartParser *parser, uint8_t ch, uint32_t now)
{
    parser->last_tick = now;

    if(ch == '$')
    {
        UartParser_StartFrame(parser, now);
        return;
    }

    if(parser->state == IDLE || parser->state == READY)
    {
        return;
    }

    if(parser->state == BUSY)
    {
        if(ch == ',')
        {
            UartParser_FinishParam(parser);
            parser->data_num++;
            if(parser->data_num >= MAX_PARAMS)
            {
                parser->data_num = MAX_PARAMS - 1U;
            }
        }
        else if(ch == '#')
        {
            UartParser_FinishParam(parser);
            parser->calib = 0;
            parser->calib_count = 0;
            parser->state = CALIB;
        }
        else if(ch == '+')
        {
            parser->sign = 1;
        }
        else if(ch == '-')
        {
            parser->sign = -1;
        }
        else if(ch == '.')
        {
            parser->frac_digits = 1;
        }
        else if(ch >= '0' && ch <= '9')
        {
            if(parser->frac_digits == 0)
            {
                parser->buffer[parser->data_num] = parser->buffer[parser->data_num] * 10.0f + (float)(ch - '0');
            }
            else if(parser->frac_digits == 1)
            {
                parser->buffer[parser->data_num] += (float)(ch - '0') * 0.1f;
                parser->frac_digits = 2;
            }
            else if(parser->frac_digits == 2)
            {
                parser->buffer[parser->data_num] += (float)(ch - '0') * 0.01f;
                parser->frac_digits = 3;
            }
        }
        else
        {
            UartParser_Reset(parser, now);
        }
        return;
    }

    if(parser->state == CALIB)
    {
        if(ch >= '0' && ch <= '9')
        {
            if(parser->calib_count < 3U)
            {
                parser->calib = parser->calib * 10 + (ch - '0');
                parser->calib_count++;
            }
            else
            {
                UartParser_Reset(parser, now);
            }
        }
        else if((ch == '\r' || ch == '\n') && parser->calib_count > 0U)
        {
            parser->state = READY;
        }
        else if(ch == '$')
        {
            UartParser_StartFrame(parser, now);
        }
        else
        {
            UartParser_Reset(parser, now);
        }

        if(parser->calib_count == 3U)
        {
            parser->state = READY;
        }
    }
}

static void Uart_ProcessRx(UartRxRing *ring, UartParser *parser)
{
    uint8_t ch = 0;
    uint32_t now = Get_ms();

    UartParser_CheckTimeout(parser, now);
    while(UartRxRing_Pop(ring, &ch))
    {
        now = Get_ms();
        UartParser_ProcessByte(parser, ch, now);
    }
    UartParser_CheckTimeout(parser, Get_ms());
}

static void Uart0_RecoverIfStalled(void)
{
    uint32_t now = Get_ms();

    if((uint32_t)(now - uart0_last_rx_ms) <= UART0_RX_STALL_MS)
    {
        return;
    }

    if((uint32_t)(now - uart0_last_recover_ms) < UART0_RECOVER_GAP_MS)
    {
        return;
    }

    UartRxRing_Reset(&uart0_rx);
    UartParser_Reset(&uart0_parser, now);

    NVIC_DisableIRQ(UART_0_INST_INT_IRQN);
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    /* TI workaround: clear pending then read once to flush stale data/flags. */
    (void)DL_UART_Main_receiveData(UART_0_INST);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    uart0_last_recover_ms = now;
}

static void Uart2_RecoverIfStalled(void)
{
    uint32_t now = Get_ms();

    if((uint32_t)(now - uart2_last_rx_ms) <= UART2_RX_STALL_MS)
    {
        return;
    }

    if((uint32_t)(now - uart2_last_recover_ms) < UART2_RECOVER_GAP_MS)
    {
        return;
    }

    UartRxRing_Reset(&uart2_rx);
    UartParser_Reset(&uart2_parser, now);

    NVIC_DisableIRQ(UART_K230_INST_INT_IRQN);
    NVIC_ClearPendingIRQ(UART_K230_INST_INT_IRQN);
    /* TI workaround: clear pending then read once to flush stale data/flags. */
    (void)DL_UART_Main_receiveData(UART_K230_INST);
    NVIC_EnableIRQ(UART_K230_INST_INT_IRQN);

    uart2_last_recover_ms = now;
}

void Uart_Init(void)
{
    uint32_t now = Get_ms();
    UartRxRing_Reset(&uart0_rx);
    UartRxRing_Reset(&uart2_rx);
    UartParser_Reset(&uart0_parser, now);
    UartParser_Reset(&uart2_parser, now);
    uart0_last_rx_ms = now;
    uart0_last_recover_ms = now;
    uart2_last_rx_ms = now;
    uart2_last_recover_ms = now;

    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    (void)DL_UART_Main_receiveData(UART_0_INST);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    NVIC_ClearPendingIRQ(UART_K230_INST_INT_IRQN);
    (void)DL_UART_Main_receiveData(UART_K230_INST);
    NVIC_EnableIRQ(UART_K230_INST_INT_IRQN);
}

//串口发送单个字符
void Uart0_Send_Char(char ch)
{
    uint32_t start = Get_ms();

    while(DL_UART_isBusy(UART_0_INST) == true)
    {
        if((Get_ms() - start) > UART_TX_TIMEOUT_MS)
        {
            return;
        }
    }
    DL_UART_Main_transmitData(UART_0_INST, ch);
}

//串口发送字符串
void Uart0_Send_String(char* str)
{
    while(str!=0 && *str!=0)
    {
        Uart0_Send_Char(*str++);
    }
}

void Uart_K230_Send_Char(char ch)
{
    uint32_t start = Get_ms();

    while(DL_UART_isBusy(UART_K230_INST) == true)
    {
        if((Get_ms() - start) > UART_TX_TIMEOUT_MS)
        {
            return;
        }
    }
    DL_UART_Main_transmitData(UART_K230_INST, ch);
}

void Uart_K230_Send_String(char* str)
{
    while(str != 0 && *str != 0)
    {
        Uart_K230_Send_Char(*str++);
    }
}

//串口打印
void Uart0_Printf(const char* format, ...)
{
    char tmp[128];  
    va_list argptr;

    va_start(argptr, format);
    vsnprintf(tmp, sizeof(tmp) - 1, format, argptr);
    va_end(argptr);

    Uart0_Send_String(tmp);
}
void Uart_K230_Printf(const char* format, ...)
{
    char tmp[128];  
    va_list argptr;

    va_start(argptr, format);
    vsnprintf(tmp, sizeof(tmp) - 1, format, argptr);
    va_end(argptr);

    Uart_K230_Send_String(tmp);
}


void UART_0_INST_IRQHandler(void)
{
    switch( DL_UART_getPendingInterrupt(UART_0_INST) )
    {
        case DL_UART_IIDX_RX:
            uart0_last_rx_ms = Get_ms();
            uart0_data = DL_UART_Main_receiveData(UART_0_INST);
            UartRxRing_Push(&uart0_rx, uart0_data);
            break;

        default:
            break;
    }
}

uint8_t Uart0_ReadCommand(float* command)
{
    Uart0_RecoverIfStalled();
    Uart_ProcessRx(&uart0_rx, &uart0_parser);
    if(uart0_parser.state != READY) return 0;

    // 1. 获取有效参数个数
    uint8_t count = uart0_parser.data_num + 1U;
    int32_t check_sum = 0;  // 用32位防止溢出

    // 2. 计算：所有参数 【带符号的整数部分】 直接相加
    for(uint8_t i = 0; i < count; i++)
    {
        // 直接取带符号整数（float强转int32_t自动保留正负）
        int32_t int_part = (int32_t)uart0_parser.buffer[i];
        check_sum += int_part;

        // 同时复制参数给上层
        command[i] = uart0_parser.buffer[i];
    }

    // 3. 负数处理：不断 +256 直到变为正数
    while(check_sum < 0)
    {
        check_sum += 256;
    }

    // 4. 最终必须对 256 取余
    uint8_t calc_check = check_sum % 256;

    // 5. 对比串口收到的校验值
    if(calc_check != (uint8_t)uart0_parser.calib)
    {
        // 校验失败
        UartParser_Reset(&uart0_parser, Get_ms());
        return 0;
    }
    // 校验成功
    UartParser_Reset(&uart0_parser, Get_ms());
    return count;
}


void UART_K230_INST_IRQHandler(void)
{
    switch(DL_UART_getPendingInterrupt(UART_K230_INST))
    {
        case DL_UART_IIDX_RX:
            uart2_last_rx_ms = Get_ms();
            uart2_data = DL_UART_Main_receiveData(UART_K230_INST);
            UartRxRing_Push(&uart2_rx, uart2_data);
            break;
        default:
            break;
    }
}

uint8_t Uart_K230_ReadCommand(float* command)
{
    Uart2_RecoverIfStalled();
    Uart_ProcessRx(&uart2_rx, &uart2_parser);
    if(uart2_parser.state != READY) return 0;

    uint8_t count = uart2_parser.data_num + 1U;
    int32_t check_sum = 0;

    for(uint8_t i = 0; i < count; i++)
    {
        int32_t int_part = (int32_t)uart2_parser.buffer[i];
        check_sum += int_part;
        command[i] = uart2_parser.buffer[i];
    }

    while(check_sum < 0)
    {
        check_sum += 256;
    }

    uint8_t calc_check = check_sum % 256;

    if(calc_check != (uint8_t)uart2_parser.calib)
    {
        UartParser_Reset(&uart2_parser, Get_ms());
        return 0;
    }

    UartParser_Reset(&uart2_parser, Get_ms());
    return count;
}

// void UART_K230_INST_IRQHandler(void)
// {
//     switch( DL_UART_getPendingInterrupt(UART_K230_INST) )
//     {
//         case DL_UART_IIDX_RX:
//             if(uart2_state == READY) return;
//             uart2_data = DL_UART_Main_receiveData(UART_K230_INST);

//             if(uart2_state == IDLE && uart2_data == '$')
//             {
//                 uart2_state = BUSY;
//                 uart2_data_num = 0;
//                 uart2_sign = 1;
//                 uart2_sign_count = 0;
//                 for(uint8_t i = 0; i < MAX_PARAMS; i++)
//                 {
//                     uart2_buffer[i] = 0.0f;
//                 }
//             }
//             else if(uart2_state == BUSY)
//             {
//                 if(uart2_data == ',')
//                 {
//                     uart2_buffer[uart2_data_num] *= uart2_sign;
//                     uart2_sign = 1;
//                     uart2_data_num++;
//                     if(uart2_data_num >= MAX_PARAMS) uart2_data_num = MAX_PARAMS-1;
//                 }
//                 else if(uart2_data == '#')
//                 {
//                     uart2_buffer[uart2_data_num] *= uart2_sign;
//                     uart2_state = READY;
//                 }
//                 else if(uart2_data == '+')
//                 {
//                     uart2_sign = 1;
//                 }
//                 else if(uart2_data == '-')
//                 {
//                     uart2_sign = -1;
//                 }
//                 else if(uart2_data == '.')
//                 {
//                     uart2_sign_count = 1;
//                 }
//                 else if(uart2_data >= '0' && uart2_data <= '9')
//                 {
//                     if(uart2_sign_count >= 1)
//                     {
//                         if(uart2_sign_count <= 4)
//                         {
//                             //uart2_buffer[uart2_data_num] = uart2_buffer[uart2_data_num]  + (uart2_data - '0') * uart_decimal_scale[uart2_sign_count];
//                             uart2_sign_count++;
//                         }
//                     }else {
//                         uart2_buffer[uart2_data_num] = uart2_buffer[uart2_data_num] * 10 + (uart2_data - '0');
//                     }
//                 }
//             }
//             break;

//         default:
//             break;
//     }
// }


// uint8_t Uart_K230_ReadCommand(float* command)
// {
//     if(uart2_state != READY) return 0;

//     // 正确的参数个数
//     uint8_t count = uart2_data_num + 1;

//     // 复制参数
//     for(uint8_t i = 0; i < count; i++)
//     {
//         command[i] = uart2_buffer[i];
//     }

//     // 重置状态
//     uart2_state = IDLE;
//     uart2_data_num = 0;

//     return count;
// }
// void UART_0_INST_IRQHandler(void)
// {
//      switch( DL_UART_getPendingInterrupt(UART_0_INST) )
//     {
//         case DL_UART_IIDX_RX:
//             uart_data = DL_UART_Main_receiveData(UART_0_INST);
//             if(uart0_state == BUSY)
//             {
//                 if(uart_data == ',')
//                 {
//                     uart_data_num++;
//                 }else if(uart_data >= '0' && uart_data <='9')
//                 {
//                     uart_buffer[uart_data_num] = uart_buffer[uart_data_num]*10 + uart_data -'0';
//                 }
//             }else if(uart0_state == IDLE && uart_data == '$')
//             {
//                 uart0_state = BUSY;
//             }else if(uart0_state == BUSY && uart_data == '#')
//             {
//                 uart0_state = READY;
//             }           
//             Uart0_Send_Char(uart_data);
//             break;
//         default:
//             break;
//     }
// }

// uint8_t Uart0_ReadCommand(int16_t* command)
// {
//     if(uart0_state != READY) return 0;

//     for(uint8_t i = 0; i < uart_data_num ; i ++)
//     {
//         command[i] = uart_buffer[i];
//     }

//     uint8_t temp = ++uart_data_num;
//     uart_data_num = 0;
//     uart0_state = IDLE;
//     return temp;
// }



//串口的中断服务函数
// void UART_0_INST_IRQHandler(void)
// {
//     switch( DL_UART_getPendingInterrupt(UART_0_INST) )
//     {
//         case DL_UART_IIDX_RX:
//             uart_data = DL_UART_Main_receiveData(UART_0_INST);
//             Uart0_Send_Char(uart_data);
//             break;
//         default:
//             break;
//     }
// }




// //
// //@简介：增加写索引
// //@参数：Length:增加的长度
// //
// static void AddReadIndex(uint8_t Length)
// {
//     ReadIndex += Length;
//     ReadIndex %= BufferSize;
// }

// static uint8_t Read(uint8_t i)
// {
//     uint8_t index = i % BufferSize;
//     return Buffer[index];
// }

// //
// //@简介：获取当前缓冲区数据长度
// //@返回值：数据长度，最大为BufferSize - 1
// //        
// static uint8_t GetLength(void)
// {
//     return (WriteIndex + BufferSize - ReadIndex) % BufferSize;
// }

// //
// //@简介：获取缓冲区剩余空间长度
// //@返回值：剩余空间长度，最小为0
// //
// static uint8_t GetRemain(void)
// {
//     return BufferSize - GetLength() - 1;
// }

// //
// //@简介：写入数据到缓冲区
// //@参数：data:要写入的数据
// //@参数：size:数据长度
// //@返回值：写入成功返回1，失败返回0
// //
// static uint8_t Write(uint8_t* data, uint16_t size)
// {
//     if(size >= GetRemain()){
//         return 0;
//     }
//     if(WriteIndex + size < BufferSize){
//         memcpy(&Buffer[WriteIndex], data, size);
//         WriteIndex += size;
//         WriteIndex %= BufferSize;
//     } else {
//         uint16_t firstPart = BufferSize - WriteIndex;
//         memcpy(&Buffer[WriteIndex], data, firstPart);
//         uint16_t secondPart = size - firstPart;
//         memcpy(Buffer, &data[firstPart], secondPart);
//         WriteIndex = secondPart;
//     }
//     return 1;
// }

// //
// //@简介：从缓冲区读取一个完整命令
// //@参数：command:存放读取命令的缓冲区
// //@返回值：命令长度，失败返回0
// //
// uint8_t Uart0_ReadCommand(uint8_t* command)
// {
//     while(1)
//     {
//         uint8_t dataLength = GetLength();
//         if(dataLength < CommandMiniSize){
//             return 0;
//         }

//         if(Buffer[ReadIndex] != CommandStartByte){
//             AddReadIndex(1);
//             continue;
//         }

//         dataLength = GetLength();
//         if(dataLength < CommandMiniSize){
//             return 0;
//         }

//         for(uint8_t i = 1; i < dataLength; i++){
//             if(Buffer[(ReadIndex + i) % BufferSize] == CommandEndByte){
//                 dataLength = i + 1;
//                 break;
//             }
//             if(i == dataLength - 1){
//                 return 0;
//             }
//         }

//         //含校验位代码
// /*
//         uint8_t Sum = 0;
//         for(uint8_t i = 0; i < dataLength; i++){
//             Sum += Read(ReadIndex + i);
//         }
//         if(Sum != Read(ReadIndex + dataLength - 1)){
//             AddReadIndex(1);
//             continue;
//         }
//         uint8_t cmdLength = Buffer[ReadIndex + 1];
//         if(dataLength < cmdLength){
//             AddReadIndex(1);
//             continue;
//         }
// */

//         for (uint8_t i = 0; i < dataLength; i++) {
//             command[i] = Read(ReadIndex + i);
//         }
//         AddReadIndex(dataLength);
//         return dataLength;
//     }
// }


// //
// //@简介：USART接收完成回调函数
// //@参数：huart:UART句柄
// //
// void UART_0_INST_IRQHandler(void)
// {
//     switch( DL_UART_getPendingInterrupt(UART_0_INST) )
//     {
//         case DL_UART_IIDX_RX:
//             uart_data = DL_UART_Main_receiveData(UART_0_INST);
//             Write((uint8_t *)&uart_data, 1);
//             break;
//         default:
//             break;
//     }
// }
