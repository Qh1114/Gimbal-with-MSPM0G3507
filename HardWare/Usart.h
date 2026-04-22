#ifndef __USART_H__
#define __USART_H__

typedef enum
{
    IDLE,
    BUSY, 
    CALIB,
    READY
}Rx_State;

void Uart_Init(void);
void Uart0_Send_Char(char ch);
void Uart0_Send_String(char* str);
void Uart_K230_Send_Char(char ch);
void Uart_K230_Send_String(char* str);
void Uart0_Printf(const char* format, ...);
void Uart_K230_Printf(const char* format, ...);
uint8_t Uart0_ReadCommand(float* command);
uint8_t Uart_K230_ReadCommand(float* command);

#endif
