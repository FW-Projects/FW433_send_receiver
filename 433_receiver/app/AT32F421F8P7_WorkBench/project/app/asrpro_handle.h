#ifndef __ASRPRO_HANDLE_H
#define __ASRPRO_HANDLE_H

#include "at32f421.h"
#include <stdbool.h>
#define VOICE_HANDLE_TIME 10

typedef struct
{
    uint8_t DATAHEAD;          // 包头
    uint8_t UNIVERSAL_COMMAND; // 通用指令
    uint8_t COMMAND_USE;       // 指令使用

    uint8_t ADDR_H; // 地址高字节
    uint8_t ADDR_L; // 地址低字节

    uint8_t DATA_LENGTH_H; // 数据长度高字节
    uint8_t DATA_LENGTH_L; // 数据长度低字节

    uint8_t DATA_VAL_1;
    uint8_t DATA_VAL_2;
    uint8_t DATA_VAL_3;
    uint8_t DATA_VAL_4;
    uint8_t DATA_VAL_5;
    uint8_t DATA_VAL_6;
    uint8_t DATA_VAL_7;
    uint8_t DATA_VAL_8;

    uint8_t CHECKSUM_1;
    uint8_t CHECKSUM_2;
    uint8_t CHECKSUM_3;
    uint8_t CHECKSUM_4;

    uint8_t DATAEND; // 包尾

} UsartAsrproData; // 除去包头包尾校验码

union UNION_ASRPRO
{
    UsartAsrproData asrpro_data;
    uint8_t asrpro_buf[20];
    /* data */
};
extern uint16_t Asrpro_Rx_buffer[3];
extern bool Rx_usart2_finish_flag ;

void asrpro_handle(void);

#endif