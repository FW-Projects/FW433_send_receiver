
#include "wk_system.h"
#include "at32f421.h"
#include "FW433_handle.h"
#include "asrpro_handle.h"
#include "usart_send_handle.h"

uint16_t Asrpro_Rx_buffer[4] = {0, 0, 0, 0};
bool Rx_usart2_finish_flag = 0;
void asrpro_Handle(void)
{
   union UNION_ASRPRO dat;
   uint32_t data_valH = 0;
   uint32_t data_valL = 0;
	if(Asrpro_Rx_buffer[3] != 0x00 && Rx_usart2_finish_flag == true)
	{
		if (Asrpro_Rx_buffer[0] == 0x00 && Asrpro_Rx_buffer[1] == 0x00) //其余操作
		{
			switch(Asrpro_Rx_buffer[3])
			{
				case MOD1:
					dat.asrpro_data.DATA_VAL_5 = 0x00;
					dat.asrpro_data.DATA_VAL_6 = 0x00;
					dat.asrpro_data.DATA_VAL_7 = 0x00;
					dat.asrpro_data.DATA_VAL_8 = 0x01;
					break;
				case MOD2:
					dat.asrpro_data.DATA_VAL_5 = 0x00;
					dat.asrpro_data.DATA_VAL_6 = 0x00;
					dat.asrpro_data.DATA_VAL_7 = 0x00;
					dat.asrpro_data.DATA_VAL_8 = 0x02;
					break;
				case MOD3:
					dat.asrpro_data.DATA_VAL_5 = 0x00;
					dat.asrpro_data.DATA_VAL_6 = 0x00;
					dat.asrpro_data.DATA_VAL_7 = 0x00;
					dat.asrpro_data.DATA_VAL_8 = 0x03;
					break;
				case MOD4:
					dat.asrpro_data.DATA_VAL_5 = 0x00;
					dat.asrpro_data.DATA_VAL_6 = 0x00;
					dat.asrpro_data.DATA_VAL_7 = 0x00;
					dat.asrpro_data.DATA_VAL_8 = 0x04;
					break;
				case POWER:
					dat.asrpro_data.DATA_VAL_5 = 0x00;
					dat.asrpro_data.DATA_VAL_6 = 0x00;
					dat.asrpro_data.DATA_VAL_7 = 0x00;
					dat.asrpro_data.DATA_VAL_8 = 0x05;
					break;
				case COLD:
					dat.asrpro_data.DATA_VAL_5 = 0x00;
					dat.asrpro_data.DATA_VAL_6 = 0x00;
					dat.asrpro_data.DATA_VAL_7 = 0x00;
					dat.asrpro_data.DATA_VAL_8 = 0x06;
					break;
				case NORMAL:
					dat.asrpro_data.DATA_VAL_5 = 0x00;
					dat.asrpro_data.DATA_VAL_6 = 0x00;
					dat.asrpro_data.DATA_VAL_7 = 0x00;
					dat.asrpro_data.DATA_VAL_8 = 0x07;
					break;
				case CURVE:
					dat.asrpro_data.DATA_VAL_5 = 0x00;
					dat.asrpro_data.DATA_VAL_6 = 0x00;
					dat.asrpro_data.DATA_VAL_7 = 0x00;
					dat.asrpro_data.DATA_VAL_8 = 0x08;
					break;
				case NUMERICAL:
					dat.asrpro_data.DATA_VAL_5 = 0x00;
					dat.asrpro_data.DATA_VAL_6 = 0x00;
					dat.asrpro_data.DATA_VAL_7 = 0x00;
					dat.asrpro_data.DATA_VAL_8 = 0x09;
					break;
				case F:
					dat.asrpro_data.DATA_VAL_5 = 0x00;
					dat.asrpro_data.DATA_VAL_6 = 0x00;
					dat.asrpro_data.DATA_VAL_7 = 0x00;
					dat.asrpro_data.DATA_VAL_8 = 0x0A;
					break;
				case C:
					dat.asrpro_data.DATA_VAL_5 = 0x00;
					dat.asrpro_data.DATA_VAL_6 = 0x00;
					dat.asrpro_data.DATA_VAL_7 = 0x00;
					dat.asrpro_data.DATA_VAL_8 = 0x0B;
					break;
				case CHANGE_HANDLE:
					dat.asrpro_data.DATA_VAL_5 = 0x00;
					dat.asrpro_data.DATA_VAL_6 = 0x00;
					dat.asrpro_data.DATA_VAL_7 = 0x00;
					dat.asrpro_data.DATA_VAL_8 = 0x0C;
					break;
				default:
					break;
			}
		}
		else if (Asrpro_Rx_buffer[0] == 0x01)      //温度操作
		{
			dat.asrpro_data.DATA_VAL_5 = 0x01;
			dat.asrpro_data.DATA_VAL_6 = Asrpro_Rx_buffer[1];
			dat.asrpro_data.DATA_VAL_7 = Asrpro_Rx_buffer[2];
			dat.asrpro_data.DATA_VAL_8 = Asrpro_Rx_buffer[3];

			
		}
		else if (Asrpro_Rx_buffer[0] == 0x02) //风量操作
		{
			dat.asrpro_data.DATA_VAL_5 = 0x02;
			dat.asrpro_data.DATA_VAL_6 = Asrpro_Rx_buffer[1];
			dat.asrpro_data.DATA_VAL_7 = Asrpro_Rx_buffer[2];
			dat.asrpro_data.DATA_VAL_8 = Asrpro_Rx_buffer[3];

		}
		
		// 清除接收数据缓存区
		Asrpro_Rx_buffer[0] = 0x00;
		Asrpro_Rx_buffer[1] = 0x00;
		Asrpro_Rx_buffer[2] = 0x00;
		Asrpro_Rx_buffer[3] = 0x00;
		// 填充包头
		dat.asrpro_data.DATAHEAD = 0xD1; // 包头
		// 填充通用指令和指令使用
		dat.asrpro_data.UNIVERSAL_COMMAND = 0x01; // 通用指令
		dat.asrpro_data.COMMAND_USE = 0x06;       // 指令使用
		// 填充地址
		dat.asrpro_data.ADDR_H = 0x00; // 地址高字节
		dat.asrpro_data.ADDR_L = 0x06; // 地址低字节
		// 填充数据长度
		dat.asrpro_data.DATA_LENGTH_H = 0x00; // 数据长度高字节
		dat.asrpro_data.DATA_LENGTH_L = 0x0A; // 数据长度低字节
										// 填充无用数据
		dat.asrpro_data.DATA_VAL_1 = 0x00;
		dat.asrpro_data.DATA_VAL_2 = 0x00;
		dat.asrpro_data.DATA_VAL_3 = 0x00;
		dat.asrpro_data.DATA_VAL_4 = 0x00;

		dat.asrpro_data.DATA_NO_1 = 0x00;
		dat.asrpro_data.DATA_NO_2 = 0x00;
		// 填充包尾
		dat.asrpro_data.DATAEND = 0xF0; // 包尾

		// 计算CRC32校验码

		uint32_t checksum[4];
		checksum[0] = (uint32_t)((dat.asrpro_data.UNIVERSAL_COMMAND << 24) | (dat.asrpro_data.COMMAND_USE << 16) | (dat.asrpro_data.ADDR_H << 8) | (dat.asrpro_data.ADDR_L));
		checksum[1] = (uint32_t)((dat.asrpro_data.DATA_LENGTH_H << 24) | (dat.asrpro_data.DATA_LENGTH_L << 16) | (dat.asrpro_data.DATA_VAL_1 << 8) | (dat.asrpro_data.DATA_VAL_2));
		checksum[2] = (uint32_t)((dat.asrpro_data.DATA_VAL_3 << 24) | (dat.asrpro_data.DATA_VAL_4 << 16) | (dat.asrpro_data.DATA_VAL_5 << 8) | (dat.asrpro_data.DATA_VAL_6));
		checksum[3] = (uint32_t)((dat.asrpro_data.DATA_VAL_7 << 24) | (dat.asrpro_data.DATA_VAL_8 << 16) | (0x00 << 8) | (0x00));

		uint32_t crc = crc_block_calculate(checksum, 4);
		crc_data_reset();
		// 将CRC32校验码分成4个字节
		dat.asrpro_data.CHECKSUM_1 = (crc >> 24) & 0xFF;
		dat.asrpro_data.CHECKSUM_2 = (crc >> 16) & 0xFF;
		dat.asrpro_data.CHECKSUM_3 = (crc >> 8) & 0xFF;
		dat.asrpro_data.CHECKSUM_4 = crc & 0xFF;

		sFW433_t.Receiver_handle.led_times = 0x0a;
		Rx_usart2_finish_flag = false;

		usart1_send_byte(dat.asrpro_buf, sizeof(dat.asrpro_buf));
	}
}

