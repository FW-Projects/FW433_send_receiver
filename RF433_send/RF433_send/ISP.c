#include "ISP.h"
#include <intrins.h>                            					 // for _nop_
#include <absacc.h>																				 // for CBYTE
#define  L_ISP_ADDR 	0xfc0

idata uint16_t r_read_rom_addr = L_ISP_ADDR ;
idata uint8_t u8_data[3] = {0}	;							  //需写Flash的数据

//====================================================================================================//
//写ISP
//====================================================================================================//
void ISPpagewrite(uint8_t *r_ram_address)
{
	WDTR = 0x5a;	
	PERAM = (uint8_t)r_ram_address;						//数据缓存器(IRAM)的第一个地址
	PEROMH = L_ISP_ADDR >> 8;									//页编程(IROM)的第一个地址(15bit-8bit)
	PEROML = (L_ISP_ADDR & 0x00f0);						//页编程(IROM)的第一个地址(7bit-5bit)
	EAL=0;//???              全局中断	//清狗
	PEROML |= 0x0a;														//开始ISP操作
	PECMD = 0x5a;															//开始ISP操作		
	EAL=1;//???              全局中断	
}	

void ISPpageread2(void)
{
	volatile uint8_t i= 0;
	for(i=0;i<3;i++)
	{
		u8_data[i] =CBYTE[r_read_rom_addr++];
	}
}


