
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
      // 判断指令
      if (Asrpro_Rx_buffer[0] == 0x00 && Asrpro_Rx_buffer[1] == 0x01) // 播放语音
      {
         switch (Asrpro_Rx_buffer[2])
         {
            // 去掉包头包尾
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
            // 00 0A 00 00 00 00 00 05 温度加10
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
            // 00 0A 00 00 00 00 00 06 温度减10
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
            // 0A 00 00 00 00 00 00 07 风量加10
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
            // 0A 00 00 00 00 00 00 08 风量减10
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
            // 00 00 00 00 00 00 00 09 冷风模式
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
            // 00 00 00 00 00 00 00 0A 普通风模式
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
            // 00 00 00 00 00 00 00 0E 曲线界面
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
            // 00 00 00 00 00 00 00 0F 数字界面
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
            // 00 00 00 00 00 00 00 10 华氏温度
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
            // 00 00 00 00 00 00 00 11 摄氏温度
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
			 // 00 00 00 00 00 00 00 12 切换手柄
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
         // 清除接收数据缓存区
         Asrpro_Rx_buffer[0] = 0x00;
         Asrpro_Rx_buffer[1] = 0x00;
         Asrpro_Rx_buffer[2] = 0x00;
		 
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
		 //填充无用数据
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
		 
          usart1_send_byte(dat.asrpro_buf, sizeof(dat.asrpro_buf));
      }
//   }
}
