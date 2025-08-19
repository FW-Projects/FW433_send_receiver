#include "SN8F5702.H"
#include "intrins.h"
#include "delayms.h"
#include "433send.h"

/*
 * name : 433�źŷ���
 * 433���͹��̣� 1.��ƽʱ������ Witty433_Init(unsigned int set_level_buf[8]) -->
 *              2.�������ݺʹ������� SendInput_433(unsigned char *data,unsigned int dataBitNum,unsigned char sendNum) -->
 *              3.���� StartSend_433()
 * 433�Զ������ݣ�433�ĸ�����ƽʱ�䣬433�ĵ�ַ�룬433�Ŀ����룬433�ķ��ʹ������û��Զ��塣
 */

#define Data_Send_H 1
#define Data_Send_L 0

sbit data_send = P1 ^ 0;

static Witty433 witty433;


uint16_t set_433time_buf[] = {120, 120, 12,   4,    4,    12,   4,    13}; // ����433���͵�ƽʱ��
                            /*12ms 12ms 1.2ms 0.4ms 0.4ms 1.2ms 0.4ms 1.3ms

//uint16_t set_433time_buf[] = {120, 120, 120, 120,120,120,120,120}; // ����433���͵�ƽʱ��


/**********************************��ƽʱ��������ó�ʼ�����Զ��岿�֣�************************************/
// #define delay_us_433 delay_us(1)                                                  // ����433΢����ʱ�������Զ��岿�֣�
// #define delay_ms_433 delay_ms(1)                                                  // ����433������ʱ�������Զ��岿�֣�
// #define delay_long_us delay_us(10)                                                // ����433����ʱ�������Զ��岿�֣�


void delay_long_us(unsigned int long_us)
{

        delay_us(long_us);
}
void delay_long_ms(unsigned int long_ms)
{
        delay_ms(long_ms);
}

void Witty433_Init(unsigned int set_level_buf[8]) // ���set_level_buf[8]���鱣����Ǹ�����ƽʱ�䣬��λ��us
{
        SetStartLevelTime_433(set_level_buf[0], set_level_buf[1]); // ������ʼ�� �� �� ��ƽʱ��
        SetOneLevelTime_433(set_level_buf[2], set_level_buf[3]);   // ����bit1   �� �� ��ƽʱ��
        SetZeroLevelTime_433(set_level_buf[4], set_level_buf[5]);  // ����bit0   �� �� ��ƽʱ��
        SetEndLevelTime_433(set_level_buf[6], set_level_buf[7]);   // ���ý����� �� �� ��ƽʱ��

        witty433.delay_433 = delay_long_us;
}

/************************************* 433��ƽʱ��������ú��� ****************************************/

/* ������ʼ���ƽʱ�� */
void SetStartLevelTime_433(unsigned int time_H, unsigned int time_L)
{
        witty433.StartLevelTime_H = time_H;
        witty433.StartLevelTime_L = time_L;
}

/* ���ý������ƽʱ�� */
void SetEndLevelTime_433(unsigned int time_H, unsigned int time_L)
{
        witty433.EndLevelTime_H = time_H;
        witty433.EndLevelTime_L = time_L;
}

/* ����bit0��ƽʱ�� */
void SetZeroLevelTime_433(unsigned int time_H, unsigned int time_L)
{
        witty433.ZeroLevelTime_H = time_H;
        witty433.ZeroLevelTime_L = time_L;
}

/* ����bit1��ƽʱ�� */
void SetOneLevelTime_433(unsigned int time_H, unsigned int time_L)
{
        witty433.OneLevelTime_H = time_H;
        witty433.OneLevelTime_L = time_L;
}

/******************************* 433���Ͳ������ú��� ****************************************/

/* ���õ�ַ�� */
//void SetAddr_433(unsigned char *addr, unsigned int addrBitNum)
//{
//        witty433.Addr = addr;
//        witty433.AddrBitNum = addrBitNum;
//}

///* ���������� */
//void SetSendData_433(unsigned char *sendData, unsigned int sendDataBitNum)
//{
//        witty433.SendData = sendData;
//        witty433.SendDataBitNum = sendDataBitNum;
//}

///* �����������ʹ��� */
//void SetSendNumber_433(unsigned char sendNumber)
//{
//        witty433.SendNumber = sendNumber;
//}

/******************************* ���ͳ�ʼ������ ****************************************/

/* ���뷢�Ͳ�������--�����򼰷��ʹ��� */
//void SendInput_433(unsigned char *data, unsigned int dataBitNum, unsigned char sendNum)
//{
//        SetSendNumber_433(sendNum);        // ����sendNum�������ʹ���,��ͬ���̵Ŀ��ܲ�һ������Ҫע��
//        SetSendData_433(data, dataBitNum); // data�����Ǿ���Ŀ�������,dataBitNum�����ݵ�λ��
//}



/************************************************************************************/

/* ������ʼ�� */
void SendStart_433()
{
        data_send = Data_Send_H;
        witty433.delay_433(witty433.StartLevelTime_H);

        data_send = Data_Send_L;
        witty433.delay_433(witty433.StartLevelTime_L);
}

/* ���͵�ַ�� */
void SendAddr(uint16_t in_addr1)
{
        uint8_t addr_h = (in_addr1 >> 8) & 0xFF; // ��ȡ��ַ���λ
        uint8_t addr_l = in_addr1 & 0xFF;        // ��ȡ��ַ���λ

        SendBit_433(addr_h, 8); // ��д��λ
        SendBit_433(addr_l, 8); // ��д��λ
}

/* ���������� */
void SendData(uint8_t in_dat1)
{
        SendBit_433(in_dat1, 8);
}

/* ���ͽ����� */
void SendEnd_433()
{
        data_send = Data_Send_H;
        witty433.delay_433(witty433.EndLevelTime_H);

        data_send = Data_Send_L;
        witty433.delay_433(witty433.EndLevelTime_L);
}

/* ����bit0 */
void SendBit0_433()
{
        data_send = Data_Send_H;
        witty433.delay_433(witty433.ZeroLevelTime_H);

        data_send = Data_Send_L;
        witty433.delay_433(witty433.ZeroLevelTime_L);
}

/* ����bit1 */
void SendBit1_433()
{
        data_send = Data_Send_H;
        witty433.delay_433(witty433.OneLevelTime_H);

        data_send = Data_Send_L;
        witty433.delay_433(witty433.OneLevelTime_L);
}

/* ����16��������--1Byte */
//void SendHex_433(unsigned char byte)
//{
//        SendBit_433(byte, 8);
//}

/* ����bit����--���������ݼ�����������bit��0~8 */

void SendBit_433(unsigned char byte, unsigned char bitNum)
{
       uint8_t a = 0;
        for (a = 0; a < bitNum; a++)
        {
                if (byte & 0x80)
                {
                        SendBit1_433();
                }
                else
                {
                        SendBit0_433();
                }
                byte <<= 1;
				_nop_();
        }
}


/*******************************����һ��433�ź�***************************************/

void StartSend_433(uint16_t in_addr2, uint8_t in_dat) // �ȴ��뷢�Ͳ������ٷ���
{
        SendStart_433();
        SendAddr(in_addr2);
        SendData(in_dat);
        SendEnd_433();
}

/*******************************���Ͷ��433�ź�***************************************/

void StartSend_433_long(uint16_t in_addr3, uint8_t in_dat,uint8_t in_num) // ���Ͷ��433�ź�
{
	uint8_t b = 0;
	for (b = 0; b < in_num; b++)
	{
			SendStart_433();
			SendAddr(in_addr3);// ���͵�ַ��
			SendData(in_dat);// ����������
	}
	SendEnd_433();
}
