#include "ti_msp_dl_config.h"
#include "Delay.h"
#include "Usart.h"
#include "Qmath.h"
#include "Step_Motor.h"
#include "Step_Motor_Test.h"
#include "Step_Motor_Turn_Angle.h"
#include "InputCapture.h"
#include "oled.h"
#include "bmp.h"

static void Uart0_Send1(void)
{
    PERIODIC(50)
    Uart0_Printf(" %f , %d, %f, %d\n", StepMotor_Angle_Up_Get(), Get_PWM_Pulse_Width_Up(), StepMotor_Angle_Down_Get(), Get_PWM_Pulse_Width_Down());
}

int main(void)
 {
    SYSCFG_DL_init();




teas















    // Uart_Init();
    // InputCapture_Init();
    // Step_Angle_Turn_Init();
    // StepMotor_Up_Start();
    // StepMotor_Down_Start();
    // DL_TimerG_startCounter(Buzzer_INST);
    // float up_angle = 0.0f;
    // float down_angle = 0.0f;
    // float Buffer[5] = {0};
    // while (1) 
    // {   
    //     uint8_t datanum = Uart_K230_ReadCommand(Buffer);
    //     if(datanum == 2)
    //     {
    //         float angle_1 = StepMotor_Angle_Up_Get_1();
    //         float angle_2 = StepMotor_Angle_Down_Get_1();
    //         up_angle = angle_1 + Buffer[0];
    //         down_angle = angle_2+ Buffer[1];
    //         while(up_angle >= 180.0f) up_angle -= 360.0f;
    //         while(up_angle < -180.0f) up_angle += 360.0f;
    //         while(down_angle >= 180.0f) down_angle -= 360.0f;
    //         while(down_angle < -180.0f) down_angle += 360.0f;
    //         Step_Up_Angle_Turn_To(up_angle);
    //         Step_Down_Angle_Turn_To(down_angle);
    //     }
    //     Uart0_Send1();
    // }
}

void Timer_Gimbal_INST_IRQHandler(void)
{
    StepMotor_Angle_Proc();
    Step_Angle_Callback();   
}
