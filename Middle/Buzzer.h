#ifndef __BUZZER_H_
#define __BUZZER_H_

#include "ti_msp_dl_config.h"
#define Buzzer_Interval_Time 2 //ms
typedef struct
{
    uint8_t state;
    uint32_t tick;
    float frequency;
} Buzzer;

void Buzzer_Init(void);
void Buzzer_On_Time(uint32_t time, float frequency);
void Buzzer_Tick(void);

#endif
