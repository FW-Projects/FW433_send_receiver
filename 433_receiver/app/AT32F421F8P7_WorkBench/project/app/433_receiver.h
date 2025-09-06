#ifndef __433_RECEIVER_H
#define __433_RECEIVER_H

#include "at32f421.h"
#include <stdbool.h>


#define TASK_433_TIME 5

//static uint32_t  valueTmp = 0;    //接收的数据
//static bool receive_flag = 0;      //数据接收完毕标志

typedef struct
{
    uint8_t DATAHEAD_433;          // 包头
    uint8_t UNIVERSAL_COMMAND_433; // 通用指令
    uint8_t COMMAND_USE_433;       // 指令使用

    uint8_t ADDR_H_433; // 地址高字节
    uint8_t ADDR_L_433; // 地址低字节

    uint8_t DATA_LENGTH_H_433; // 数据长度高字节
    uint8_t DATA_LENGTH_L_433; // 数据长度高字节

    /* data_value */
    uint8_t DATA_VAL_1_433;
    uint8_t DATA_VAL_2_433;
    uint8_t DATA_VAL_3_433;
    uint8_t DATA_VAL_4_433;
    uint8_t DATA_VAL_5_433;
    uint8_t DATA_VAL_6_433;
    uint8_t DATA_VAL_7_433;
    uint8_t DATA_VAL_8_433;
	uint8_t DATA_NO_1_433;
	uint8_t DATA_NO_2_433;
    uint8_t CHECKSUM_1_433;
    uint8_t CHECKSUM_2_433;
    uint8_t CHECKSUM_3_433;
    uint8_t CHECKSUM_4_433;

    uint8_t DATAEND_433;   // 包尾

} Usart433Data;

union UNION_433
{
    Usart433Data usart433_data;
    uint8_t usart433_buf[22];
    /* data */
};


 void recevier_handle(void);
 void right_code_handle(uint8_t *in_u8_code);
 void decode_handle(uint8_t *in_u8code);




#endif