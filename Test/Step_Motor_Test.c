#include "ti_msp_dl_config.h"
#include "Step_Motor_Test.h"
#include "Step_Motor_Turn_Angle.h"
#include "Step_Motor.h"
#include "Usart.h"
#include "InputCapture.h"
#include "Delay.h"

void Step_Motor_PWM_Measure_Test(void)
{
    Uart_Init();
    InputCapture_Init();
    uint32_t start_tick = Get_ms(); 
    StepMotor_Up_Start();
    StepMotor_Down_Start();
    StepMotor_Up_Set_Speed(360.0f);
    //StepMotor_Down_Set_Speed(360.0f);
    Delay_ms(200);
    uint32_t Pulse_Width_Max_up = Get_PWM_Pulse_Width_Up();
    uint32_t Pulse_Width_Min_up = Get_PWM_Pulse_Width_Up();
    uint32_t Pulse_Width_Max_down = Get_PWM_Pulse_Width_Down();
    uint32_t Pulse_Width_Min_down = Get_PWM_Pulse_Width_Down();
    uint32_t Pulse_Width = 0;
    uint8_t flag = 0;
    while(1)
    {
        if(Get_ms() - start_tick > 10000)
        {
            Uart0_Printf("Up: Max:%d , Min:%d , Pulse:%d , Period:%d \n", Pulse_Width_Max_up, Pulse_Width_Min_up, Get_PWM_Pulse_Width_Up(), Get_PWM_Period_Width_Up());
            Uart0_Printf("Down: Max:%d , Min:%d , Pulse:%d , Period:%d \n", Pulse_Width_Max_down, Pulse_Width_Min_down, Get_PWM_Pulse_Width_Down(), Get_PWM_Period_Width_Down());
            if(!flag)
            {
                StepMotor_Up_Stop();
                StepMotor_Down_Stop();
                flag = 1;
            }
           
        }else {
            Pulse_Width = Get_PWM_Pulse_Width_Up();
            if(Pulse_Width_Max_up < Pulse_Width){
                Pulse_Width_Max_up = Pulse_Width;
            }else if(Pulse_Width_Min_up > Pulse_Width)
            {
                Pulse_Width_Min_up = Pulse_Width;
            }
                        
            Pulse_Width = Get_PWM_Pulse_Width_Down();
            if(Pulse_Width_Max_down < Pulse_Width){
                Pulse_Width_Max_down = Pulse_Width;
            }else if(Pulse_Width_Min_down > Pulse_Width)
            {
                Pulse_Width_Min_down = Pulse_Width;
            }

        }
    }
}

void Step_Angle_Get_Test(void)
{
    Uart_Init();
    InputCapture_Init();
    StepMotor_Up_Start();
    StepMotor_Down_Start();
    StepMotor_Up_Set_Speed(360.0f);
    StepMotor_Down_Set_Speed(360.0f);
    Delay_ms(200);
    float angle_up = 0.0f, angle_down = 0.0f;
    while(1)
    {
        angle_up = StepMotor_Angle_Up_Get();
        angle_down = StepMotor_Angle_Down_Get();
        Uart0_Printf("%f , %f\n", angle_up, angle_down);
    }
}

static float SP;
static float Buffer_1[5], Buffer_2[5];
static void Uart0_Send1(void)
{
    PERIODIC_R(50)
    Uart0_Printf("%f, %f , %d, %f, %d\n",SP, StepMotor_Angle_Up_Get(), Get_PWM_Pulse_Width_Up(), StepMotor_Angle_Down_Get(), Get_PWM_Pulse_Width_Down());
}
void Step_Turn_Angle_Test(void)
{
    Uart_Init();
    InputCapture_Init();
    Step_Angle_Turn_Init();
    StepMotor_Up_Start();
    StepMotor_Down_Start();
    while(1)
    {
        uint8_t datalong_1 = Uart_K230_ReadCommand(Buffer_1);
        uint8_t datalong_2 = Uart0_ReadCommand(Buffer_2);
        if(datalong_2 == 1)
        {
            Step_Angle_Turn_Cmd(Buffer_2[0]);
        }else if(datalong_2 == 2)
        {
            Step_Up_Angle_Turn_To(Buffer_2[1]);
            Step_Down_Angle_Turn_To(Buffer_2[1]);
            SP = Buffer_2[1];
            Uart0_Printf("Set Angle : %f", Buffer_2[1]);
        }else if(datalong_2 == 3)
        {
            Step_Angle_Turn_SetK(Buffer_2[0], Buffer_2[1], Buffer_2[2]);
            Uart0_Printf("Kp:%f, Ki:%f, Kd: %f", Buffer_2[0], Buffer_2[1], Buffer_2[2]);
        }

        if(datalong_1 == 1)
        {
            Step_Angle_Turn_Cmd(Buffer_1[0]);
            //Uart0_Printf("State: %d",Buffer[0]);
            
        }else if(datalong_1 == 2)
        {
            Step_Up_Angle_Turn_To(Buffer_1[1]);
            Step_Down_Angle_Turn_To(Buffer_1[1]);
            SP = Buffer_1[1];
            //Uart0_Printf("Set Angle : %d", Buffer[1]);
        }else if(datalong_1 == 3)
        {
            Step_Angle_Turn_SetK(Buffer_1[0], Buffer_1[1], Buffer_1[2]);
            //Uart0_Printf("Kp:%d, Ki:%d, Kd: %d", Buffer[0], Buffer[1], Buffer[2]);
        }
        Uart0_Send1();
    }
}
