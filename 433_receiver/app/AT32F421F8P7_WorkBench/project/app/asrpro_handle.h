#ifndef __ASRPRO_HANDLE_H
#define __ASRPRO_HANDLE_H

#include "at32f421.h"
#include <stdbool.h>
#define VOICE_HANDLE_TIME 10

typedef struct
{
    uint8_t DATAHEAD;          // ��ͷ
    uint8_t UNIVERSAL_COMMAND; // ͨ��ָ��
    uint8_t COMMAND_USE;       // ָ��ʹ��

    uint8_t ADDR_H; // ��ַ���ֽ�
    uint8_t ADDR_L; // ��ַ���ֽ�

    uint8_t DATA_LENGTH_H; // ���ݳ��ȸ��ֽ�
    uint8_t DATA_LENGTH_L; // ���ݳ��ȵ��ֽ�

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

    uint8_t DATAEND; // ��β

} UsartAsrproData; // ��ȥ��ͷ��βУ����

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