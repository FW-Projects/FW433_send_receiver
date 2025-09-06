#ifndef __OUTPUT_H
#define __OUTPUT_H
#include "flash.h"
#define FLASH_HANDLE_TIME          5
#define DATA_SIZE                  2
#define FLASH_MENBER               3



/* 主存储地址 */
#define A_LAST_ADDRESS_CODE_ADDRESS           	       (0x08000000 + 1024 * 60)      
#define A_LAST_RIGHT_CODE_FLAG_ADDRESS   				A_LAST_ADDRESS_CODE_ADDRESS + DATA_SIZE   
#define A_FLASH_VERSION_ADDRESS                         A_LAST_RIGHT_CODE_FLAG_ADDRESS + DATA_SIZE   
  
                                                                            
/* 备份地址 */    
#define B_LAST_ADDRESS_CODE_ADDRESS           	       (0x08000000 + 1024 * 61)
#define B_LAST_RIGHT_CODE_FLAG_ADDRESS   				B_LAST_ADDRESS_CODE_ADDRESS + DATA_SIZE   
#define B_FLASH_VERSION_ADDRESS                            B_LAST_RIGHT_CODE_FLAG_ADDRESS + DATA_SIZE
  						 
typedef enum
{
    FLASH_START = 0,
    FLASH_DIRECT_DATA,   
	FLASH_FINSH,
} flash_state_t;


typedef struct
{
    flash_state_t state;
} flash_handle_t;

void FlashProc(void);

#endif
