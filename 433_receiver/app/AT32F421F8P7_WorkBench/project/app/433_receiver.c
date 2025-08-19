
#include "wk_system.h"
#include "at32f421.h"
#include "433_receiver.h"
#include "FW433_handle.h"
#include "at32f421_int.h"
#include "usart_send_handle.h"

/*
 * SHUT = P4 ^ 4;   //433M SHUT�ӿ� ���͵�ƽ����
 * de = P2 ^ 2;	    //433M DO�ӿ� �� �ⲿ�жϽӿ�
 */

void right_code_handle(uint8_t *in_u8_code);
void decode_handle(uint8_t *in_u8code);
/*
 * @brief  433M���մ�����
 * @param  none
 * @retval none
 *
 * �������ݵĲ��裺
 * 1.��ѯ����״̬���������ɹ�����������״̬���������ʧ�ܣ��򲻽��н��մ�������״̬Right_code_flag
 * 2.����״̬Right_code_flag=0ʱ��ʱ�̲�ѯ24bit�ĺ�8λ�����룬���������=0xff����ʼ���룬��¼16bit��ַ��
 * 3.����״̬Right_code_flag=1ʱ����ʼ���봦��ָ��
 */
void recevier_handle(void)
{
	if (sFW433_t.Receiver_handle.Right_code_flag == false)
	{
		/* ���봦�� */

		right_code_handle(data_433_buffer);
	}
	else
	{
		/* ���봦�� */

		decode_handle(data_433_buffer);
	}
}

void right_code_handle(uint8_t *in_u8_code)
{
	static uint8_t right_code_time = 0;
	if (in_u8_code[2] == RIGHT_CODE) // ����ָ��
	{
		right_code_time++;
		if (right_code_time > 30) // 30֡����
		{
			right_code_time = 0;
			sFW433_t.Receiver_handle.Right_code_flag = TRUE;							  // ����ɹ�
			sFW433_t.Receiver_handle.Address_code = (in_u8_code[0] << 8) | in_u8_code[1]; // �����ַ��
		}
	}
}

void decode_handle(uint8_t *in_u8code)
{
	union UNION_433 dat_433;
	sFW433_t.Receiver_handle.Command_code = in_u8code[2];
	if (sFW433_t.Receiver_handle.Command_code == CLEAR_CODE)
	{
		// ������� ����������ƥ��ң��
		sFW433_t.Receiver_handle.Right_code_flag = false;
		sFW433_t.Receiver_handle.Address_code = 0x00;
	}
	else
	{
		if (sFW433_t.Receiver_handle.Address_code == ((in_u8code[0] << 8) | in_u8code[1])) // ��ѯ��ַ��
		{

			switch (sFW433_t.Receiver_handle.Command_code)
			{
			case CH1:
				// ����CH1ָ��
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
				// ����CH2ָ��
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
				// ����CH3ָ��
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
				// ����CH4ָ��
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
				// �����¶ȼ�10ָ��
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
				// �����¶ȼ�10ָ��
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
				// ���������10ָ��
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
				// ���������10ָ��
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
				// �������ģʽָ��
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
				// ������ͨ��ģʽָ��
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
				// ����˯��״ָ̬��
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
				// �������߽���ָ��
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
				// �������ֽ���ָ��
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
				// �������¶�ָ��
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
				// ���������¶�ָ��
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

			// ����У���
			uint32_t crc_433 = crc_block_calculate(checksum_sum, 8);
			crc_data_reset();

			// ��CRC32У����ֳ�4���ֽ�
			dat_433.usart433_data.CHECKSUM_1_433 = (crc_433 >> 24) & 0xFF;
			dat_433.usart433_data.CHECKSUM_2_433 = (crc_433 >> 16) & 0xFF;
			dat_433.usart433_data.CHECKSUM_3_433 = (crc_433 >> 8) & 0xFF;
			dat_433.usart433_data.CHECKSUM_4_433 = crc_433 & 0xFF;

			// ����ͷ
			dat_433.usart433_data.DATAHEAD_433 = 0xD1; // ��ͷ
			// ���ͨ��ָ���ָ��ʹ��
			dat_433.usart433_data.UNIVERSAL_COMMAND_433 = 0x01; // ͨ��ָ��
			dat_433.usart433_data.COMMAND_USE_433 = 0x06;		// ָ��ʹ��
			// ����ַ
			dat_433.usart433_data.ADDR_H_433 = 0x00; // ��ַ���ֽ�
			dat_433.usart433_data.ADDR_L_433 = 0x07; // ��ַ���ֽ�
			// ������ݳ���
			dat_433.usart433_data.DATA_LENGTH_H_433 = 0x00; // ���ݳ��ȸ��ֽ�
			dat_433.usart433_data.DATA_LENGTH_L_433 = 0x08; // ���ݳ��ȵ��ֽ�
			// ����β
			dat_433.usart433_data.DATAEND_433 = 0xF0; // ��β2105

			sFW433_t.Receiver_handle.usart_send_ready_433_flag = true; // ����׼���ã����Է���
			sFW433_t.Receiver_handle.usart_send_finish_433_flag = false;

			usart1_send_byte(dat_433.usart433_buf, sizeof(dat_433.usart433_buf));
		}
		else
		{
			// ��ַ����ȷ�����н��봦��
		}
	}
}