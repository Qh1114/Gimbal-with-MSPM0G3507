#ifndef __W25Q128_H__
#define __W25Q128_H__

#include "ti_msp_dl_config.h"

#define FLASH_CS(x)   ((x) ? (DL_GPIO_setPins(FLASH_PORT, FLASH_CS_FLASH_PIN)) : (DL_GPIO_clearPins(FLASH_PORT, FLASH_CS_FLASH_PIN)))

uint16_t W25Q128_readID(void);//读取W25Q128的ID
void W25Q128_write(uint8_t* buffer, uint32_t addr, uint16_t numbyte);      //W25Q128写数据
void W25Q128_read(uint8_t* buffer,uint32_t read_addr,uint16_t read_length);//W25Q128读数据

#endif
