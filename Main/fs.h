#ifndef __fs_H
#define __fs_H


#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

void FS_Init(void);
void FS_DeInit(void);
uint32_t FS_Size(char *file);
HAL_StatusTypeDef FS_ReadEntireFile(char *file, uint8_t *buffer, uint32_t bufferSize, void (*callback)(uint8_t *buffer, uint32_t fromBytesCount, uint32_t bytesCount));
void FS_Delete(char *path);
bool FS_IsExistingFile(char *file);


#endif /* __fs_H */
