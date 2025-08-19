#include "SN8F5702.H"
#include "tmr.h"

/*  T0 tmr  */
#define T0Mode0     0 << 0    //T0 mode0,13bit counter
#define T0Mode1     1 << 0    //T0 mode1,16bit counter
#define T0Mode2     2 << 0    //T0 mode2,8bit auto-reload counter
#define T0Mode3     3 << 0    //T0 mode3,T0 two 8bit counter / T1 no flag
#define T0Gate      8 << 0    //T0 gating clock by INT0
#define T0ClkFcpu   0 << 0    //T0 clock source from Fcpu / 12
#define T0ClkExt    4 << 0    //T0 clock source from Fosc or FRTC
#define T0ExtFosc   0 << 4    //T0 clock source from Fosc
#define T0ExtFRTC   8 << 4    //T0 clock source from FRTC


/*  T1 tmr  */
#define T1Mode0     0 << 4    //T1 mode0,13bit counter
#define T1Mode1     1 << 4    //T1 mode1,16bit counter
#define T1Mode2     2 << 4    //T1 mode2,8bit auto-reload counter
#define T1Mode3     3 << 4    //T1 mode3,T1 stop
#define T1Gate      8 << 4    //T1 gating clock by INT1
#define T1ClkFcpu   0 << 4    //T1 clock source from Fcpu / 12
#define T1ExtFosc   4 << 4    //T1 clock source from Fosc


void InitT0(void)
{
	//T0 Initial 从0x00开始计数
	TH0 = 0x00;
	TL0 = 0x00;
	
	//T0 mode1,16bit counter & Fcpu/12
	TMOD |= T0Mode1 | T0ClkFcpu;
	
	//T0 enable & Clear TF0
	TR0 = 1;
	TF0 = 0;
	
	//enable T0 interrupt
	ET0 = 1;
	//enable total interrupt
	EAL = 1;
	
}

void InitT1(void)
{	
	//T1 mode1,16bit counter & Fcpu/12
	TMOD |= T1Mode1 | T1ClkFcpu;
	
	//T1 enable & Clear TF0
	TR1 = 1;
	TF1 = 0;

	//从初值55536开始计数
	TH1 = (65536 - 10000) / 256;
	TL1 = (65536 - 10000) % 256;

	//低优先级
	IP0 &= ~(1 << 3);
	IP1 &= ~(1 << 3);
	
	//enable T1 interrupt
	ET1 = 1;
	//enable total interrupt
	EAL = 1;
}




void StartT0(void)
{
	TR0 = 1;
	ET0 = 1;
}

void StopT0(void)
{
	TR0 = 0;
	ET0 = 0;
}