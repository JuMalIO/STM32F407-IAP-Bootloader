#ifndef __flash_H
#define __flash_H


#include "stm32f4xx_hal.h"

HAL_StatusTypeDef FLASH_TryUpdate(void);
void FLASH_RunApplication(void);

/* Define the address from where user application will be loaded.
   Note: this area is reserved for the IAP code                  */
#define APPLICATION_ADDRESS           0x08004000          /* Start user code address */
#define APPLICATION_SECTOR            FLASH_SECTOR_1      /* Start user code sector 16 Kbytes x4, 128 Kbytes x... */

/* Notable Flash addresses */
#define FLASH_SIZE                 ((uint32_t)0x80000)  /* 64 KBytes */
#define FLASH_START                ((uint32_t)0x08000000)
#define USER_FLASH_END_ADDRESS     FLASH_START + FLASH_SIZE
  

#endif /*__ flash_H */
