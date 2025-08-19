#include "FW433_handle.h"

FW433_Handle sFW433_t;

uint8_t FW433_Init(FW433_Handle *FW433)
{
	FW433->Receiver_handle.Right_code_flag = false;
	FW433->Receiver_handle.Address_code = 0x0000;			   // ��ʼ����ַ��Ϊ0
	FW433->Receiver_handle.Command_code = 0x00;				   // ��ʼ��������Ϊ0
	FW433->Receiver_handle.usart_send_finish_433_flag = false; // ��ʼ������433��־λΪfalse
	FW433->Receiver_handle.usart_send_ready_433_flag = false;
	FW433->ASRPRO_handle.usart_send_asrpro_flag = false;
	FW433->buf[0] = 0x00;
	FW433->buf[1] = 0x00;
	FW433->buf[2] = 0x00;

	return 0;
}
