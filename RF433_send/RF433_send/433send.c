#include "SN8F5703.H"
#include "intrins.h"
#include "delayms.h"
#include "433send.h"

/*
 * name : 433信号发送
 * 433发送过程： 1.电平时间设置 Witty433_Init(unsigned int set_level_buf[8]) -->
 *              2.发送内容和次数设置 SendInput_433(unsigned char *data,unsigned int dataBitNum,unsigned char sendNum) -->
 *              3.发送 StartSend_433()
 * 433自定义内容：433的各个电平时间，433的地址码，433的控制码，433的发送次数由用户自定义。
 */

#define Data_Send_H 1
#define Data_Send_L 0

sbit data_send = P2 ^ 0;

static Witty433 witty433;


uint16_t set_433time_buf[] = {60,   60,  12,   4,    4,    12,   4,    12}; // 设置433发送电平时间

                            /*12ms 12ms 2.5ms 0.8ms 0.8ms 2.5ms 0.8ms 2.5ms

//uint16_t set_433time_buf[] = {120, 120, 120, 120,120,120,120,120}; // 设置433发送电平时间


/**********************************电平时间参数设置初始化（自定义部分）************************************/
// #define delay_us_433 delay_us(1)                                                  // 设置433微秒延时函数（自定义部分）
// #define delay_ms_433 delay_ms(1)                                                  // 设置433毫秒延时函数（自定义部分）
// #define delay_long_us delay_us(10)                                                // 设置433长延时函数（自定义部分）


void delay_long_us(unsigned int long_us)
{

        delay_us(long_us);
}
//void delay_long_ms(unsigned int long_ms)
//{
//        delay_ms(long_ms);
//}

void Witty433_Init(unsigned int set_level_buf[8]) // 这个set_level_buf[8]数组保存的是各个电平时间，单位是us
{
        SetStartLevelTime_433(set_level_buf[0], set_level_buf[1]); // 设置起始码 高 低 电平时间
        SetOneLevelTime_433(set_level_buf[2], set_level_buf[3]);   // 设置bit1   高 低 电平时间
        SetZeroLevelTime_433(set_level_buf[4], set_level_buf[5]);  // 设置bit0   高 低 电平时间
        SetEndLevelTime_433(set_level_buf[6], set_level_buf[7]);   // 设置结束码 高 低 电平时间

        witty433.delay_433 = delay_long_us;
}

/************************************* 433电平时间参数设置函数 ****************************************/

/* 设置起始码电平时间 */
void SetStartLevelTime_433(unsigned int time_H, unsigned int time_L)
{
        witty433.StartLevelTime_H = time_H;
        witty433.StartLevelTime_L = time_L;
}

/* 设置结束码电平时间 */
void SetEndLevelTime_433(unsigned int time_H, unsigned int time_L)
{
        witty433.EndLevelTime_H = time_H;
        witty433.EndLevelTime_L = time_L;
}

/* 设置bit0电平时间 */
void SetZeroLevelTime_433(unsigned int time_H, unsigned int time_L)
{
        witty433.ZeroLevelTime_H = time_H;
        witty433.ZeroLevelTime_L = time_L;
}

/* 设置bit1电平时间 */
void SetOneLevelTime_433(unsigned int time_H, unsigned int time_L)
{
        witty433.OneLevelTime_H = time_H;
        witty433.OneLevelTime_L = time_L;
}

/******************************* 433发送参数设置函数 ****************************************/

/* 设置地址码 */
//void SetAddr_433(unsigned char *addr, unsigned int addrBitNum)
//{
//        witty433.Addr = addr;
//        witty433.AddrBitNum = addrBitNum;
//}

///* 设置数据域 */
//void SetSendData_433(unsigned char *sendData, unsigned int sendDataBitNum)
//{
//        witty433.SendData = sendData;
//        witty433.SendDataBitNum = sendDataBitNum;
//}

///* 设置连续发送次数 */
//void SetSendNumber_433(unsigned char sendNumber)
//{
//        witty433.SendNumber = sendNumber;
//}

/******************************* 发送初始化函数 ****************************************/

/* 传入发送参数内容--数据域及发送次数 */
//void SendInput_433(unsigned char *data, unsigned int dataBitNum, unsigned char sendNum)
//{
//        SetSendNumber_433(sendNum);        // 设置sendNum连续发送次数,不同厂商的可能不一样，需要注意
//        SetSendData_433(data, dataBitNum); // data数组是具体的控制数据,dataBitNum是数据的位数
//}



/************************************************************************************/

/* 发送起始码 */
void SendStart_433()
{
        data_send = Data_Send_H;
        witty433.delay_433(witty433.StartLevelTime_H);

        data_send = Data_Send_L;
        witty433.delay_433(witty433.StartLevelTime_L);
}

/* 发送地址码 */
void SendAddr(uint16_t in_addr1)
{
        uint8_t addr_h = (in_addr1 >> 8) & 0xFF; // 获取地址码高位
        uint8_t addr_l = in_addr1 & 0xFF;        // 获取地址码低位

        SendBit_433(addr_h, 8); // 先写高位
        SendBit_433(addr_l, 8); // 先写地位
}

/* 发送数据域 */
void SendData(uint8_t in_dat1)
{
        SendBit_433(in_dat1, 8);
}

/* 发送结束码 */
void SendEnd_433()
{
        data_send = Data_Send_H;
        witty433.delay_433(witty433.EndLevelTime_H);

        data_send = Data_Send_L;
        witty433.delay_433(witty433.EndLevelTime_L);
}

/* 发送bit0 */
void SendBit0_433()
{
        data_send = Data_Send_H;
        witty433.delay_433(witty433.ZeroLevelTime_H);

        data_send = Data_Send_L;
        witty433.delay_433(witty433.ZeroLevelTime_L);
}

/* 发送bit1 */
void SendBit1_433()
{
        data_send = Data_Send_H;
        witty433.delay_433(witty433.OneLevelTime_H);

        data_send = Data_Send_L;
        witty433.delay_433(witty433.OneLevelTime_L);
}

/* 发送16进制数据--1Byte */
//void SendHex_433(unsigned char byte)
//{
//        SendBit_433(byte, 8);
//}

/* 发送bit数据--待发送数据及待发送数据bit数0~8 */

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


/*******************************发送一次433信号***************************************/

void StartSend_433(uint16_t in_addr2, uint8_t in_dat) // 先传入发送参数，再发送
{
        SendStart_433();
        SendAddr(in_addr2);
        SendData(in_dat);
        SendEnd_433();
}

/*******************************发送多次433信号***************************************/

void StartSend_433_long(uint16_t in_addr3, uint8_t in_dat,uint8_t in_num) // 发送多次433信号
{
	uint8_t b = 0;
	for (b = 0; b < in_num; b++)
	{
			SendStart_433();
			SendAddr(in_addr3);// 发送地址码
			SendData(in_dat);// 发送数据域
	}
	SendEnd_433();
}
