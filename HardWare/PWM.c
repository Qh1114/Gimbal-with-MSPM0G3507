#include "ti_msp_dl_config.h"
#include "PWM.h"

#define PWM_Clock_Freq PWM_Up_INST_CLK_FREQ
#define Min_Freq 1.0f
#define Max_Freq PWM_Up_INST_CLK_FREQ

#define Buzzer_Clock_Freq Buzzer_INST_CLK_FREQ
#define Buzzer_Max_Freq 5000.0f

void PWM_Under_Start(void)
{
    DL_TimerG_startCounter(PWM_Under_INST);
}

void PWM_Under_Stop(void)
{
    DL_TimerG_stopCounter(PWM_Under_INST);
}

void PWM_Under_Set_Frequency(float Frequncy)
{
    if(Frequncy > Max_Freq) Frequncy = Max_Freq;
    if(Frequncy < Min_Freq) Frequncy = Min_Freq;
    uint32_t load_value = (uint32_t)(PWM_Clock_Freq / Frequncy);
    DL_TimerG_setLoadValue(PWM_Under_INST, load_value);
    DL_TimerG_setCaptureCompareValue(PWM_Under_INST, load_value / 2, GPIO_PWM_Under_C1_IDX);
}

void PWM_Up_Start(void)
{
    DL_TimerG_startCounter(PWM_Up_INST);
}

void PWM_Up_Stop(void)
{
    DL_TimerG_stopCounter(PWM_Up_INST);
}

void PWM_Up_Set_Frequency(float Frequncy)
{
    if(Frequncy > Max_Freq) Frequncy = Max_Freq;
    if(Frequncy < Min_Freq) Frequncy = Min_Freq;
    uint32_t load_value = (uint32_t)(PWM_Clock_Freq / Frequncy);
    DL_TimerG_setLoadValue(PWM_Up_INST, load_value);
    DL_TimerG_setCaptureCompareValue(PWM_Up_INST, load_value / 2, GPIO_PWM_Up_C1_IDX);
}

void PWM_Buzzer_Start(void)
{
    DL_TimerG_startCounter(Buzzer_INST);
}

void PWM_Buzzer_Stop(void)
{
    DL_TimerG_stopCounter(Buzzer_INST);
}

void PWM_Buzzer_Set_Frequency(float Frequncy)
{
    if(Frequncy > Buzzer_Max_Freq) Frequncy = Buzzer_Max_Freq;
    uint32_t load_value = (uint32_t)(Buzzer_Clock_Freq / Frequncy);
    DL_TimerG_setLoadValue(Buzzer_INST, load_value);
    DL_TimerG_setCaptureCompareValue(Buzzer_INST, load_value / 2, GPIO_Buzzer_C0_IDX);
}