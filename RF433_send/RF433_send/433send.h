#ifndef __433_SEND_H
#define __433_SEND_H


extern uint16_t set_433time_buf[]; // ����433���͵�ƽʱ��


typedef struct st_witty433
{
	unsigned int StartLevelTime_H;		//��ʼ�ߵ�ƽʱ��
	unsigned int StartLevelTime_L;		//��ʼ�͵�ƽʱ��
	
	unsigned int ZeroLevelTime_H;		//0�ߵ�ƽʱ��
	unsigned int ZeroLevelTime_L;		//0�͵�ƽʱ��
	
	unsigned int OneLevelTime_H;		//1�ߵ�ƽʱ��
	unsigned int OneLevelTime_L;		//1�͵�ƽʱ��
	
	unsigned int EndLevelTime_H;		//�����ߵ�ƽʱ��
	unsigned int EndLevelTime_L;		//�����͵�ƽʱ��
	
	unsigned char *Addr;				//433��ַ��
	unsigned int AddrBitNum;			//433��ַbit��
	
	unsigned char *SendData;			//433���ݶ�
	unsigned int SendDataBitNum;		//433����bit��
	
	unsigned char SendNumber;			//�������ʹ���
	
	void (*delay_433)(unsigned int us);		//433��ʱ����
	
}Witty433;


void Witty433_Init(unsigned int set_level_buf[8]);


void SetStartLevelTime_433(unsigned int time_H,unsigned int time_L);
void SetEndLevelTime_433(unsigned int time_H,unsigned int time_L);
void SetZeroLevelTime_433(unsigned int time_H,unsigned int time_L);
void SetOneLevelTime_433(unsigned int time_H,unsigned int time_L);


void SetAddr_433(unsigned char *addr,unsigned int addrBitLen);
void SetSendNumber_433(unsigned char sendNumber);
void SetSendData_433(unsigned char *sendData,unsigned int sendDataBitLen);


//void SendInput_433(unsigned char *data,unsigned int dataBitNum,unsigned char sendNum);
void StartSend_433(uint16_t in_addr2, uint8_t in_dat); // �ȴ��뷢�Ͳ������ٷ���
void StartSend_433_long(uint16_t in_addr3, uint8_t in_dat,uint8_t in_num);// ���Ͷ��433�ź�
void SendStart_433(void);
void SendAddr(uint16_t in_addr1);
void SendData(uint8_t in_dat1);
void SendEnd_433(void);


void SendBit0_433(void);
void SendBit1_433(void);
void SendBit_433(unsigned char byte,unsigned char bitNum);
#endif
