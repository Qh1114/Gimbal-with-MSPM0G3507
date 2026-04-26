#include "Buzzer.h"
#include "PWM.h"

static Buzzer buzzer;

void Buzzer_Init(void)
{
    buzzer.state = 0;
    buzzer.tick = 0;
    buzzer.frequency = 0.0f;
}

void Buzzer_On_Time(uint32_t time, float frequency)
{
    buzzer.state = 1;
    buzzer.tick = time / Buzzer_Interval_Time;
    buzzer.frequency = frequency;
    PWM_Buzzer_Set_Frequency(frequency);
    PWM_Buzzer_Start();
}

void Buzzer_Tick(void)
{
    if(!buzzer.state) return;
    buzzer.tick--;
    if(buzzer.tick == 0)
    {
        buzzer.state = 0;
        PWM_Buzzer_Stop();
    }
}