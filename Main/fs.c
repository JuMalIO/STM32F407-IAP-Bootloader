#include "fs.h"
#include "ff.h"
#include "diskio.h"
#include <stdio.h>

static FATFS FatFs;
static FIL File;

void FS_Init(void)
{
	f_mount(&FatFs, "", 1);
}

void FS_DeInit(void)
{
	f_mount(NULL, "", 0);
	
	disk_initialize(0);
}

uint32_t FS_Size(char *file)
{
	if (f_open(&File, file, FA_OPEN_EXISTING | FA_READ) != FR_OK)
	{
		return 0;
	}

	uint32_t bytesCount = f_size(&File);
	f_close(&File);
	
	return bytesCount;
}

HAL_StatusTypeDef FS_ReadEntireFile(char *file, uint8_t *buffer, uint32_t bufferSize, void (*callback)(uint8_t *buffer, uint32_t fromBytesCount, uint32_t bytesCount))
{
	if (f_open(&File, file, FA_READ) != FR_OK)
	{
		return HAL_ERROR;
	}
	
	uint32_t fromBytesCount = 0;
	uint32_t bytesCount;
	do
	{
		f_read(&File, buffer, bufferSize, &bytesCount);
		callback(buffer, fromBytesCount, bytesCount);
		fromBytesCount += bytesCount;
	} while (bytesCount > 0);
	f_close(&File);
		
	return HAL_OK;
}

void FS_Delete(char *path)
{
	f_unlink(path);
}

bool FS_IsExistingFile(char *file)
{
	if (f_open(&File, file, FA_READ) == FR_OK)
	{
		f_close(&File);
		return true;
	}
	
	return false;
}
