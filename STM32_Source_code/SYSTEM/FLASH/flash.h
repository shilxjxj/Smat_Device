#ifndef __FLASH_H__
#define __FLASH_H__

#include "stm32f4xx.h"
#include "stdio.h"

//#define FLASH_Sector_0     ((uint16_t)0x0000) /*!< Sector Number 0   */
//#define FLASH_Sector_1     ((uint16_t)0x0008) /*!< Sector Number 1   */
//#define FLASH_Sector_2     ((uint16_t)0x0010) /*!< Sector Number 2   */
//#define FLASH_Sector_3     ((uint16_t)0x0018) /*!< Sector Number 3   */
//#define FLASH_Sector_4     ((uint16_t)0x0020) /*!< Sector Number 4   */
//#define FLASH_Sector_5     ((uint16_t)0x0028) /*!< Sector Number 5   */
//#define FLASH_Sector_6     ((uint16_t)0x0030) /*!< Sector Number 6   */
//#define FLASH_Sector_7     ((uint16_t)0x0038) /*!< Sector Number 7   */
//#define FLASH_Sector_8     ((uint16_t)0x0040) /*!< Sector Number 8   */

#define  ADDR_FLASH_SECTOR_0   ((uint32_t)0x08000000) 
#define  ADDR_FLASH_SECTOR_1   ((uint32_t)0x08004000) 
#define  ADDR_FLASH_SECTOR_2   ((uint32_t)0x08008000) 
#define  ADDR_FLASH_SECTOR_3   ((uint32_t)0x0800C000) 
#define  ADDR_FLASH_SECTOR_4   ((uint32_t)0x08010000) 
#define  ADDR_FLASH_SECTOR_5   ((uint32_t)0x08020000) 
#define  ADDR_FLASH_SECTOR_6   ((uint32_t)0x08040000) 
#define  ADDR_FLASH_SECTOR_7   ((uint32_t)0x08060000) 
#define  ADDR_FLASH_SECTOR_8   ((uint32_t)0x08080000) 


void Write_Sector(uint32_t Star_Addr, char *wdata, u32 size_len);
int Read_Data(uint32_t Start_Addr, char *buffer, u32 len);

#endif
