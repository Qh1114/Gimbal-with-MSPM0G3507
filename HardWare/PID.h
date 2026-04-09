#ifndef __PID_H__
#define __PID_H__

#include <ti/iqmath/include/IQmathLib.h>

typedef struct{
    _iq13 Kp;                   // 比例增益
    _iq13 Ki;                   // 积分增益
    _iq13 Kd;                   // 微分增益
    _iq13 SP;                   // 设定点
    _iq13 delta_time;           // 每次计算的时间差
    _iq13 last_error;           // 上次误差
    _iq13 last_integral;        // 上次积分值
    float Upper_Limit;          // 输出上限
    float Lower_Limit;          // 输出下限
    float Upper_IntergralLimit;  // 积分上限
    float Lower_IntergralLimit;  // 积分下限
    uint8_t first_calculate;    // 标记是否为第一次计算pid, 0为第一次，非0代表不是第一次
}PID_TypeDef;

void PID_Init(PID_TypeDef *pid, float kp, float ki, float kd, float delta_time);
void PID_ChangeSP(PID_TypeDef *pid, float sp);
void PID_SetOutputLimits(PID_TypeDef *pid, float upper_limit, float lower_limit, float upper_intergral, float lower_intergral);
void PID_Reset(PID_TypeDef *pid);
void PID_SetK(PID_TypeDef *pid, float kp, float ki, float kd);

float PID_Compute(PID_TypeDef *pid, float FB);
float PID_AngleCompute(PID_TypeDef *pid, float FB);


#endif 
