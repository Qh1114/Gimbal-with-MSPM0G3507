#include "Key_Test.h"
#include "Key.h"
#include "Usart.h"

void Key_Test1(void)
{
    Key_Init();
    Uart_Init();
    while (1) {
        uint8_t key_num = Key_Num_Get();
        if (key_num) {
            Uart0_Printf("Key %d pressed\n", key_num);
        }
    }
}