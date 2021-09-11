#ifndef __flash_if_config_H
#define __flash_if_config_H


#include "stm32f4xx_hal.h"

/* Define the address from where user application will be loaded.
   Note: this area is reserved for the IAP code                  */
#define FLASH_IF_APPLICATION_ADDRESS        0x08004000          /* Start user code address */

/* stm32f4xx: sector 16 Kbytes x4, 64 Kbytes x1, 128 Kbytes x3... */
#define FLASH_IF_SECTOR_TOTAL_COUNT 8
#ifndef _FLASH_IF_CONST_
#define _FLASH_IF_CONST_
static const uint32_t FLASH_IF_SECTOR_SIZES[FLASH_IF_SECTOR_TOTAL_COUNT] = { 16, 16, 16, 16, 64, 128, 128, 128 };
#endif

/* Notable Flash addresses */
#define FLASH_IF_SIZE_LOADER          0x4000               /* 16 KBytes */
#define FLASH_IF_SIZE                 ((uint32_t)0x7C000)  /* 496 KBytes */
#define FLASH_IF_START                ((uint32_t)0x08000000)
#define FLASH_IF_END_ADDRESS          FLASH_IF_START + FLASH_IF_SIZE_LOADER + FLASH_IF_SIZE
  

#endif /* __flash_if_config_H */
