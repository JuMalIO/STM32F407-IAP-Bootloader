#ifndef __flash_H
#define __flash_H


#include "stm32f4xx_hal.h"

HAL_StatusTypeDef FLASH_TryUpdate(void);
void FLASH_RunApplication(void);

/* Define the address from where user application will be loaded.
   Note: this area is reserved for the IAP code                  */
#define APPLICATION_ADDRESS        0x08004000          /* Start user code address */

/* stm32f4xx: sector 16 Kbytes x4, 64 Kbytes x1, 128 Kbytes x3... */
#define FLASH_SECTOR_TOTAL_COUNT 8
#ifndef _FLASH_CONST_
#define _FLASH_CONST_
static const uint32_t FLASH_SECTOR_SIZES[FLASH_SECTOR_TOTAL_COUNT] = { 16, 16, 16, 16, 64, 128, 128, 128 };
#endif

/* Notable Flash addresses */
#define FLASH_SIZE                 ((uint32_t)0x80000)  /* 512 KBytes */
#define FLASH_START                ((uint32_t)0x08000000)
#define USER_FLASH_END_ADDRESS     FLASH_START + FLASH_SIZE
  

#endif /*__ flash_H */
