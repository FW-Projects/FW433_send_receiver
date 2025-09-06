#include "SN8F5702.H"
#include "intrins.h"
#include "delayms.h"
#include "433send.h"
#include "getkey.h"
#include "ISP.h"
#include "gpio.h"
#include "tmr.h"

#define uint8_t unsigned char
#define uinttrue6_t unsigned int

#define true 1
#define false 0

#define KEY_NULL 0x00
#define KEY_CH1 0x01
#define KEY_CH2 0x02
#define KEY_CH3 0x03
#define KEY_CH4 0x04

#define KEY_TEMP_UP 0x05
#define KEY_TEMP_DOWN 0x06

#define KEY_AIR_UP 0x07
#define KEY_AIR_DOWN 0x08
#define KEY_SWITCH_HANDLE 0x09

#define KEY_Right_Code 0xff
#define KEY_CLEAR_CODE 0x0f

sbit SEND_LED = P2 ^ 4;
sbit Battery_LED = P2 ^ 3;
sbit charge_flag = P2 ^ 1; 

volatile uint8_t key_out_time = 0, key_state = 0,key_n = 0,start_init_outtime = 0,reset_led_time = 0;
volatile uint8_t send_data = 0,first_get_addr_complete_flag = 0,send_counter = 0,led_times = 0,while_n = 0x00;
volatile uint16_t send_addr = 0;
volatile bit key_ent_flag = 0,longkey_flag = 0,tmr_stop_flag = 0,start_init_flag = 0,reset_flag = 0;
volatile bit start_init_end_flag = 0,key_stop_tmr_flag = 0,send_finish_flag = 0,open_led_flag = 0;

void key_handle(void);
void fisrt_get_addr_handle(void);
void send_handle(void);
void Start_init_handle(void);
void Rom_write(uinttrue6_t in_data, uint8_t n);
void Rom_read(void);
uint16_t data_8bit_to_16bit(uint8_t n);
void check_key(void);

void T0Interrupt(void) interrupt ISRTimer0  
{
	//TF0 clear
	TF0 = 0;
	TH0 = 0;
	TL0 = 0;
}


void T1Interrupt(void) interrupt ISRTimer1
{
	if(key_n != 0x00)
	{
		key_n --;
	}
	if(start_init_outtime != 0x00)
	{
		start_init_outtime--;
	}
	if(key_out_time != 0x00)
	{
		key_out_time--;
	}

	if(reset_flag == true)
	{
		if(reset_led_time != 0x00)
		{
			reset_led_time--;
		}
		else
		{
			reset_led_time = 0x01;
			SEND_LED = ~SEND_LED;
		}
	}
	TH1 = (65536 - 10000) / 256;
	TL1 = (65536 - 10000) % 256;
	ET1 = 1; 
	TR1 = 1; 
	TF1 = 0;
}

void main(void)
{
	/* system clock */
 	CKCON = 0x70;
	CLKSEL = 0x05; // Fcpu = 32M
	CLKCMD = 0x69;
	WDTR = 0x5A;

	gpio_init();
	InitT0(); // ���ڻ�ȡ������
	InitT1();
	Witty433_Init(set_433time_buf); // 433���͵�ƽʱ������
	Rom_read();
	while (1)
	{
		WDTR = 0x5A;
		if (start_init_flag == 0)
		{
			if (first_get_addr_complete_flag == false)
			{
				if(key_stop_tmr_flag == true)
				{
					// �����״λ�ȡ������
					first_get_addr_complete_flag = true; // �����״λ�ȡ��ַ����ɱ�־λ
					key_stop_tmr_flag = false;			
					start_init_flag = true;				// ���ÿ�ʼ��־λ
					fisrt_get_addr_handle();	
				}
				else
				{
//					StartSend_433(0xffff, 0x00);
				}
														// ��ȡ��ַ��	
			}
			else 
			{
				send_data = key_state;
				send_handle(); // 433���ʹ���
			}
		}
		else 
			Start_init_handle(); // ��ʼ������
		switch(while_n)
		{
			case 1: 
				if(reset_flag == false)
				{
					if(open_led_flag == true)
					{
						SEND_LED = true;
						led_times++;
						if(led_times > 10)
						{
							SEND_LED = false;
							led_times = 0;
						}
					}
				}
				if(charge_flag == 0)
					Battery_LED = true;
				else 
					Battery_LED = false;
				break;
			case 2:
				if (key_n  == 0)
				{
					key_handle(); // ����ʶ��
					key_n  = 0x02;
				}
				break;
			default:
				while_n = 0x00;
				break;
			
		}
		while_n++;
		
	}
}

/*
 * 433���ʹ���
 * ��ʼ��+��ַ��+������+������
 */
void send_handle(void)
{
#if 1
	//����5֡����
	if(longkey_flag == true)  //����һֱ����
	{
		StartSend_433(send_addr, send_data);
		send_finish_flag = true;
		open_led_flag = true;
	}
	else
	{
		if(send_finish_flag == false)
		{
			StartSend_433(send_addr, send_data);
			send_finish_flag = true;
//			send_counter++;
//			if(send_counter > 1)
//			{
//				key_state = KEY_NULL;
//				send_finish_flag = true;
//				send_counter = 0x00;
//				open_led_flag = true;
//			}
		}
		
	}
	


	
#endif

}

/*
 *�����״λ�ȡ��ַ��
 *ͨ����ʱ��������ȡ����ʱ��
 *����ʱ����Ϊ��ַ��洢��flash��
 *����ʱ�䷶Χ0~65535
 *������ͣ��־Ϊȷ�ϼ�����
 */
void fisrt_get_addr_handle(void)
{				  
	StopT0();																  // ֹͣ����
	send_addr = TH0  << 8 | TL0;				  // ��ȡ����ʱ����Ϊ��ַ��
	u8_data[2] = first_get_addr_complete_flag; // ��ַ���λ
	Rom_write(send_addr, 0);					  // д��Flash
}
void Start_init_handle(void)
{
	if (start_init_flag == true && start_init_end_flag == 0)
	{

		start_init_end_flag = true; // ���ý�����־λ
		start_init_outtime = 0x0A;
		send_finish_flag = false;
		/* ��ȡROM���� */
		send_addr = data_8bit_to_16bit(0); // ROM��ַ

		first_get_addr_complete_flag = u8_data[2]; // �״λ�ȡ��ַ����ɱ�־λ
		if(first_get_addr_complete_flag > 1)
			first_get_addr_complete_flag = 0;
		if (first_get_addr_complete_flag == false)
		{
			// ������ʱ����ʼ����
			TH0 = 0x00; // ����������
			TL0 = 0x00;
			StartT0(); // ��������
		}
		else
			StopT0(); // ֹͣ����
	}
	else if (start_init_end_flag == true && start_init_outtime == 0x00)
	{
		start_init_flag = false; // ��λ��־λ
		start_init_end_flag = false;
	}
}

void Rom_write(uinttrue6_t in_data, uint8_t n)
{
	/* true6bit�����ݴ����� */
	u8_data[n] = in_data >> 8; // ��λ
	u8_data[n + 1] = in_data;  // ��λ
	ISPpagewrite(u8_data);
}

uint16_t data_8bit_to_16bit(uint8_t n)
{
	uinttrue6_t out_data;
	out_data = (u8_data[n] << 8) | u8_data[n + 1]; // true6bit����
	return out_data;
}
void Rom_read(void)
{
	ISPpageread2();
	start_init_flag = true;
	start_init_end_flag = 0;
	start_init_outtime = 0x00;
}


#if 1
void key_handle(void)
{
	uint8_t key_value;
	key_value = get_key();
	if (inkey_number == key_temp_up)
	{
		switch (key_value)
		{
		case (keydown_ent):
			break;
		case (keyup_ent):
		{
			if(longkey_flag == 0)
			{
				key_ent_flag = true;
				key_state = KEY_TEMP_UP;
				send_finish_flag = false;
			}
			inkey_number = key_null;
			longkey_flag = false;
			key_out_time = 0x05;
		}
		break;
		case (key_long):
			break;
		case (key_continue):
		{
			if(longkey_flag == 0)
			{
				key_ent_flag = true;
				key_state = KEY_TEMP_UP;
				send_finish_flag = false;
				longkey_flag = true;
				key_out_time = 0x05;
			}
		}
		break;
		default:
			break;
		}
	}
	else if (inkey_number == key_temp_down)
	{
		switch (key_value)
		{
		case (keydown_ent):
			break;
		case (keyup_ent):
		{
			if(longkey_flag == 0)
			{
				key_ent_flag = true;
				key_state = KEY_TEMP_DOWN;
				send_finish_flag = false;
			}
			longkey_flag = false;
			inkey_number = key_null;
			key_out_time = 0x05;
		}
		break;
		case (key_long):
			break;
		case (key_continue):
		{
			if(longkey_flag == 0)
			{
				key_ent_flag = true;
				key_state = KEY_TEMP_DOWN;
				send_finish_flag = false;
				longkey_flag = true;
				key_out_time = 0x05;
			}
		}
		break;
		default:
			break;
		}
	}
	else if (inkey_number == key_air_up)
	{
		switch (key_value)
		{
		case (keydown_ent):
			break;
		case (keyup_ent):
		{
			if(longkey_flag == 0)
			{
				key_ent_flag = true;
				key_state = KEY_AIR_UP;
				send_finish_flag = false;
			}
			longkey_flag = false;
			inkey_number = key_null;
			key_out_time = 0x05;
		}
		break;
		case (key_long):
			break;
		case (key_continue):
		{
			if(longkey_flag == 0)
			{
				key_ent_flag = true;
				key_state = KEY_AIR_UP;
				send_finish_flag = false;
				longkey_flag = true;
				key_out_time = 0x05;
			}
		}
		break;
		default:
			break;
		}
	}
	else if (inkey_number == key_air_down)
	{
		switch (key_value)
		{
		case (keydown_ent):
			break;
		case (keyup_ent):
		{
			if(longkey_flag == 0)
			{
			key_ent_flag = true;
			key_state = KEY_AIR_DOWN;
			send_finish_flag = false;
			}
			longkey_flag = false;
			inkey_number = key_null;
			key_out_time = 0x05;
		}
		break;
		case (key_long):
			break;
		case (key_continue):
		{
			if(longkey_flag == 0)
			{
				key_ent_flag = true;
				key_state = KEY_AIR_DOWN;
				send_finish_flag = false;
				longkey_flag = true;
				key_out_time = 0x05;
			}
		}
		break;
		default:
			break;
		}
	}
	else if (inkey_number == key_ch1)
	{
		switch (key_value)
		{
		case (keydown_ent):
			break;
		case (keyup_ent):
		{
			key_ent_flag = true;
			key_state = KEY_CH1;
			send_finish_flag = false;
			inkey_number = key_null;
			key_out_time = 0x05;
		}
		break;
		case (key_long):
			break;
		case (key_continue):
		{
			key_ent_flag = true;
			longkey_flag = true;
		}
		break;
		default:
			break;
		}
	}
	else if (inkey_number == key_ch2)
	{
		switch (key_value)
		{
		case (keydown_ent):
			break;
		case (keyup_ent):
		{
			key_ent_flag = true;
			key_state = KEY_CH2;
			send_finish_flag = false;
			inkey_number = key_null;
			key_out_time = 0x05;
		}
		break;
		case (key_long):
			break;
		case (key_continue):
		{
			key_ent_flag = true;
			longkey_flag = true;
		}
		break;
		default:
			break;
		}
	}
	else if (inkey_number == key_ch3)
	{
		switch (key_value)
		{
		case (keydown_ent):
			break;
		case (keyup_ent):
		{
			key_ent_flag = true;
			key_state = KEY_CH3;
			send_finish_flag = false;
			inkey_number = key_null;
			key_out_time = 0x05;
		}
		break;
		case (key_long):
			break;
		case (key_continue):
		{
			key_ent_flag = true;
			longkey_flag = true;
		}
		break;
		default:
			break;
		}
	}
	else if (inkey_number == key_ch4)
	{
		switch (key_value)
		{
		case (keydown_ent):
			break;
		case (keyup_ent):
		{
			key_ent_flag = true;
			key_state = KEY_CH4;
			send_finish_flag = false;
			inkey_number = key_null;
			key_out_time = 0x05;
		}
		break;
		case (key_long):
			break;
		case (key_continue):
		{
			key_ent_flag = true;
			longkey_flag = true;
		}
		break;
		default:
			break;
		}
	}
	else if (inkey_number == KEY_Switch_handle)
	{
		/* ȷ�ϰ���  &  ������
		 * ������ �� ����ȷ�ϼ� ȷ������������
		 */
		switch (key_value)
		{
		case (keyup_ent):
		{
			if(longkey_flag == 0)
			{
				//�л��ֱ�
				key_ent_flag = true;
				key_state = KEY_SWITCH_HANDLE;
				send_finish_flag = false;
				key_out_time = 0x05;
			}
			longkey_flag = false;
			inkey_number = key_null;
		}
		break;
		case (key_continue):
		{
			if(longkey_flag == 0)
			{
				key_ent_flag = true;
				if(first_get_addr_complete_flag == false)
					key_stop_tmr_flag = true; // ֹͣ����
				else
					key_state = KEY_Right_Code;
				send_finish_flag = false;
				longkey_flag = true;
				key_out_time = 0x05;
			}
			
		}
		break;
		default:
			break;
		}
	}
	else if (inkey_number == key_clear)
	{
		/* �������  
		 */
		switch (key_value)
		{
		case (keyup_ent):
		{
			inkey_number = key_null;
			longkey_flag = false;
		}
		break;
		case (key_continue):
		{
			if(longkey_flag == 0)
			{
				key_ent_flag = true;
				key_state = KEY_CLEAR_CODE;
				send_finish_flag = false;
				longkey_flag = true;
				key_out_time = 0x05;
			}
			
		}
		break;
		default:
			break;
		}
	}
	else if( inkey_number == key_reset)
	{
		/* �ָ��������� ��Ҫ���»�ȡ������  
		 */
		switch (key_value)
		{
		case (keyup_ent):
		{
			inkey_number = key_null;
			longkey_flag = false;
		}
		break;
		case (key_continue):
		{
			if(longkey_flag == 0)
			{
				key_ent_flag = true;
				send_addr = 0x0000;
				first_get_addr_complete_flag = false;
				Rom_write(send_addr, 0);
				key_stop_tmr_flag = false;
				send_finish_flag = false;
				send_data = 0x00;
				key_state = send_data;
				reset_flag = true;
				longkey_flag = true;
				key_out_time = 0x20;
			}
			
		}
		break;
		default:
			break;
		}
	}
	else if(key_ent_flag == true && key_out_time == 0x00)
	{
		key_ent_flag = false;
		longkey_flag = 0;
		if(reset_flag == true)
			reset_flag = false;
	}
}
#endif
