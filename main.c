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
#include "Key.h"
#include "Key_Test.h"
#include "multi_button.h"
#include "LED.h"
#include "LED_Test.h"
#include "Buzzer.h"
#include "Buzzer_Test.h"
#include "Menu.h"
#include "W25Q128_Test.h"
#include "W25Q128.h"
#include "task.h"
int main(void)
 {
    SYSCFG_DL_init();
    Uart_Init();
    InputCapture_Init(); 
    OLED_Init();
    Step_Angle_Turn_Init();
    StepMotor_Up_Start();
    StepMotor_Down_Start();
    NVIC_EnableIRQ(Timer_Gimbal_INST_INT_IRQN);
    DL_TimerG_startCounter(Timer_Gimbal_INST);
    Key_Init();
    //W25Q128_Test3();
    // Send_Task(1);
    // Send_Task(2);
    // Send_Task(3);
    // Send_Task(4);
    // Send_Task(5);

    Menu1();
    //Buzzer_Test1();
    //LED_Test1();
    //Key_Test1();
    float up_angle = 0.0f;
    float down_angle = 0.0f;
    float Buffer[5] = {0};
    while (1) 
    {   
        uint8_t datanum = Uart0_ReadCommand(Buffer);
        if(datanum == 2)
        {
            float angle_1 = StepMotor_Angle_Up_Get_1();
            float angle_2 = StepMotor_Angle_Down_Get_1();
            up_angle = angle_1 + Buffer[1];
            down_angle = angle_2+ Buffer[0];
            while(up_angle >= 180.0f) up_angle -= 360.0f;
            while(up_angle < -180.0f) up_angle += 360.0f;
            while(down_angle >= 180.0f) down_angle -= 360.0f;
            while(down_angle < -180.0f) down_angle += 360.0f;
            Step_Up_Angle_Turn_To(up_angle);
            Step_Down_Angle_Turn_To(down_angle);
        }
    }
        
    
}

void Timer_Gimbal_INST_IRQHandler(void)
{
    Buzzer_Tick();
    LED_Tick();
    button_ticks();
    StepMotor_Angle_Proc();
    Step_Angle_Callback();   
}
