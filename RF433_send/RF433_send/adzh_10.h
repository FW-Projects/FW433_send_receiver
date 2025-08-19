#ifndef	__ADZU_H__
#define __ADZU_H__

#define uchar unsigned char
#define uint unsigned int
/*
 ADC转换函数：12位AD转换精度＃调用时只需输入单片机的第几个脚 ，从0开始 返回整型值
*/
adc_value_10(uchar inp_n);
ADC_S(void);

#endif