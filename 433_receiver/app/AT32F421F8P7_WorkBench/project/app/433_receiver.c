
#include "wk_system.h"
#include "at32f421.h"
#include "433_receiver.h"
#include "FW433_handle.h"
#include "at32f421_int.h"
#include "usart_send_handle.h"

/*
 * SHUT = P4 ^ 4;   //433M SHUT接口 ：低电平工作
 * de = P2 ^ 2;	    //433M DO接口 ： 外部中断接口
 */

void right_code_handle(uint8_t *in_u8_code);
void decode_handle(uint8_t *in_u8code);
/*
 * @brief  433M接收处理函数
 * @param  none
 * @retval none
 *
 * 接收数据的步骤：
 * 1.查询对码状态，如果对码成功，则进入接收状态；如果对码失败，则不进行接收处理；对码状态Right_code_flag
 * 2.对码状态Right_code_flag=0时，时刻查询24bit的后8位按键码，如果按键码=0xff，则开始对码，记录16bit地址码
 * 3.对码状态Right_code_flag=1时，开始解码处理指令
 */
void recevier_handle(void)
{
	if (sFW433_t.Receiver_handle.Right_code_flag == false)
	{
		/* 对码处理 */

		right_code_handle(data_433_buffer);
	}
	else
	{
		/* 解码处理 */

		decode_handle(data_433_buffer);
	}
}

void right_code_handle(uint8_t *in_u8_code)
{
	static uint8_t right_code_time = 0;
	if (in_u8_code[2] == RIGHT_CODE) // 对码指令
	{
		right_code_time++;
		if (right_code_time > 30) // 30帧对码
		{
			right_code_time = 0;
			sFW433_t.Receiver_handle.Right_code_flag = TRUE;							  // 对码成功
			sFW433_t.Receiver_handle.Address_code = (in_u8_code[0] << 8) | in_u8_code[1]; // 保存地址码
		}
	}
}

void decode_handle(uint8_t *in_u8code)
{
	union UNION_433 dat_433;
	sFW433_t.Receiver_handle.Command_code = in_u8code[2];
	if (sFW433_t.Receiver_handle.Command_code == CLEAR_CODE)
	{
		// 清除对码 以至于重新匹配遥控
		sFW433_t.Receiver_handle.Right_code_flag = false;
		sFW433_t.Receiver_handle.Address_code = 0x00;
	}
	else
	{
		if (sFW433_t.Receiver_handle.Address_code == ((in_u8code[0] << 8) | in_u8code[1])) // 查询地址码
		{

			switch (sFW433_t.Receiver_handle.Command_code)
			{
			case CH1:
				// 处理CH1指令
				// 00 00 00 00 00 00 00 01
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x01;
				break;
			case CH2:
				// 处理CH2指令
				// 00 00 00 00 00 00 00 02
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x02;
				break;
			case CH3:
				// 处理CH3指令
				// 00 00 00 00 00 00 00 03
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x03;
				break;
			case CH4:
				// 处理CH4指令
				// 00 00 00 00 00 00 00 04
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x04;
				break;
			case TEMP_UP:
				// 处理温度加10指令
				// 00 0A 00 00 00 00 00 05
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x0A;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x05;
				break;
			case TEMP_DOWN:
				// 处理温度减10指令
				// 00 0A 00 00 00 00 00 06
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x0A;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x06;
				break;
			case AIR_UP:
				// 处理风量加10指令
				// 0A 00 00 00 00 00 00 07
				dat_433.usart433_data.DATA_VAL_1_433 = 0x0A;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x07;
				break;
			case AIR_DOWN:
				// 处理风量减10指令
				// 0A 00 00 00 00 00 00 08
				dat_433.usart433_data.DATA_VAL_1_433 = 0x0A;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x08;
				break;
			case COLD_AIR_MODE:
				// 处理冷风模式指令
				// 00 00 00 00 00 00 00 09
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x09;
				break;
			case NORMAL_AIR_MODE:
				// 处理普通风模式指令
				// 00 00 00 00 00 00 00 0A
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x0A;
				break;
			case SLEEP_STAND:
				// 处理睡眠状态指令
				// 00 00 00 00 00 00 00 0B
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x0B;
				break;
			case CURVE_INTERFACE:
				// 处理曲线界面指令
				// 00 00 00 00 00 00 00 0E
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x0E;
				break;
			case NUMERICAL_INTERFACE:
				// 处理数字界面指令
				// 00 00 00 00 00 00 00 0F
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x0F;
				break;
			case FAHRENHEIT:
				// 处理华氏温度指令
				// 00 00 00 00 00 00 00 10
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x10;
				break;
			case CELSIUS:
				// 处理摄氏温度指令
				// 00 00 00 00 00 00 00 11
				dat_433.usart433_data.DATA_VAL_1_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_2_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_3_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_4_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_5_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_6_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_7_433 = 0x00;
				dat_433.usart433_data.DATA_VAL_8_433 = 0x11;
				break;
			case CONFIRM:
				break;
			default:
				break;
			}
			data_433_buffer[0] = 0x00;
			data_433_buffer[1] = 0x00;
			data_433_buffer[2] = 0x00;
			uint32_t checksum_sum[8] = {
				dat_433.usart433_data.DATA_VAL_1_433,
				dat_433.usart433_data.DATA_VAL_2_433,
				dat_433.usart433_data.DATA_VAL_3_433,
				dat_433.usart433_data.DATA_VAL_4_433,
				dat_433.usart433_data.DATA_VAL_5_433,
				dat_433.usart433_data.DATA_VAL_6_433,
				dat_433.usart433_data.DATA_VAL_7_433,
				dat_433.usart433_data.DATA_VAL_8_433};

			// 计算校验和
			uint32_t crc_433 = crc_block_calculate(checksum_sum, 8);
			crc_data_reset();

			// 将CRC32校验码分成4个字节
			dat_433.usart433_data.CHECKSUM_1_433 = (crc_433 >> 24) & 0xFF;
			dat_433.usart433_data.CHECKSUM_2_433 = (crc_433 >> 16) & 0xFF;
			dat_433.usart433_data.CHECKSUM_3_433 = (crc_433 >> 8) & 0xFF;
			dat_433.usart433_data.CHECKSUM_4_433 = crc_433 & 0xFF;

			// 填充包头
			dat_433.usart433_data.DATAHEAD_433 = 0xD1; // 包头
			// 填充通用指令和指令使用
			dat_433.usart433_data.UNIVERSAL_COMMAND_433 = 0x01; // 通用指令
			dat_433.usart433_data.COMMAND_USE_433 = 0x06;		// 指令使用
			// 填充地址
			dat_433.usart433_data.ADDR_H_433 = 0x00; // 地址高字节
			dat_433.usart433_data.ADDR_L_433 = 0x07; // 地址低字节
			// 填充数据长度
			dat_433.usart433_data.DATA_LENGTH_H_433 = 0x00; // 数据长度高字节
			dat_433.usart433_data.DATA_LENGTH_L_433 = 0x08; // 数据长度低字节
			// 填充包尾
			dat_433.usart433_data.DATAEND_433 = 0xF0; // 包尾2105

			sFW433_t.Receiver_handle.usart_send_ready_433_flag = true; // 数据准备好，可以发送
			sFW433_t.Receiver_handle.usart_send_finish_433_flag = false;

			usart1_send_byte(dat_433.usart433_buf, sizeof(dat_433.usart433_buf));
		}
		else
		{
			// 地址不正确不进行解码处理
		}
	}
}