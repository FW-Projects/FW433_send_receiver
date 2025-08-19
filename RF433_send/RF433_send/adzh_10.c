/*
 ADC转换函数：10位AD转换精度，高8位，低2位，入口参数：uchar adio_asf为AD模拟功能控制脚位，
        
*/
#include <stdio.h>
#include <SN8F5702.h>
#define ADCEn  0x80
#define EADC (0 << 3) //关闭ADC中断
#define ADCStart  0xc0
#define ad_flag 0x50
#define ClearEOC 0x8f
#define uchar unsigned char
#define uint unsigned int
ADC_S(void);
adc_value_10(uchar inp_n)//10次ＡＤ求平均值
{
	uint adn=0;
	uint sum=0;
	uint min=0xffff;
	uint max=0;
	uint av_data=0;
	uint ad10_data[10];//定义无符号整形数组
  ADM= ADCEn | inp_n;
  ADR= 0x50;    // 250K转换频率
  VREFH = 0x07;/*IEN0 |= 0x80; //enable global interrupt*/
  IEN2 |= EADC;     //关闭中断ad
  for(adn=0;adn<10;adn++)
	{
		ad10_data[adn]=ADC_S();		//调用AD转换并赋值
		if(max<ad10_data[adn]) max=ad10_data[adn];//求最大
		if(min>ad10_data[adn]) min=ad10_data[adn];//求最小
		sum+=ad10_data[adn];//求和
	}	
	ADM&= ClearEOC;
  av_data=(sum-min-max)/8;//去掉最大值，去掉最小值，求平均
	return(av_data);//返回平均值	
}
ADC_S(void)
{
 uint ADCBuffer=0;
 ADM |= ADCStart;  //转换开始
 while(ADM&ad_flag);  //等待结束	
 ADCBuffer = (ADB << 4) + (ADR &0x0F);
 ADCBuffer>>=2;
 ADM&= ClearEOC;
 return (ADCBuffer);
}

