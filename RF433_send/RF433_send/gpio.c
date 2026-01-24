
#include <SN8F5703.H>
#include "gpio.h"

void gpio_init(void)
{
	/* key input gpio */
	
	//P00-P07
	P0UR = 0xff;
	P0M = 0x00;
	
	//P13-P14
	P1UR = 0xff;
	P1M = 0x00;

	
	/* 433send  output gpio */
	P2UR &= ~(1 << 0);
	P2M |= 1 << 0;
	
	//LED
	P2UR &= ~(3 << 3);
	P2M |= 3 << 3;
	
	//DONE CHAR
	P2UR |= 3 << 1;
	P2M &= ~(3 << 1);
}