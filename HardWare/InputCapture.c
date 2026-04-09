#include "ti_msp_dl_config.h"
#include "InputCapture.h"

volatile uint32_t gCaptureCnt_up, gCaptureCnt_down;      //捕获到高电平时的计数值
volatile bool gSync_up, gSync_down;                //是否同步成功
volatile bool gCheckCaptures_up, gCheckCaptures_down;       //是否捕获成功
uint32_t gLoadValue_up, gLoadValue_down;                //初始计数值

void InputCapture_Init(void)
{
    gLoadValue_up = DL_TimerG_getLoadValue(CAPTURE_Up_INST);
    gSync_up        = false;
    gCheckCaptures_up = false;

    gLoadValue_down = DL_TimerG_getLoadValue(CAPTURE_Down_INST);
    gSync_down        = false;
    gCheckCaptures_down = false;

    DL_TimerG_setCoreHaltBehavior(CAPTURE_Up_INST, DL_TIMER_CORE_HALT_IMMEDIATE);
    DL_TimerG_setCoreHaltBehavior(CAPTURE_Down_INST, DL_TIMER_CORE_HALT_IMMEDIATE);
    NVIC_EnableIRQ(CAPTURE_Up_INST_INT_IRQN);
    NVIC_EnableIRQ(CAPTURE_Down_INST_INT_IRQN);
    DL_TimerG_startCounter(CAPTURE_Up_INST);
    DL_TimerG_startCounter(CAPTURE_Down_INST);
}

//获取周期值
//使用前应先判断是否非零
uint32_t Get_PWM_Period_Width_Up(void)
{
    if(gCheckCaptures_up == true)
    {
        gCheckCaptures_up = false;
        return (gLoadValue_up - gCaptureCnt_up);
    }
    else {
        return 0;
    }
}

//获取脉宽
uint32_t Get_PWM_Pulse_Width_Up(void)
{
    return (gLoadValue_up - DL_TimerG_getCaptureCompareValue(CAPTURE_Up_INST, DL_TIMER_CC_0_INDEX));
}

uint32_t Get_PWM_Period_Width_Down(void)
{
    if(gCheckCaptures_down == true)
    {
        gCheckCaptures_down = false;
        return (gLoadValue_down - gCaptureCnt_down);
    }
    else {
        return 0;
    }
}


uint32_t Get_PWM_Pulse_Width_Down(void)
{
    return (gLoadValue_down - DL_TimerG_getCaptureCompareValue(CAPTURE_Down_INST, DL_TIMER_CC_0_INDEX));
}

void CAPTURE_Up_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(CAPTURE_Up_INST)) {
        case DL_TIMERG_IIDX_CC1_DN:
            if (gSync_up == true) {
                gCaptureCnt_up = DL_TimerG_getCaptureCompareValue(CAPTURE_Up_INST, DL_TIMER_CC_1_INDEX);
                gCheckCaptures_up = true;
            } else {
                gSync_up = true;
            }
            DL_TimerG_setTimerCount(CAPTURE_Up_INST, gLoadValue_up);
            break;
        case DL_TIMERG_IIDX_ZERO:
            gSync_up = false;
            break;
        default:
            break;
    }
}

void CAPTURE_Down_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(CAPTURE_Down_INST)) {
        case DL_TIMERG_IIDX_CC1_DN:
            if (gSync_down == true) {
                gCaptureCnt_down = DL_TimerG_getCaptureCompareValue(CAPTURE_Down_INST, DL_TIMER_CC_1_INDEX);
                gCheckCaptures_down = true;
            } else {
                gSync_down = true;
            }
            DL_TimerG_setTimerCount(CAPTURE_Down_INST, gLoadValue_down);
            break;
        case DL_TIMERG_IIDX_ZERO:
            gSync_down = false;
            break;
        default:
            break;
    }    
}
