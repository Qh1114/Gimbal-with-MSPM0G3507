#include "ti_msp_dl_config.h"
#include "Step_Motor.h"
#include "PWM.h"
#include "Delay.h"
#include <ti/iqmath/include/IQmathLib.h>
#include "InputCapture.h"

#define StepCount 200                       //一圈所需步速
#define MicroDivision 32                    //细分数
#define AllStepCount 6400.0f                //总步数 StepCount * 6400
#define Max_Pulse_up 20174                  //最大脉冲
#define Min_Pulse_up 36                     //最小脉冲
#define Angle_Pulse_up 20138.0f             //角度部分的脉冲长度， 计算公式为 Max_Pulse - Min_Pulse
#define Max_Pulse_down 20536                  //最大脉冲
#define Min_Pulse_down 36                     //最小脉冲
#define Angle_Pulse_down 20500.0f             //角度部分的脉冲长度， 计算公式为 Max_Pulse - Min_Pulse

volatile float angle_down, angle_up ,angle_down_1, angle_up_1 = 0.0f;
volatile static _iq14 q_Min_Pulse_up =_IQ14(Min_Pulse_up), q_Angle_Pulse_up =_IQ14(Angle_Pulse_up), q_Min_Pulse_down =_IQ14(Min_Pulse_down), q_Angle_Pulse_down =_IQ14(Angle_Pulse_down);
volatile static _iq14 q_360 = _IQ14(360), q_Now_Pulse_up = 0 , q_Angle_up = 0, q_Now_Pulse_down = 0 , q_Angle_down = 0;
volatile static float a = 0.2;
volatile static uint8_t up_state = 0 , down_state = 0;

static float WrapAngle180(float angle)
{
    while(angle >= 180.0f) angle -= 360.0f;
    while(angle < -180.0f) angle += 360.0f;
    return angle;
}

// Filter in circular-angle space to avoid false jumps near +/-180 deg.
static float CircularLpf(float prev, float now, float alpha)
{
    float delta = now - prev;
    while(delta >= 180.0f) delta -= 360.0f;
    while(delta < -180.0f) delta += 360.0f;
    return WrapAngle180(prev + alpha * delta);
}
//开始并未开启转动，应再开始之后紧接设置速度
void StepMotor_Up_Start(void)
{
    EN_UP(DISABLE);
    PWM_Up_Start();
    up_state = 0;
}

void StepMotor_Down_Start(void)
{
    EN_DOWN(DISABLE);
    PWM_Under_Start();
    down_state = 0;
}

//停止运行
void StepMotor_Up_Stop(void)
{
    EN_UP(DISABLE);
    PWM_Up_Stop();
}

void StepMotor_Down_Stop(void)
{
    EN_DOWN(DISABLE);
    PWM_Under_Stop();
}

//单位为度每秒
void StepMotor_Up_Set_Speed(float Speed)
{
    if(Speed >= 0)
    {
        DIR_UP(CLOCK_WISE);
    }else {
        DIR_UP(COUNTCLOCK_WISE);
        Speed *= -1.0f;
    }
    float Freq = Speed / 360.0f *AllStepCount;
    PWM_Up_Set_Frequency(Freq);
    EN_UP(ENABLE);
}

//单位为度每秒
void StepMotor_Down_Set_Speed(float Speed)
{
    if(Speed >= 0)
    {
        DIR_DOWN(CLOCK_WISE);
    }else {
        DIR_DOWN(COUNTCLOCK_WISE);
        Speed *= -1.0f;
    }
    float Freq = Speed / 360.0f *AllStepCount;
    PWM_Under_Set_Frequency(Freq);
    EN_DOWN(ENABLE);
}

//获取上电机的角度值，归一化为-180到180度
float StepMotor_Angle_Up_Get(void)
{
    return angle_up;
}

float StepMotor_Angle_Down_Get(void)
{
    return angle_down;
}

float StepMotor_Angle_Up_Get_1(void)
{
    return angle_up_1;
}

float StepMotor_Angle_Down_Get_1(void)
{
    return angle_down_1;
}

void StepMotor_Angle_Proc(void)
{
    q_Now_Pulse_up = _IQ14(Get_PWM_Pulse_Width_Up()) - q_Min_Pulse_up;               //现在角度脉冲长度
    q_Angle_up = _IQ14mpy(q_360, _IQ14div(q_Now_Pulse_up, q_Angle_Pulse_up));         //计算出实际角度
    float angle = WrapAngle180(_IQ14toF(q_Angle_up));
    if(!up_state)
    {
        up_state = 1;
        angle_up = angle;
    }
    else{
        angle_up = CircularLpf(angle_up, angle, a);
    }
    angle_up = WrapAngle180(angle_up);
    angle_up_1 = angle_up;

    q_Now_Pulse_down = _IQ14(Get_PWM_Pulse_Width_Down()) - q_Min_Pulse_down;               //现在角度脉冲长度
    q_Angle_down = _IQ14mpy(q_360, _IQ14div(q_Now_Pulse_down, q_Angle_Pulse_down));           //计算出实际角度
    angle = WrapAngle180(_IQ14toF(q_Angle_down));
    if(!down_state)
    {
        down_state = 1;
        angle_down = angle;
    }
    else{
        angle_down = CircularLpf(angle_down, angle, a);
    }    
    angle_down = WrapAngle180(angle_down);
    angle_down_1 = angle_down;
}