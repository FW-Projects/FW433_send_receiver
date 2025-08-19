/*
 ADCת��������10λADת�����ȣ���8λ����2λ����ڲ�����uchar adio_asfΪADģ�⹦�ܿ��ƽ�λ��
        
*/
#include <stdio.h>
#include <SN8F5702.h>
#define ADCEn  0x80
#define EADC (0 << 3) //�ر�ADC�ж�
#define ADCStart  0xc0
#define ad_flag 0x50
#define ClearEOC 0x8f
#define uchar unsigned char
#define uint unsigned int
ADC_S(void);
adc_value_10(uchar inp_n)//10�Σ�����ƽ��ֵ
{
	uint adn=0;
	uint sum=0;
	uint min=0xffff;
	uint max=0;
	uint av_data=0;
	uint ad10_data[10];//�����޷�����������
  ADM= ADCEn | inp_n;
  ADR= 0x50;    // 250Kת��Ƶ��
  VREFH = 0x07;/*IEN0 |= 0x80; //enable global interrupt*/
  IEN2 |= EADC;     //�ر��ж�ad
  for(adn=0;adn<10;adn++)
	{
		ad10_data[adn]=ADC_S();		//����ADת������ֵ
		if(max<ad10_data[adn]) max=ad10_data[adn];//�����
		if(min>ad10_data[adn]) min=ad10_data[adn];//����С
		sum+=ad10_data[adn];//���
	}	
	ADM&= ClearEOC;
  av_data=(sum-min-max)/8;//ȥ�����ֵ��ȥ����Сֵ����ƽ��
	return(av_data);//����ƽ��ֵ	
}
ADC_S(void)
{
 uint ADCBuffer=0;
 ADM |= ADCStart;  //ת����ʼ
 while(ADM&ad_flag);  //�ȴ�����	
 ADCBuffer = (ADB << 4) + (ADR &0x0F);
 ADCBuffer>>=2;
 ADM&= ClearEOC;
 return (ADCBuffer);
}

