#include "app.h"
#include "fatfs.h"
#include "flash_if.h"
#include "fs.h"

#define FLASH_FILE "_update.bin"
#define FILE_BUFFER_SIZE 512

typedef void (*pFunction)(void);

pFunction JumpToApplication;
uint32_t  JumpAddress;

void APP_Init(void)
{
	FS_Init();
	
	if (FS_IsExistingFile(FLASH_FILE) && FS_Size(FLASH_FILE) == FLASH_IF_SIZE)
	{
		uint8_t buffer[FILE_BUFFER_SIZE];
		FLASH_IF_Init();
		if (FLASH_IF_Erase(FLASH_IF_APPLICATION_ADDRESS - FLASH_IF_START, FLASH_IF_SIZE) == HAL_OK)
		{
			FS_ReadEntireFile(FLASH_FILE, buffer, FILE_BUFFER_SIZE, FLASH_IF_ProgramFlashMemory);
			FS_Delete(FLASH_FILE);
		}
	}
	
	FS_DeInit();
}

void APP_Run(void)
{
	FATFS_UnLinkDriver(SDPath);
	HAL_RCC_DeInit();
	HAL_DeInit();
	
	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;
	
  //__HAL_RCC_SYSCFG_CLK_ENABLE();
  //__HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();
	
	/* Jump to user application */
	JumpAddress = *(__IO uint32_t*) (FLASH_IF_APPLICATION_ADDRESS + 4);
	JumpToApplication = (pFunction) JumpAddress;
	/* Initialize user application's Stack Pointer */
#if   (defined ( __GNUC__ ))
	/* Compensation as the Stack Pointer is placed at the very end of RAM */
	__set_MSP((*(__IO uint32_t*) APPLICATION_ADDRESS) - 64);
#else  /* (defined  (__GNUC__ )) */
	__set_MSP(*(__IO uint32_t*) FLASH_IF_APPLICATION_ADDRESS);
#endif /* (defined  (__GNUC__ )) */

	JumpToApplication();
}
