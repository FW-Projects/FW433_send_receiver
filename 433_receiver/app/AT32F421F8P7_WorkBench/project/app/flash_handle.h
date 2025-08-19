#ifndef __OUTPUT_H
#define __OUTPUT_H
#include "flash.h"
#define FLASH_HANDLE_TIME          10
#define DATA_SIZE                  2
#define FLASH_MENBER               2



/* 主存储地址 */
#define A_LAST_ADDRESS_CODE_ADDRESS           	       (0x08000000 + 1024 * 60)      
#define A_FLASH_VERSION_ADDRESS                            A_LAST_ADDRESS_CODE_ADDRESS + DATA_SIZE   
  
                                                                            
/* 备份地址 */    
#define B_LAST_ADDRESS_CODE_ADDRESS           	       (0x08000000 + 1024 * 61)

#define B_FLASH_VERSION_ADDRESS                            B_LAST_ADDRESS_CODE_ADDRESS + DATA_SIZE
  						 
typedef enum
{
    FLASH_START = 0,
    FLASH_DIRECT_DATA,   
	FLASH_GENERAL_DATA,
    FLASH_GENERAL_CH_DATA,
    FLASH_VER,
	FLASH_FINSH,
} flash_state_t;


typedef struct
{
    flash_state_t state;
} flash_handle_t;

void FlashProc(void);

#endif
