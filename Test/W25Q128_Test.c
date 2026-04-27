#include "W25Q128.h"
#include "W25Q128_Test.h"
#include "Usart.h"
#include "Delay.h"
#include "Key.h"
#include "oled.h"
#include "flash_use.h"
#include <stdio.h>
void W25Q128_Test1(void)
{
    Uart0_Printf("W25Q128 ID: %X\r\n", W25Q128_readID());
    Delay_ms(10);
}

void W25Q128_Test2(void)
{
    uint8_t  Key_Num = 0;
    uint8_t count = 0;
    W25Q128_read(&count, 0, 1);
    char buffer[20];
    sprintf(buffer, "Count: %d", count);
    OLED_Clear();
    OLED_ShowString(48, 0, buffer, 16, 1);
    OLED_Refresh();
    while(1)
    {
        Key_Num = Key_Num_Get();
        if(Key_Num == 1)
        {
            count ++;
            W25Q128_write(&count, 0, 1);
            sprintf(buffer, "Count: %d", count);
            OLED_Clear();
            OLED_ShowString(48, 0, buffer, 16, 1);
            OLED_Refresh();
        }
        else if(Key_Num == 2)
        {
            count --;
            W25Q128_write(&count, 0, 1);
            sprintf(buffer, "Count: %d", count);
            OLED_Clear();
            OLED_ShowString(48, 0, buffer, 16, 1);  
            OLED_Refresh();
        }
    }
}

void W25Q128_Test3(void)
{
    float x = -170.0f;
    float y = 170.0f;
    uint8_t  Key_Num = 0;
    Read_Gimbal_XY(&x,&y);
    char buffer[20];
    sprintf(buffer, "X: %.2f", x);
    OLED_Clear();
    OLED_ShowString(0, 0, buffer, 16, 1);
    sprintf(buffer, "Y: %.2f", y);
    OLED_ShowString(0, 16, buffer, 16, 1);
    OLED_Refresh();
    while(1)
    {
        Key_Num = Key_Num_Get();
        if(Key_Num == 1)
        {
            x += 10.0f;
            if(x > 180.0f) x = 180.0f;
            Write_Gimbal_XY(x, y);
            sprintf(buffer, "X: %.2f", x);
            OLED_Clear();
            OLED_ShowString(0, 0, buffer, 16, 1);
            sprintf(buffer, "Y: %.2f", y);
            OLED_ShowString(0, 16, buffer, 16, 1);  
            OLED_Refresh();
        }
        else if(Key_Num == 2)
        {
            y -= 10.0f;
            if(y < -180.0f) y = -180.0f;
            Write_Gimbal_XY(x, y);
            sprintf(buffer, "X: %.2f", x);
            OLED_Clear();
            OLED_ShowString(0, 0, buffer, 16, 1);
            sprintf(buffer, "Y: %.2f", y);
            OLED_ShowString(0, 16, buffer, 16, 1);  
            OLED_Refresh();
        }
        
    }
}