#include "flash_use.h"
#include "W25Q128.h"

//将浮点数转换为Q16.7格式的无符号整数,7位小数
#define decimal_count 7
static uint16_t float_to_uint16(float value)
{
    float value_tmp = value;
    int8_t sign = 0;        //符号位，0表示正数，1表示负数
    if(value_tmp < -180.0f) value_tmp = -180.0f;
    else if(value_tmp > 180.0f) value_tmp = 180.0f;

    if(value_tmp <= 0) {
        value_tmp = -value_tmp;
        sign = 1;
    }
    return ((uint16_t)(value_tmp * (1 << decimal_count))|(sign << 15));
}

static float uint16_to_float(uint16_t value)
{
    int8_t sign = (value >> 15) & 0x01;        //提取符号位
    uint16_t value_tmp = value & 0x7FFF;        //提取数值部分
    float result = (float)value_tmp / (1 << decimal_count);
    if(sign) {
        result = -result;
    }
    return result;
}
void Read_Gimbal_XY(float* x, float* y)
{
    uint8_t buffer[8];
    W25Q128_read(buffer, 0, 8);
    *x = uint16_to_float(*((uint16_t*)buffer));
    *y = uint16_to_float(*((uint16_t*)(buffer + 4)));
}

void Write_Gimbal_XY(float x, float y)
{
    uint8_t buffer[8];
    *((uint16_t*)buffer) = float_to_uint16(x);
    *((uint16_t*)(buffer + 4)) = float_to_uint16(y);
    W25Q128_write(buffer, 0, 8);
}
