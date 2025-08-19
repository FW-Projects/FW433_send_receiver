
#include "wk_system.h"
#include "at32f421.h"
#include "FW433_handle.h"
#include "asrpro_handle.h"
#include "usart_send_handle.h"

uint16_t Asrpro_Rx_buffer[3] = {0, 0, 0};
bool Rx_usart2_finish_flag = 0;
void asrpro_handle(void)
{
   union UNION_ASRPRO dat;
   uint32_t data_valH = 0;
   uint32_t data_valL = 0;
   if (Rx_usart2_finish_flag == true)
   {
      Rx_usart2_finish_flag = false;
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
         case SLEEP_STAND:
            // 00 00 00 00 00 00 00 0B ˯��״̬
            dat.asrpro_data.DATA_VAL_1 = 0x00;
            dat.asrpro_data.DATA_VAL_2 = 0x00;
            dat.asrpro_data.DATA_VAL_3 = 0x00;
            dat.asrpro_data.DATA_VAL_4 = 0x00;
            dat.asrpro_data.DATA_VAL_5 = 0x00;
            dat.asrpro_data.DATA_VAL_6 = 0x00;
            dat.asrpro_data.DATA_VAL_7 = 0x00;
            dat.asrpro_data.DATA_VAL_8 = 0x0B;
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
         default:
            break;
         }
         // ����������ݻ�����
         Asrpro_Rx_buffer[0] = 0x00;
         Asrpro_Rx_buffer[1] = 0x00;
         Asrpro_Rx_buffer[2] = 0x00;
         // ����CRC32У����
         uint32_t checksum[8] = {
             dat.asrpro_data.DATA_VAL_1,
             dat.asrpro_data.DATA_VAL_2,
             dat.asrpro_data.DATA_VAL_3,
             dat.asrpro_data.DATA_VAL_4,
             dat.asrpro_data.DATA_VAL_5,
             dat.asrpro_data.DATA_VAL_6,
             dat.asrpro_data.DATA_VAL_7,
             dat.asrpro_data.DATA_VAL_8};
         uint32_t crc = crc_block_calculate(checksum, 8);
         crc_data_reset();
         // ��CRC32У����ֳ�4���ֽ�
         dat.asrpro_data.CHECKSUM_1 = (crc >> 24) & 0xFF;
         dat.asrpro_data.CHECKSUM_2 = (crc >> 16) & 0xFF;
         dat.asrpro_data.CHECKSUM_3 = (crc >> 8) & 0xFF;
         dat.asrpro_data.CHECKSUM_4 = crc & 0xFF;
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
         dat.asrpro_data.DATA_LENGTH_L = 0x08; // ���ݳ��ȵ��ֽ�
         // ����β
         dat.asrpro_data.DATAEND = 0xF0; // ��β
         usart1_send_byte(dat.asrpro_buf, sizeof(dat.asrpro_buf));
      }
   }
}
