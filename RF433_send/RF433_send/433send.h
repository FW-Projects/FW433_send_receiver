#ifndef __433_SEND_H
#define __433_SEND_H


extern uint16_t set_433time_buf[]; // 设置433发送电平时间


typedef struct st_witty433
{
	unsigned int StartLevelTime_H;		//起始高电平时间
	unsigned int StartLevelTime_L;		//起始低电平时间
	
	unsigned int ZeroLevelTime_H;		//0高电平时间
	unsigned int ZeroLevelTime_L;		//0低电平时间
	
	unsigned int OneLevelTime_H;		//1高电平时间
	unsigned int OneLevelTime_L;		//1低电平时间
	
	unsigned int EndLevelTime_H;		//结束高电平时间
	unsigned int EndLevelTime_L;		//结束低电平时间
	
	unsigned char *Addr;				//433地址段
	unsigned int AddrBitNum;			//433地址bit数
	
	unsigned char *SendData;			//433数据段
	unsigned int SendDataBitNum;		//433数据bit数
	
	unsigned char SendNumber;			//连续发送次数
	
	void (*delay_433)(unsigned int us);		//433延时函数
	
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
void StartSend_433(uint16_t in_addr2, uint8_t in_dat); // 先传入发送参数，再发送
void StartSend_433_long(uint16_t in_addr3, uint8_t in_dat,uint8_t in_num);// 发送多次433信号
void SendStart_433(void);
void SendAddr(uint16_t in_addr1);
void SendData(uint8_t in_dat1);
void SendEnd_433(void);


void SendBit0_433(void);
void SendBit1_433(void);
void SendBit_433(unsigned char byte,unsigned char bitNum);
#endif
