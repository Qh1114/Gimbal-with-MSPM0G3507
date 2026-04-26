#include "Menu.h"
#include "oled.h"

static uint8_t Key = 0;

void Menu1(void)
{
    OLED_Clear();
    OLED_ShowString(0, 0, "Gimbal Control", 16, 0);
    OLED_ShowString(0, 16, "Up Angle:", 16, 1);
    OLED_ShowString(0, 32, "Down Angle:", 16, 1);
    OLED_ShowString(0, 48, "Down Angle:", 16, 1);
    OLED_Refresh();
}