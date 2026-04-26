#include "LED.h"
    
static LED led;

void LED_Init(void) {
    led.state = 0;
    led.tick = 0;
}


void LED_On_Time(uint32_t time)
{
    led.state = 1;
    led.tick = time / tick_interval;
    DL_GPIO_clearPins(LED_LED1_PORT, LED_LED1_PIN);
    DL_GPIO_clearPins(LED_LED2_PORT, LED_LED2_PIN);
    DL_GPIO_clearPins(LED_LED3_PORT, LED_LED3_PIN);
}
void LED_Tick(void) {
    if(!led.state) return; 
    led.tick--;
    if (led.tick == 0) {
        led.tick = 0;
        led.state = 0;
        DL_GPIO_setPins(LED_LED1_PORT, LED_LED1_PIN);
        DL_GPIO_setPins(LED_LED2_PORT, LED_LED2_PIN);
        DL_GPIO_setPins(LED_LED3_PORT, LED_LED3_PIN);
    }
}
