#include <SN8F5703.H>
#include "delayms.h"
#define uint8_t unsigned char
#define uint16_t  unsigned int 
//void delay_ms(uint16_t xms)
//{
//	uint16_t i,j;
//	for(i=xms;i>0;i--)
//	{		
//	for(j=110;j>0;j--);
//	}
//}

void delay_us(uint16_t xus)
{
	uint16_t i,j;
	for(i=xus;i>0;i--)
	for(j=4;j>0;j--);
}

//void delay_us2(uint16_t n) // n=1??1us
//{
//	while (--n)
//	;
//}