#include "usart_send_handle.h"
#include "433_receiver.h"
#include "FW433_handle.h"
#include "asrpro_handle.h"
// #include "at32_Usart.h"
void usart1_send_byte(u8 *p, u16 length);
void usart_send_handle(void)
{
  union UNION_ASRPRO send_asrpro;
  union UNION_433 send_433;
  uint16_t usart_send_counter = 0;

  if (sFW433_t.Receiver_handle.usart_send_ready_433_flag == true && sFW433_t.Receiver_handle.usart_send_finish_433_flag == false)
  {
    //    usart_send_counter = usart_sendData(0, send_433.usart433_buf, sizeof(send_433.usart433_buf)); // ����433����
    //	  usart1_send_byte(send_433.usart433_buf,sizeof(send_433.usart433_buf));
    sFW433_t.Receiver_handle.usart_send_ready_433_flag = false;
    sFW433_t.Receiver_handle.usart_send_finish_433_flag = true; // ���ݷ������
  }
  else if (sFW433_t.ASRPRO_handle.usart_send_asrpro_flag == true)
  {
    //    usart_send_counter = usart_sendData(0, send_asrpro.asrpro_buf, sizeof(send_asrpro.asrpro_buf)); // ����ASRPRO����
    sFW433_t.ASRPRO_handle.usart_send_asrpro_flag = false; // �������
  }
  else if (sFW433_t.Receiver_handle.usart_send_finish_433_flag == false &&
           sFW433_t.ASRPRO_handle.usart_send_asrpro_flag == false)
  {
    // do nothing
  }
}

/*************************************************
 * ���������� USART1����
 * ��    ���� p--���͵������ַ��length--Ҫ���͵ĳ���
 * ��    �أ� ��
 *************************************************/
void usart1_send_byte(u8 *p, u16 length)
{
  while (length--)
  {
    while (usart_flag_get(USART1, USART_TDBE_FLAG) == RESET) // �ȴ���һ�����ݷ���ȥ
    {
    }
    usart_data_transmit(USART1, *p++); // ��һ���ֽ�
  }
}


