#ifndef _FW433_HANDLE_H
#define _FW433_HANDLE_H
#include "at32f421.h"
#include "stdbool.h"

///* 10ms - 15ms     test_time = 14ms */
//#define StartLevelTime_H_MAX 45000
//#define StartLevelTime_H_MIN 30000

//#define StartLevelTime_L_MAX 45000
//#define StartLevelTime_L_MIN 30000


///* 0.4ms - 0.8ms   test_time = 0.6ms */ 
//#define ZeroLevelTime_H_MAX 2400
//#define ZeroLevelTime_H_MIN 1200

///* 1ms - 1.6ms     test_time = 1.4ms */
//#define ZeroLevelTime_L_MAX 4800
//#define ZeroLevelTime_L_MIN 3000

///* 1ms - 1.6ms     test_time = 1.4ms */
//#define OneLevelTime_H_MAX 4800
//#define OneLevelTime_H_MIN 3000

///* 0.4ms - 0.8ms   test_time = 0.6ms */
//#define OneLevelTime_L_MAX 2400
//#define OneLevelTime_L_MIN 1200


/* 10ms - 14ms     test_time = 12ms */
#define StartLevelTime_H_MAX 42000
#define StartLevelTime_H_MIN 30000
//#define StartLevelTime_H_MAX 60000
//#define StartLevelTime_H_MIN 0

#define StartLevelTime_L_MAX 42000
#define StartLevelTime_L_MIN 30000


/* 0.6ms - 1ms   test_time = 0.8ms */ 
#define ZeroLevelTime_H_MAX 3000
#define ZeroLevelTime_H_MIN 1800

/* 2.3ms - 2.7ms     test_time = 2.5ms */
#define ZeroLevelTime_L_MAX 8100
#define ZeroLevelTime_L_MIN 6900

/* 2.3ms - 2.7ms     test_time = 2.5ms */
#define OneLevelTime_H_MAX 8100
#define OneLevelTime_H_MIN 6900

/* 0.6ms - 1ms   test_time = 0.8ms */ 
#define OneLevelTime_L_MAX 3000
#define OneLevelTime_L_MIN 1800


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
    CURVE_INTERFACE = 0x0e,
    NUMERICAL_INTERFACE = 0x0f,
    FAHRENHEIT = 0x10,
    CELSIUS = 0x11,
	SWITCH_HANDLE = 0x12,
	SWITCH_HANDLE_433 = 0x09,
    RIGHT_CODE = 0xff,
	CLEAR_CODE = 0x0f,

} command_code_e;


typedef enum
{
    MOD1 = 0x01,
    MOD2 = 0x02,
    MOD3 = 0x03,
    MOD4 = 0x04,
	POWER = 0X05,
    COLD = 0x06,
    NORMAL = 0x07,
    CURVE = 0x08,
    NUMERICAL = 0x09,
    F = 0x0A,
    C = 0x0B,
	CHANGE_HANDLE = 0x0C,

} command_code_e_asrpro;

typedef struct
{
    command_code_e COMMAND_CODE;
	
    bool Right_code_flag;
    uint16_t Address_code; // 16bitµØÖ·Âë
    uint8_t Command_code;  // 8bit°´¼üÂë
    bool usart_send_finish_433_flag;
	bool usart_send_ready_433_flag;
	uint8_t led_times;

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
