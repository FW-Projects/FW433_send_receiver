
#include "wk_system.h"
#include "at32f421.h"
#include "FW433_handle.h"
#include "asrpro_handle.h"
#include "usart_send_handle.h"

uint16_t Asrpro_Rx_buffer[3] = {0, 0, 0};
bool Rx_usart2_finish_flag = 0;
void asrpro_Handle(void)
{
   union UNION_ASRPRO dat;
   uint32_t data_valH = 0;
   uint32_t data_valL = 0;
//   if (Rx_usart2_finish_flag == true)
//   {
//      Rx_usart2_finish_flag = false;
      // �ж�ָ��
      if (Asrpro_Rx_buffer[0] == 0x00 && Asrpro_Rx_buffer[1] == 0x01) // ��������
      {
         switch (Asrpro_Rx_buffer[2])
         {
            // ȥ����ͷ��β
         case CH1:
            // 00 00 00 00 00 00 00 01
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x01;

            break;
         case CH2:
            // 00 00 00 00 00 00 00 02
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x02;

            break;
         case CH3:
            // 00 00 00 00 00 00 00 03
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x03;

            break;
         case CH4:
            // 00 00 00 00 00 00 00 04
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x04;

            break;
         case TEMP_UP:
            // 00 0A 00 00 00 00 00 05 �¶ȼ�10
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x0A;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x05;

            break;
         case TEMP_DOWN:
            // 00 0A 00 00 00 00 00 06 �¶ȼ�10
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x0A;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x06;

            break;
         case AIR_UP:
            // 0A 00 00 00 00 00 00 07 ������10
            dat.asrpro_data.DATA_VAL_1 = 0x0A;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x07;
            break;
         case AIR_DOWN:
            // 0A 00 00 00 00 00 00 08 ������10
            dat.asrpro_data.DATA_VAL_1 = 0x0A;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x08;
            break;

         case COLD_AIR_MODE:
            // 00 00 00 00 00 00 00 09 ���ģʽ
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x09;
            break;
         case NORMAL_AIR_MODE:
            // 00 00 00 00 00 00 00 0A ��ͨ��ģʽ
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x0A;
            break;
         case CURVE_INTERFACE:
            // 00 00 00 00 00 00 00 0E ���߽���
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x0E;
            break;
         case NUMERICAL_INTERFACE:
            // 00 00 00 00 00 00 00 0F ���ֽ���
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x0F;
            break;
         case FAHRENHEIT:
            // 00 00 00 00 00 00 00 10 �����¶�
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x10;
            break;
         case CELSIUS:
            // 00 00 00 00 00 00 00 11 �����¶�
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x11;
            break;
		 case SWITCH_HANDLE:
			 // 00 00 00 00 00 00 00 12 �л��ֱ�
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x12;
            break;
         default:
            break;
         }
         // ����������ݻ�����
         Asrpro_Rx_buffer[0] = 0x00;
         Asrpro_Rx_buffer[1] = 0x00;
         Asrpro_Rx_buffer[2] = 0x00;
		 
		 // ����ͷ
         dat.asrpro_data.DATAHEAD = 0xD1; // ��ͷ
         // ���ͨ��ָ���ָ��ʹ��
         dat.asrpro_data.UNIVERSAL_COMMAND = 0x01; // ͨ��ָ��
         dat.asrpro_data.COMMAND_USE = 0x06;       // ָ��ʹ��
         // ����ַ
         dat.asrpro_data.ADDR_H = 0x00; // ��ַ���ֽ�
         dat.asrpro_data.ADDR_L = 0x06; // ��ַ���ֽ�
         // ������ݳ���
         dat.asrpro_data.DATA_LENGTH_H = 0x00; // ���ݳ��ȸ��ֽ�
         dat.asrpro_data.DATA_LENGTH_L = 0x0A; // ���ݳ��ȵ��ֽ�
		 //�����������
		dat.asrpro_data.DATA_NO_1 = 0x00; 
		dat.asrpro_data.DATA_NO_2 = 0x00; 
         // ����β
         dat.asrpro_data.DATAEND = 0xF0; // ��β
		 
         // ����CRC32У����
		 
		 uint32_t checksum[4];
		 checksum[0] = (uint32_t)((dat.asrpro_data.UNIVERSAL_COMMAND << 24) | (dat.asrpro_data.COMMAND_USE << 16) | (dat.asrpro_data.ADDR_H << 8) | (dat.asrpro_data.ADDR_L));
		 checksum[1] = (uint32_t)((dat.asrpro_data.DATA_LENGTH_H << 24) | (dat.asrpro_data.DATA_LENGTH_L << 16) | (dat.asrpro_data.DATA_VAL_1 << 8) | (dat.asrpro_data.DATA_VAL_2));
         checksum[2] = (uint32_t)((dat.asrpro_data.DATA_VAL_3 << 24) | (dat.asrpro_data.DATA_VAL_4 << 16) | (dat.asrpro_data.DATA_VAL_5 << 8) | (dat.asrpro_data.DATA_VAL_6));
		 checksum[3] = (uint32_t)((dat.asrpro_data.DATA_VAL_7 << 24) | (dat.asrpro_data.DATA_VAL_8 << 16) | (0x00 << 8) | (0x00));

		 
         uint32_t crc = crc_block_calculate(checksum, 4);
         crc_data_reset();
         // ��CRC32У����ֳ�4���ֽ�
         dat.asrpro_data.CHECKSUM_1 = (crc >> 24) & 0xFF;
         dat.asrpro_data.CHECKSUM_2 = (crc >> 16) & 0xFF;
         dat.asrpro_data.CHECKSUM_3 = (crc >> 8) & 0xFF;
         dat.asrpro_data.CHECKSUM_4 = crc & 0xFF;
         
		 sFW433_t.Receiver_handle.led_times = 0x0a;
		 
          usart1_send_byte(dat.asrpro_buf, sizeof(dat.asrpro_buf));
      }
//   }
}
