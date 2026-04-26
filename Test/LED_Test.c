#include "LED.h"
#include "LED_Test.h"
#include "Delay.h"

void LED_Test1(void)
{
    LED_Init();
    while (1) {
        LED_On_Time(1000);
        Delay_ms(2000);
    }
}