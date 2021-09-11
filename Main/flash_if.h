#ifndef __flash_if_H
#define __flash_if_H


#include "stm32f4xx_hal.h"
#include "flash_if_config.h"

void FLASH_IF_Init(void);
HAL_StatusTypeDef FLASH_IF_Erase(uint32_t start, uint32_t size);
void FLASH_IF_ProgramFlashMemory(uint8_t *buffer, uint32_t fromBytesCount, uint32_t bytesCount);


#endif /* __flash_if_H */
