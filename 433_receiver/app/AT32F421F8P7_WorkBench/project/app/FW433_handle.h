#ifndef _FW433_HANDLE_H
#define _FW433_HANDLE_H
#include "at32f421.h"
#include "stdbool.h"

/* 10ms - 15ms     test_time = 14ms */
#define StartLevelTime_H_MAX 45000
#define StartLevelTime_H_MIN 30000
#define StartLevelTime_L_MAX 45000
#define StartLevelTime_L_MIN 30000

/* 0.4ms - 0.8ms   test_time = 0.6ms */ 
#define ZeroLevelTime_H_MAX 2400
#define ZeroLevelTime_H_MIN 1200

/* 1ms - 1.6ms     test_time = 1.4ms */
#define ZeroLevelTime_L_MAX 4800
#define ZeroLevelTime_L_MIN 3000

/* 1ms - 1.6ms     test_time = 1.4ms */
#define OneLevelTime_H_MAX 4800
#define OneLevelTime_H_MIN 3000

/* 0.4ms - 0.8ms   test_time = 0.6ms */
#define OneLevelTime_L_MAX 2400
#define OneLevelTime_L_MIN 1200


//static uint32_t  valueTmp = 0;    //接收的数据
//static uint16_t  bitNums  = 0;    //接收数据的位数
//static uint8_t   state = 0;       //接收步骤
//static uint8_t   u8_value[3];     //存储接收的数据：3个8bit
//static bool receive_flag = 0;      //数据接收完毕标志
//static uint16_t holdTime = 0;
typedef enum
{
    NO_CODE = 0x00,
    CH1 = 0x01,
    CH2 = 0x02,
    CH3 = 0x03,
    CH4 = 0x04,
    TEMP_UP = 0x05,
    TEMP_DOWN = 0x06,
    AIR_UP = 0x07,
    AIR_DOWN = 0x08,
    COLD_AIR_MODE = 0x09,
    NORMAL_AIR_MODE = 0x0a,
    SLEEP_STAND = 0x0b,
    CURVE_INTERFACE = 0x0c,
    NUMERICAL_INTERFACE = 0x0d,
    FAHRENHEIT = 0x0e,
    CELSIUS = 0x0f,
    CONFIRM = 0x10,
    RIGHT_CODE = 0xff,
	CLEAR_CODE = 0x0f,

} command_code_e;

typedef struct
{
    command_code_e COMMAND_CODE;
    bool Right_code_flag;
    uint16_t Address_code; // 16bit地址码
    uint8_t Command_code;  // 8bit按键码
    bool usart_send_finish_433_flag;
	bool usart_send_ready_433_flag;
	

} receiver_433_e;

typedef struct
{
    bool Rx2_flag;
    bool usart_send_asrpro_flag;
    /* data */
} asrpro_handle_e;

typedef struct
{

    /* data */
} uasrt_data_e;

typedef struct
{
    receiver_433_e Receiver_handle;
    uasrt_data_e Uasrt_data_handle;
    asrpro_handle_e ASRPRO_handle;
	uint8_t buf[3];

} FW433_Handle;

extern FW433_Handle sFW433_t;

uint8_t FW433_Init(FW433_Handle *FWS2);

#endif
