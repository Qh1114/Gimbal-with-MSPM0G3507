#include "ti_msp_dl_config.h"
#include "Delay.h"

uint32_t MS = (uint32_t)(CPUCLK_FREQ / 1000);
uint32_t US = (uint32_t)(CPUCLK_FREQ / 1000000);
volatile static uint32_t now_tick = 0;

void Delay_ms(uint32_t delay_time)
{
    while(delay_time --)
        delay_cycles(MS);
}

void Delay_us(uint32_t delay_time)
{
    while(delay_time --)
        delay_cycles(US);
}

//获取现在时间
uint32_t Get_ms(void)
{
    return now_tick;
}

//系统计时
void SysTick_Handler(void)
{
    now_tick++;
}