#include "flash_if.h"
#include "utils.h"

void FLASH_IF_Init(void)
{
  /* Unlock the Program memory */
  HAL_FLASH_Unlock();

  /* Clear all FLASH flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR | FLASH_FLAG_WRPERR);
	
  /* Unlock the Program memory */
  HAL_FLASH_Lock();
}

HAL_StatusTypeDef FLASH_IF_Erase(uint32_t start, uint32_t size)
{
  uint32_t strOfSector = 0;
  uint32_t nbrOfSectors = 0;
  uint32_t pageError = 0;
  FLASH_EraseInitTypeDef pEraseInit = {0};
  HAL_StatusTypeDef status = HAL_OK;

  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();

  /* Get the sector where start the user flash area */
	for (uint16_t i = 0; i < FLASH_IF_SECTOR_TOTAL_COUNT; i++)
	{
		if (start >= FLASH_IF_SECTOR_SIZES[i] * 1024)
		{
			start -= FLASH_IF_SECTOR_SIZES[i] * 1024;
			strOfSector++;
		}
		else
		{
			start = 0;
			
			if (size > 0)
			{
				size -= MIN(FLASH_IF_SECTOR_SIZES[i] * 1024, size);
				nbrOfSectors++;
			}
		}
	}

  pEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
	pEraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
  pEraseInit.Sector = strOfSector;
  pEraseInit.NbSectors = nbrOfSectors;
  status = HAL_FLASHEx_Erase(&pEraseInit, &pageError);

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();

  if (status != HAL_OK)
  {
    /* Error occurred while page erase */
    return HAL_ERROR; // FLASHIF_ERASEKO;
  }

  return HAL_OK;
}

HAL_StatusTypeDef FLASH_IF_Write(uint32_t destination, uint32_t *p_source, uint32_t length)
{
  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();

  for (uint32_t i = 0; (i < (length / 4)) && (destination <= (FLASH_IF_END_ADDRESS - 4)); i++)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, destination, *(uint32_t*)(p_source + i)) == HAL_OK)
    {
      /* Check the written value */
      if (*(uint32_t*)destination != *(uint32_t*)(p_source + i))
      {
        /* Flash content doesn't match SRAM content */
        return HAL_ERROR; // (FLASHIF_WRITINGCTRL_ERROR);
      }
      /* Increment FLASH destination address */
      destination += 4;
    }
    else
    {
      /* Error occurred while writing data in Flash memory */
      return HAL_ERROR; //(FLASHIF_WRITING_ERROR);
    }
  }

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();

  return HAL_OK;
}

void FLASH_IF_ProgramFlashMemory(uint8_t *buffer, uint32_t fromBytesCount, uint32_t bytesCount)
{
	FLASH_IF_Write(fromBytesCount + FLASH_IF_APPLICATION_ADDRESS, (uint32_t*)buffer, bytesCount);
}
