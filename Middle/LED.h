#ifndef __LED_H_
#define __LED_H_

#include "ti_msp_dl_config.h"

#define tick_interval 2  // ms

typedef struct _LED { 
    uint8_t state;      // 0: off, 1: on 
    uint32_t tick;
}LED;

void LED_Init(void);
void LED_On_Time(uint32_t time);
void LED_Tick(void);

#endif // __LED_H