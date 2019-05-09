#include "flash.h"

static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_Sector_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_Sector_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_Sector_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_Sector_7;  
  }

  return sector;
}


void Write_Sector(uint32_t Star_Addr, char *wdata, u32 size_len)
{
	u32 *tmp_data = (u32 *)wdata;
	u32 uwData32 = 0;
	u32 uwStartSector; // 起始扇区编号
	u32 uwEndSector;   // 结束扇区编号
	u32 uwSectorCounter;  // 临时扇区编号变量
	u32 uwAddress; // 写数据的起始地址
	
	// 解除写保护
	FLASH_Unlock();
	
	/* Erase the user Flash area ************************************************/
	/* area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR */
	
	/* Clear pending flags (if any) */  
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
					FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	
	/* Get the number of the start and end sectors */
	uwStartSector = GetSector(Star_Addr);
	uwEndSector = GetSector(Star_Addr + size_len);
	
	/* Strat the erase operation */
	uwSectorCounter = uwStartSector;
	while (uwSectorCounter <= uwEndSector) 
	{
		// 擦除对应的uwSectorCounter扇区
		if (FLASH_EraseSector(uwSectorCounter, VoltageRange_3) != FLASH_COMPLETE)
		{ 
			/* Error occurred while sector erase. 
			User can add here some code to deal with this error  */
			printf("擦除失败！\n");
		}
		
		uwSectorCounter += 8;
	}
	
	 uwAddress = Star_Addr;

	while (uwAddress < Star_Addr+size_len)
	{
		printf("temp_data=%#X\n", *tmp_data);
		if (FLASH_ProgramWord(uwAddress, *tmp_data++) == FLASH_COMPLETE)
		{
			uwAddress = uwAddress + 4;
		}
		else
		{ 
			printf("写入失败\n");
		}
	}

	FLASH_Lock(); 
	
}

int Read_Data(uint32_t Start_Addr, char *buffer, u32 len)
{
	u32 uwAddress; // 写数据的起始地址
	u32 *temp_data =  (u32 *)buffer;
	int size_count = 0;
	
	// 读取写入的数据
	uwAddress = Start_Addr;
	
		if( (len % 4) != 0)
			len = len / 4 + 1;
		else
			len = len / 4;
	
	while (uwAddress < Start_Addr+len)
	{
		*temp_data = *(__IO uint32_t*)uwAddress;
		
		
		if (*temp_data++ == 0xFFFFFFFF)
		{
			*temp_data--;
			*temp_data = 0x00;
			
			printf("读取完成\n");
			break;
		}
		size_count += 4;
		uwAddress = uwAddress + 4;
	}  
	
	return size_count;

}	


