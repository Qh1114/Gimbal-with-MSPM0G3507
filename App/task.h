#ifndef __TASK_H_
#define __TASK_H_

#include "ti_msp_dl_config.h"

void Transfer_Protocol(float *data, uint8_t length, char *protool);
void Send_Task(uint8_t task_id);
void Gimbal_Receive_Task(float angle_down, float angle_up);
void Buzzer_Task(void);
void LED_Task(void);
void Gimbal_Turn_To_Goal(void);

#endif