
#include <SN8F5702.H>
#include "gpio.h"

void gpio_init(void)
{
	/* key input gpio */
	
	//P00-P07
	P0UR = 0xff;
	P0M &= 0x00;
	
	//P13-P14
	P1UR = 3 << 3;
	P1M &= ~(3 << 3);

	//P20
	P2UR = 0xff;
	P2M &= 0x00;
	
	/* 433send  output gpio */
	P1UR &= ~(1 << 0);
	P1M |= 1 << 0;
}