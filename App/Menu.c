#include "Menu.h"
#include "oled.h"
#include "flash_use.h"
#include <stdio.h>
#include "Key.h"
#include "Delay.h"
#include "Step_Motor.h"
#include "task.h"
static uint8_t Key = 0;
static char buffer[16];

void Menu1(void)
{
    float x = 0.0f;
    float y = 0.0f;
    uint8_t menu_state = 1;
    char Menu_String[2][16] = {"Next", "Reset"};
    uint8_t Menu_xy[2][2] = {{0, 48}, {50, 48}};
    OLED_Clear();
    OLED_ShowString(0, 0, "Goal Angle", 16, 1);
    Read_Gimbal_XY(&x, &y);
    sprintf(buffer, "Up: %.2f", y);
    OLED_ShowString(0, 16, buffer, 16, 1);
    sprintf(buffer, "Down: %.2f", x);
    OLED_ShowString(0, 32, buffer, 16, 1);
    OLED_ShowString(Menu_xy[0][0], Menu_xy[0][1], Menu_String[0], 16, 0);
    OLED_ShowString(Menu_xy[1][0], Menu_xy[1][1], Menu_String[1], 16, 1);
    OLED_Refresh();
    
    while(1)
    {
        Key = Key_Num_Get();
        switch(Key)
        {
            case 1: //状态加1
                menu_state = (menu_state == 2) ? 1 : menu_state + 1;
                break;
            case 2: //状态减1
                menu_state = (menu_state == 1) ? 2 : menu_state - 1;
                break;
            case 3: //确定
                if(menu_state == 1)
                {
                    //进入任务界面
                    Menu2_SelectTask();
                }
                else if(menu_state == 2)
                {
                    //进入重置Gimbal界面
                    Menu2_ResetGimbal();
                    Read_Gimbal_XY(&x, &y);
                }
                break;
            default:
                break;
        }

        PERIODIC_C(50); //每250ms刷新一次界面
        OLED_Clear();
        OLED_ShowString(0, 0, "Goal Angle", 16, 1);
        sprintf(buffer, "Up: %.2f", y);
        OLED_ShowString(0, 16, buffer, 16, 1);
        sprintf(buffer, "Down: %.2f", x);
        OLED_ShowString(0, 32, buffer, 16, 1);
        OLED_ShowString(Menu_xy[0][0], Menu_xy[0][1], Menu_String[0], 16, 1);
        OLED_ShowString(Menu_xy[1][0], Menu_xy[1][1], Menu_String[1], 16, 1);
        OLED_ShowString(Menu_xy[menu_state - 1][0], Menu_xy[menu_state - 1][1], Menu_String[menu_state - 1], 16, 0);
        OLED_Refresh();
    }
}

//重置Gimbal的代码
void Menu2_ResetGimbal(void)
{
    float x = StepMotor_Angle_Down_Get();
    float y = StepMotor_Angle_Up_Get();
    uint8_t menu_state = 1;
    char Menu_String[2][16] = {"OK", "EXIT"};
    uint8_t Menu_xy[2][2] = {{0, 48}, {50, 48}};
    OLED_Clear();
    OLED_ShowString(0, 0, "Goal Angle", 16, 1);
    Read_Gimbal_XY(&x, &y);
    sprintf(buffer, "Up: %.2f", y);
    OLED_ShowString(0, 16, buffer, 16, 1);
    sprintf(buffer, "Down: %.2f", x);
    OLED_ShowString(0, 32, buffer, 16, 1);
    OLED_ShowString(Menu_xy[0][0], Menu_xy[0][1], Menu_String[0], 16, 0);
    OLED_ShowString(Menu_xy[1][0], Menu_xy[1][1], Menu_String[1], 16, 1);
    OLED_Refresh();
    while(1)
    {
        
        Key = Key_Num_Get();
        switch(Key)
        {
            case 1: //状态加1
                menu_state = (menu_state == 2) ? 1 : menu_state + 1;
                break;
            case 2: //状态减1
                menu_state = (menu_state == 1) ? 2 : menu_state - 1;
                break;
            case 3: //确定
                if(menu_state == 1)
                {
                    x = StepMotor_Angle_Down_Get();
                    y = StepMotor_Angle_Up_Get();
                    Write_Gimbal_XY(x, y); //重置角度
                    return; //重置完成，返回主界面
                }
                else if(menu_state == 2)
                {
                    return; //直接返回主界面
                }
                break;
            default:
                break;
        }

        PERIODIC_C(50); //每250ms刷新一次界面
        x = StepMotor_Angle_Down_Get();
        y = StepMotor_Angle_Up_Get();
        OLED_Clear();
        OLED_ShowString(0, 0, "Angle", 16, 1);
        sprintf(buffer, "Up: %.2f", y);
        OLED_ShowString(0, 16, buffer, 16, 1);
        sprintf(buffer, "Down: %.2f", x);
        OLED_ShowString(0, 32, buffer, 16, 1);
        OLED_ShowString(Menu_xy[0][0], Menu_xy[0][1], Menu_String[0], 16, 1);
        OLED_ShowString(Menu_xy[1][0], Menu_xy[1][1], Menu_String[1], 16, 1);
        OLED_ShowString(Menu_xy[menu_state - 1][0], Menu_xy[menu_state - 1][1], Menu_String[menu_state - 1], 16, 0);
        OLED_Refresh();
    }
}

//选择任务的代码
void Menu2_SelectTask(void)
{
    uint8_t menu_state = 1;
    char Menu_String[7][16] = {"<-","Test","Task 1","Task 2", "Task 3","Task 4","Task 5"};
    uint8_t Menu_xy[7][2] = {{0, 0}, {0, 16}, {0, 32}, {0, 48}, {0, 0}, {0, 16}, {0, 32}};
    OLED_Clear();
    OLED_ShowString(Menu_xy[0][0], Menu_xy[0][1], Menu_String[0], 16, 0);
    for(int i = 1; i < 4; i++)
    {
        OLED_ShowString(Menu_xy[i][0], Menu_xy[i][1], Menu_String[i], 16, 1);
    }
    OLED_Refresh();
    while(1)
    {
        Key = Key_Num_Get();
        switch(Key)
        {
            case 1: //状态减1
                menu_state = (menu_state == 1) ? 7 : menu_state - 1;
                break;
            case 2: //状态减1
                menu_state = (menu_state == 7) ? 1 : menu_state + 1;
                break;
            case 3: //确定
                //根据menu_state的值执行对应的任务
                switch(menu_state)
                {
                    case 1:
                         return;
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        Menu3_Task(menu_state - 2); //进入任务执行界面，传入任务ID
                        break;
                    default:
                        break;
                }
            default:
                break;
        }

        PERIODIC_C(50); //每250ms刷新一次界面
        OLED_Clear();
        if(menu_state <= 4)
        {
            OLED_ShowString(Menu_xy[0][0], Menu_xy[0][1], Menu_String[0], 16, 0);
            for(int i = 0; i < 4; i++)
            {
                OLED_ShowString(Menu_xy[i][0], Menu_xy[i][1], Menu_String[i], 16, 1);
            }
        }else
        {
            OLED_ShowString(Menu_xy[0][0], Menu_xy[0][1], Menu_String[menu_state - 3], 16, 0);
            for(int i = 4; i < 8; i++)
            {
                OLED_ShowString(Menu_xy[i][0], Menu_xy[i][1], Menu_String[i], 16, 1);
            }
        }
        OLED_ShowString(Menu_xy[menu_state - 1][0], Menu_xy[menu_state - 1][1], Menu_String[menu_state - 1], 16, 0);
        OLED_Refresh();
    }
}

void Menu3_Task(uint8_t task_id)
{
    OLED_Clear();
    char Task_String[16];
    if(!task_id)
    {
        sprintf(Task_String, "Executing Task %d", task_id);
    }else
    {
        sprintf(Task_String, "Executing Test");
    }
    OLED_ShowString(0, 0, "<-", 16, 0);
    OLED_ShowString(0, 16, Task_String, 16, 1);
    OLED_Refresh();

    Gimbal_Turn_To_Goal();
    if(task_id) Send_Task(task_id);
    float Buffer[5] = {0};
    while(1)
    {
        Key = Key_Num_Get();
        if(Key == 3) //按下确定键返回主界面
        {
            return;
        }
        uint8_t datanum = Uart0_ReadCommand(Buffer);
        if((task_id == 2||task_id ==0) && datanum == 1) //如果是Task 2或者Test且接收到数据
        {
            if(Buffer[0] == 1) 
            {
                Buzzer_Task();
                LED_Task();
            }
        }
        if(datanum == 2) //如果接收到两个数据，说明是云台控制指令
        {
            Gimbal_Receive_Task(Buffer[0], Buffer[1]);
        }
        
    }

}
