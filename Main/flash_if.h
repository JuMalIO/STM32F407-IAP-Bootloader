#ifndef __flash_if_H
#define __flash_if_H


#include "stm32f4xx_hal.h"

#define FLASH_IF_APPLICATION_ADDRESS  0x08000000

/* stm32f4xx: sector 16 Kbytes x4, 64 Kbytes x1, 128 Kbytes x3... */
#define FLASH_IF_SECTOR_TOTAL_COUNT 8
#ifndef _FLASH_IF_CONST_
#define _FLASH_IF_CONST_
static const uint32_t FLASH_IF_SECTOR_SIZES[FLASH_IF_SECTOR_TOTAL_COUNT] = { 16, 16, 16, 16, 64, 128, 128, 128 };
#endif

#define FLASH_IF_SIZE                 ((uint32_t)0x4000)  /* 16 KBytes */
#define FLASH_IF_START                ((uint32_t)0x08000000)
#define FLASH_IF_END_ADDRESS          FLASH_IF_START + FLASH_IF_SIZE

void FLASH_IF_Init(void);
HAL_StatusTypeDef FLASH_IF_Erase(uint32_t start, uint32_t size);
void FLASH_IF_ProgramFlashMemory(uint8_t *buffer, uint32_t fromBytesCount, uint32_t bytesCount);


#endif /* __flash_if_H */
