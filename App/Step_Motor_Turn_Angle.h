#ifndef __STEP_MOTOR_TURN_ANGLE_H__
#define __STEP_MOTOR_TURN_ANGLE_H__

typedef enum
{
    Stop, 
    Start
}Turn_Angle_State;

extern float speed_up, speed_down;
void Step_Angle_Turn_Init(void);
void Step_Up_Angle_Turn_To(float goal_angle);
void Step_Down_Angle_Turn_To(float goal_angle);
void Step_Angle_Turn_SetK(float kp, float ki, float kd);
void Step_Angle_Turn_Cmd(Turn_Angle_State State);
void Step_Angle_Callback(void);

#endif
