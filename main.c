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

static void OLED_RunSelfTest(void)
{
    /*
     * OLED 分层自检：
     * 1) A5 全亮命令：验证命令通道(DC/CS/SPI时序)
     * 2) GRAM 清屏+画框：验证数据通道
     * 3) 反色+翻转：验证显示控制寄存器命令
     * 4) 文本显示：验证字体与坐标绘制链路
     */
    for (uint8_t i = 0; i < 3; i++) {
        OLED_WR_Byte(0xAE, OLED_CMD);
        OLED_WR_Byte(0xA5, OLED_CMD);
        OLED_WR_Byte(0xAF, OLED_CMD);
        Delay_ms(300);
        OLED_WR_Byte(0xAE, OLED_CMD);
        OLED_WR_Byte(0xA4, OLED_CMD);
        OLED_WR_Byte(0xAF, OLED_CMD);
        Delay_ms(300);
    }

    OLED_Clear();
    for (uint8_t x = 0; x < 128; x++) {
        OLED_DrawPoint(x, 0, 1);
        OLED_DrawPoint(x, 63, 1);
    }
    for (uint8_t y = 0; y < 64; y++) {
        OLED_DrawPoint(0, y, 1);
        OLED_DrawPoint(127, y, 1);
    }
    OLED_Refresh();
    Delay_ms(700);

    OLED_ColorTurn(1);
    Delay_ms(300);
    OLED_ColorTurn(0);
    OLED_DisplayTurn(1);
    Delay_ms(300);
    OLED_DisplayTurn(0);

    OLED_Clear();
    OLED_ShowString(0, 0, (uint8_t*)"OLED DIAG", 16, 1);
    OLED_ShowString(0, 18, (uint8_t*)"CMD OK", 12, 1);
    OLED_ShowString(0, 34, (uint8_t*)"DATA OK", 12, 1);
    OLED_ShowString(0, 50, (uint8_t*)"CTRL OK", 12, 1);
    OLED_Refresh();
}

int main(void)
 {
    SYSCFG_DL_init();

    // OLED_Init();
    // OLED_ColorTurn(0);//0正常显示，1 反色显示
    // OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
    // OLED_RunSelfTest();

    // while(1)
    // {
    //     Delay_ms(1000);
    // }
    Uart_Init();
    InputCapture_Init();
    Step_Angle_Turn_Init();
    StepMotor_Up_Start();
    StepMotor_Down_Start();
   // DL_TimerG_startCounter(Buzzer_INST);
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
            up_angle = angle_1 - Buffer[1];
            down_angle = angle_2- Buffer[0];
            while(up_angle >= 180.0f) up_angle -= 360.0f;
            while(up_angle < -180.0f) up_angle += 360.0f;
            while(down_angle >= 180.0f) down_angle -= 360.0f;
            while(down_angle < -180.0f) down_angle += 360.0f;
            Step_Up_Angle_Turn_To(up_angle);
            Step_Down_Angle_Turn_To(down_angle);
            Uart_K230_Printf("angle_up_now:%f , angle_down_now:%f, goal_up_angle:%f, goal_down_angle:%f,Buffer:%f,%f\n", StepMotor_Angle_Up_Get(), StepMotor_Angle_Down_Get(), up_angle, down_angle, Buffer[0], Buffer[1]);
        }Uart0_Send1();
    }
        
    
}

void Timer_Gimbal_INST_IRQHandler(void)
{
    StepMotor_Angle_Proc();
    Step_Angle_Callback();   
}
