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

    uint8_t t=' ';
    OLED_Init();
    OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
    while(1)
    {
        OLED_ShowPicture(0,0,128,64,BMP1,1);
        OLED_Refresh();
        Delay_ms(500);
        OLED_Clear();
        OLED_ShowChinese(0,0,0,16,1);//中
        OLED_ShowChinese(18,0,1,16,1);//景
        OLED_ShowChinese(36,0,2,16,1);//园
        OLED_ShowChinese(54,0,3,16,1);//电
        OLED_ShowChinese(72,0,4,16,1);//子
        OLED_ShowChinese(90,0,5,16,1);//技
        OLED_ShowChinese(108,0,6,16,1);//术
        OLED_ShowString(8,16,(uint8_t*)"ZHONGJINGYUAN",16,1);
        OLED_ShowString(20,32,(uint8_t*)"2014/05/01",16,1);
        OLED_ShowString(0,48,(uint8_t*)"ASCII:",16,1);
        OLED_ShowString(63,48,(uint8_t*)"CODE:",16,1);
        OLED_ShowChar(48,48,t,16,1);//显示ASCII字符
        t++;
        if(t>'~')t=' ';
        OLED_ShowNum(103,48,t,3,16,1);
        OLED_Refresh();
        Delay_ms(500);
        OLED_Clear();
        OLED_ShowChinese(0,0,0,16,1);  //16*16 中
        OLED_ShowChinese(16,0,0,24,1); //24*24 中
        OLED_ShowChinese(24,20,0,32,1);//32*32 中
        OLED_ShowChinese(64,0,0,64,1); //64*64 中
        OLED_Refresh();
        Delay_ms(500);
        OLED_Clear();
        OLED_ShowString(0,0,(uint8_t*)"ABC",8,1);//6*8 “ABC”
        OLED_ShowString(0,8,(uint8_t*)"ABC",12,1);//6*12 “ABC”
        OLED_ShowString(0,20,(uint8_t*)"ABC",16,1);//8*16 “ABC”
        OLED_ShowString(0,36,(uint8_t*)"ABC",24,1);//12*24 “ABC”
        OLED_Refresh();
        Delay_ms(500);
        OLED_ScrollDisplay(11,4,1);
    }
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
