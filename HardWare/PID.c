#include "ti_msp_dl_config.h"
#include "PID.h"
#include <ti/iqmath/include/IQmathLib.h>
//
//@简介: 初始化PID控制器
//@参数: pid - PID控制器结构体指针
//@参数: kp - 比例增益
//@参数: ki - 积分增益
//@参数: kd - 微分增益
//@参数: upper_limit - 输出上限
//@参数: lower_limit - 输出下限
//@返回: 无
void PID_Init(PID_TypeDef *pid, float kp, float ki, float kd, float delta_time)
{
    pid->Kp = _IQ13(kp);
    pid->Ki = _IQ13(ki);
    pid->Kd = _IQ13(kd);
    pid->SP = 0;
    pid->delta_time = _IQ13(delta_time);
    pid->last_error = 0;
    pid->last_integral = 0;
    pid->Upper_Limit = 3.4e+38f;
    pid->Lower_Limit = -3.4e+38f;
    pid->Upper_IntergralLimit = 3.4e+38f *0.5;
    pid->Lower_IntergralLimit = -3.4e+38f *0.5;
    pid->first_calculate = 0;
}

//
//@简介: 修改PID控制器的设定点
//@参数: pid - PID控制器结构体指针
//@参数: sp - 新的设定点
//@返回: 无
void PID_ChangeSP(PID_TypeDef *pid, float sp)
{
    pid->SP = _IQ13(sp);
}

//
//@简介: 设置PID控制器的输出限制
//@参数: pid - PID控制器结构体指针
//@参数: upper_limit - 输出上限
//       lower_limit - 输出下限
//@返回: 无
void PID_SetOutputLimits(PID_TypeDef *pid, float upper_limit, float lower_limit, float upper_intergral, float lower_intergral)
{
    pid->Upper_Limit = upper_limit;
    pid->Lower_Limit = lower_limit;
    pid->Upper_IntergralLimit = upper_intergral;
    pid->Lower_IntergralLimit = lower_intergral;
}

//
//@简介: 重置PID控制器的状态
//@参数: pid - PID控制器结构体指针
//@返回: 无
void PID_Reset(PID_TypeDef *pid)
{
    pid->last_error = 0;
    pid->last_integral = 0;
}

//
//@简介: 设置PID控制器的增益参数
//@参数: pid - PID控制器结构体指针
//@参数: kp - 比例增益
//@参数: ki - 积分增益
//@参数: kd - 微分增益
//@返回: 无
void PID_SetK(PID_TypeDef *pid, float kp, float ki, float kd)
{
    pid->Kp = _IQ13(kp);
    pid->Ki = _IQ13(ki);
    pid->Kd = _IQ13(kd);
}

//
//@简介: 计算PID控制器的输出
//@参数: pid - PID控制器结构体指针
//@参数: FB - 当前反馈值
//@返回: PID控制器的输出值
float PID_Compute(PID_TypeDef *pid, float FB)
{
    _iq13 error = pid->SP - _IQ13(FB);

    if(!pid->first_calculate)
    {
        pid->first_calculate = 1;
        pid->last_error = error;
        return _IQ13toF(_IQ13mpy(pid->Kp,error));
    }

    _iq13 err_integral = pid->last_integral + _IQ13div(_IQ13mpy((error + pid->last_error) , pid->delta_time),_IQ13(2.0f));
    _iq13 err_derivative = _IQ13div((error - pid->last_error) , pid->delta_time);

    if(_IQ13toF(err_integral) > pid->Upper_IntergralLimit)
        err_integral = _IQ13(pid->Upper_IntergralLimit);
    else if(_IQ13toF(err_integral) < pid->Lower_IntergralLimit)
        err_integral = _IQ13(pid->Lower_IntergralLimit);    

    _iq13 output_p = _IQ13mpy(pid->Kp , error);
    _iq13 output_i = _IQ13mpy(pid->Ki , err_integral); 
    _iq13 output_d = _IQ13mpy(pid->Kd , err_derivative); 

    float output = _IQ13toF(output_p + output_i + output_d);

    pid->last_integral = err_integral;
    pid->last_error = error;
    
    if(output > pid->Upper_Limit)
        output = pid->Upper_Limit;
    else if(output < pid->Lower_Limit)
        output = pid->Lower_Limit;

    return output;
}

//!!!!!!kd不可大于0.5，否则可能超出计数的范围，根据微分项的出来，error最大为360，delta_time为0.001再乘上kd， 不得超过_iq13的大小
//      但如果实际调参的时候kd远小于0.5.可适当调节q的大小，提高精度
//
//@简介: 计算角度PID控制器的输出
//@参数: pid - PID控制器结构体指针
//@参数: FB - 当前反馈值
//@返回: PID控制器的输出值
float PID_AngleCompute(PID_TypeDef *pid, float FB)
{
    // 1. 计算浮点数角度误差（正确！）
    float error = _IQ13toF(pid->SP) - FB;

    // 2. 角度环归一化到 -180 ~ 180（正确）
    while(error >= 180)     error -= 360;
    while(error < -180)     error += 360;

    // 3. 把 浮点数误差 转成 IQ13定点数（正确用法！）
    _iq13 error_iq = _IQ13(error);

    // 4. 修复初始化：不再直接返回
    if(!pid->first_calculate)
    {
        pid->first_calculate = 1;
        pid->last_error = error_iq;
        pid->last_integral = 0;  // 积分清零
    }

    // 5. 梯形积分 + 微分（正确计算）
    _iq13 err_integral = pid->last_integral + _IQ13div(_IQ13mpy((error_iq + pid->last_error) , pid->delta_time), _IQ13(2.0f));
    _iq13 err_derivative = _IQ13div((error_iq - pid->last_error) , pid->delta_time);

    // 积分限幅
    if(_IQ13toF(err_integral) > pid->Upper_IntergralLimit)
        err_integral = _IQ13(pid->Upper_IntergralLimit);
    else if(_IQ13toF(err_integral) < pid->Lower_IntergralLimit)
        err_integral = _IQ13(pid->Lower_IntergralLimit);    

    // 6. PID 计算
    _iq13 output_p = _IQ13mpy(pid->Kp , error_iq);
    _iq13 output_i = _IQ13mpy(pid->Ki , err_integral); 
    _iq13 output_d = _IQ13mpy(pid->Kd , err_derivative); 

    // 转浮点数输出
    float output = _IQ13toF(output_p + output_i + output_d);

    // 记录历史值
    pid->last_integral = err_integral;
    pid->last_error = error_iq;

    // 输出限幅
    if(output > pid->Upper_Limit)
        output = pid->Upper_Limit;
    else if(output < pid->Lower_Limit)
        output = pid->Lower_Limit;

    return output;
//     float error_1 = _IQ13toF(pid->SP) - FB;
//     // _iq13 error = pid->SP - _IQ13(FB);
//     while(error_1 >= 180)     error_1 -= 360;          //归一化到-180到180
//     while(error_1 < -180)     error_1 += 360;
//     _iq13 error = _IQ13(error_1);

//     if(!pid->first_calculate)
//     {
//         pid->first_calculate = 1;
//         pid->last_error = error;
//         return _IQ13toF(_IQ13mpy(pid->Kp,error));
//     }

//     _iq13 err_integral = pid->last_integral + _IQ13div(_IQ13mpy((error + pid->last_error) , pid->delta_time),_IQ13(2.0f));
//     _iq13 err_derivative = _IQ13div((error - pid->last_error) , pid->delta_time);

//     if(_IQ13toF(err_integral) > pid->Upper_IntergralLimit)
//         err_integral = _IQ13(pid->Upper_IntergralLimit);
//     else if(_IQ13toF(err_integral) < pid->Lower_IntergralLimit)
//         err_integral = _IQ13(pid->Lower_IntergralLimit);    

//     _iq13 output_p = _IQ13mpy(pid->Kp , error);
//     _iq13 output_i = _IQ13mpy(pid->Ki , err_integral); 
//     _iq13 output_d = _IQ13mpy(pid->Kd , err_derivative); 

//    float output =_IQ13toF(output_p + output_i + output_d);
//    //float output =_IQ13toF(output_p);
//     pid->last_integral = err_integral;
//     pid->last_error = error;
    
//     if(output > pid->Upper_Limit)
//         output = pid->Upper_Limit;
//     else if(output < pid->Lower_Limit)
//         output = pid->Lower_Limit;

//     return output;
}

