#ifndef __STEP_MOTOR__
#define __STEP_MOTOR__

typedef enum
{
    COUNTCLOCK_WISE,
    CLOCK_WISE
} StepMotor_Direction;

typedef enum
{
    DISABLE,
    ENABLE
}StepMotor_State;

#define DIR_UP(T) DL_GPIO_writePinsVal(DIR_UP_PORT, DIR_UP_PIN_0_PIN, (T >= 1) ? (!DIR_UP_PIN_0_PIN) : (DIR_UP_PIN_0_PIN))
#define EN_UP(T) DL_GPIO_writePinsVal(EN_UP_PORT, EN_UP_PIN_1_PIN, (T >= 1) ? (EN_UP_PIN_1_PIN) : (!EN_UP_PIN_1_PIN))
#define DIR_DOWN(T) DL_GPIO_writePinsVal(DIR_DOWN_PORT, DIR_DOWN_PIN_3_PIN, (T >= 1) ? (DIR_DOWN_PIN_3_PIN) : (!DIR_DOWN_PIN_3_PIN))
#define EN_DOWN(T) DL_GPIO_writePinsVal(EN_DOWN_PORT, EN_DOWN_PIN_2_PIN, (T >= 1) ? (EN_DOWN_PIN_2_PIN) : (!EN_DOWN_PIN_2_PIN))

void StepMotor_Up_Start(void);
void StepMotor_Down_Start(void);
void StepMotor_Up_Stop(void);
void StepMotor_Down_Stop(void);
void StepMotor_Up_Set_Speed(float Speed);
void StepMotor_Down_Set_Speed(float Speed);
float StepMotor_Angle_Up_Get(void);
float StepMotor_Angle_Down_Get(void);
float StepMotor_Angle_Up_Get_1(void);
float StepMotor_Angle_Down_Get_1(void);
void StepMotor_Angle_Proc(void);

#endif
