#include <SN8F5702.H>
#include "getkey.h"
#define uchar unsigned char
#define uint unsigned int
sbit key_01 = P0 ^ 2;
sbit key_02 = P0 ^ 7;
sbit key_03 = P1 ^ 3;
sbit key_04 = P1 ^ 4;
sbit key_05 = P2 ^ 0;
sbit key_06 = P0 ^ 6;
sbit key_07 = P0 ^ 1;
sbit key_08 = P0 ^ 0;
sbit key_09 = P0 ^ 5;
uint8_t key_stat = 1;

volatile uint8_t inkey_number = 0; // ���水������ֵ
volatile uint16_t key_time = 0, last_temp;

uint8_t key_scan(void)
{
	if(key_05 == 0 && key_04 == 0)
		return (key_reset);
	if(key_05 == 0 && key_08 == 0)
		return (key_clear);
	if (key_01 == 0)
		return (key_air_up); 
	if (key_02 == 0)
		return (key_temp_down);
	if (key_03 == 0)
		return (key_temp_up);
	if (key_04 == 0)
		return (key_ch3);
	if (key_05 == 0)
		return (key_ch1); 
	if (key_06 == 0)
		return (KEY_Switch_handle);
	if (key_07 == 0)
		return (key_ch4);
	if (key_08 == 0)
		return (key_ch2);
	if (key_09 == 0)
		return (key_air_down);
	return (key_null); 
}				

	uint8_t key_temp = 0;  //
get_key(void) // ɨ�����
{
	key_temp = key_scan(); // ��ȡ�ĸ�������
	switch (key_stat)
	{
	case (key_init):
		if (key_null != key_temp)
			key_stat = key_wobble;
		break;
	case (key_wobble):
		key_stat = key_press;
		break;
	case (key_press):
	{
		if (key_null != key_temp)
		{
			inkey_number = key_temp; // ���潡ֵs
			last_temp = key_temp;
			key_temp = keydown_ent;	 // ȷ�ϰ�����
			key_stat = keylong_stat; // ��λ���������
		}
		else
			key_stat = key_period; // ����λ�������ͷ�
	}
	break;
	case (keylong_stat):
	{
		if (key_null != key_temp)
		{
			if (key_time++ > keylong_pepione) // ��ⳤ����
			{
				key_stat = key_long_on; // ��λ��
				key_temp = key_long;	// ������־
				key_time = 0;
			}
			else
			{
				if (last_temp != key_temp)
					key_time = 0x00, key_stat = key_press;
				key_temp = keydown_ent; // ����ȷ�ϰ���
			}
		}
		else
			key_stat = key_period; // ����λ�������ͷ�
	}
	break;
	case (key_long_on): // ��������
	{
		if (key_null != key_temp)
		{
			if (key_time++ > key_continue_period)
			{
				key_time = 0;
				key_temp = key_continue;
				key_stat = key_long_on;
			}
			else
				key_temp = key_long;
		}
		else
			key_stat = key_period;
	}
	break;
	case (key_period): //                ȷ�ϰ����ͷ�
	{
		key_time = 0;
		key_stat = key_init;
		key_temp = keyup_ent;
	}
	break;
	default:
		inkey_number = key_null;
		break; // �޼�����
	}
	return (key_temp);
}