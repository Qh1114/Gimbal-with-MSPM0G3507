#include "task.h"
#include "Usart.h"
#include "Buzzer.h"
#include "LED.h"
#include <stdio.h>
#include "Step_Motor.h"
#include "Delay.h"
#include "Step_Motor_Turn_Angle.h"
void Transfer_Protocol(float *data, uint8_t length, char *protool)
{
	// 假设data为float数组的指针
	float *params = data;
	int32_t check_sum = 0;
	char buf[32];
	char *p = protool;
	uint8_t i;

	*p++ = '$';
	for(i = 0; i < length; i++) {
		// 拼接参数，保留两位小数
		if(i == 0) {
			sprintf(buf, "%.2f", params[i]);
		} else {
			sprintf(buf, ",%.2f", params[i]);
		}
		char *q = buf;
		while(*q) *p++ = *q++;
		// 校验累加整数部分
		check_sum += (int32_t)params[i];
	}
	// 负数处理
	while(check_sum < 0) check_sum += 256;
	uint8_t calc_check = check_sum % 256;
	// 拼接校验码，3位，不足补0
	sprintf(buf, "#%03d\r\n", calc_check);
	char *q = buf;
	while(*q) *p++ = *q++;
	*p = '\0';
}

void Send_Task(uint8_t task_id)
{
    float data[3] = {0,0,task_id};
    char protocol[64];
    Transfer_Protocol(data, 3, protocol);
    uint8_t i = 0;
    while(1)
    {
        if(i++ > 5) break; //发送5次
        Uart0_Printf("%s", protocol);
        Delay_ms(100); //每100ms发送一次
    }
}

void Gimbal_Receive_Task(float angle_down, float angle_up)
{
    float angle_1 = StepMotor_Angle_Up_Get_1();
    float angle_2 = StepMotor_Angle_Down_Get_1();
    float up_angle = angle_1 + angle_up;
    float down_angle = angle_2+ angle_down;
    while(up_angle >= 180.0f) up_angle -= 360.0f;
    while(up_angle < -180.0f) up_angle += 360.0f;
    while(down_angle >= 180.0f) down_angle -= 360.0f;
    while(down_angle < -180.0f) down_angle += 360.0f;
    Step_Up_Angle_Turn_To(up_angle);
    Step_Down_Angle_Turn_To(down_angle);
}

void Buzzer_Task(void)
{
    Buzzer_On_Time(100, 3000.0f); 
}

void LED_Task(void)
{
    LED_On_Time(500); 
}

void Gimbal_Turn_To_Goal(void)
{
    float x = 0.0f;
    float y = 0.0f;
    Read_Gimbal_XY(&x, &y);
    Step_Up_Angle_Turn_To(y);
    Step_Down_Angle_Turn_To(x);
}