#include "ti_msp_dl_config.h"
#include "Step_Motor_Turn_Angle.h"
#include "Step_Motor.h"
#include "PID.h"
#include <math.h>
#define up_limit 140.0f
#define low_limit -90.0f
#define angle_deadband 0.25f
#define min_start_speed_up 20.0f
#define min_start_speed_down 20.0f
static PID_TypeDef pid_turn_angle_up, pid_turn_angle_down;
volatile static bool cmd_up = false, cmd_down = false;
static uint8_t state_up = 0, state_down = 0;       //上电机运行状态， 1表示运行中， 0表示停止
static float SP_up = 0, SP_down = 0;

void Step_Angle_Turn_Init(void)
{
    PID_Init(&pid_turn_angle_up, 4, 0, 0, 0.002);
    PID_Init(&pid_turn_angle_down, 4, 0, 0, 0.002);
    PID_SetOutputLimits(&pid_turn_angle_up, 1000, -1000, 500, -500);
    PID_SetOutputLimits(&pid_turn_angle_down, 1000, -1000, 500, -500);
    NVIC_ClearPendingIRQ(Timer_Gimbal_INST_INT_IRQN);
    cmd_up = false;
    cmd_down = false;
}

void Step_Up_Angle_Turn_To(float goal_angle)
{
    SP_up = goal_angle;
    PID_ChangeSP(&pid_turn_angle_up, goal_angle);
    state_up = 0;
    cmd_up = true;
}

void Step_Down_Angle_Turn_To(float goal_angle)
{
    SP_down = goal_angle;
    PID_ChangeSP(&pid_turn_angle_down, goal_angle);
    state_down = 0;
    cmd_down = true;
}

void Step_Angle_Turn_SetK(float kp, float ki, float kd)
{
    PID_SetK(&pid_turn_angle_up, kp, ki, kd);
    PID_SetK(&pid_turn_angle_down, kp, ki, kd);
}

void Step_Angle_Turn_Cmd(Turn_Angle_State State)
{
    cmd_up = State;
    cmd_down = State;
}

void Step_Angle_Callback(void)
{
    if(cmd_up) 
    {
        float angle_now_up = StepMotor_Angle_Up_Get();
        float speed_up = PID_AngleCompute(&pid_turn_angle_up, angle_now_up);
        StepMotor_Up_Set_Speed(-speed_up);
    }

    if(cmd_down)
    {
        float angle_now_down = StepMotor_Angle_Down_Get();
        float speed_down = PID_AngleCompute(&pid_turn_angle_down, angle_now_down);
        StepMotor_Down_Set_Speed(-speed_down);
    }
}
