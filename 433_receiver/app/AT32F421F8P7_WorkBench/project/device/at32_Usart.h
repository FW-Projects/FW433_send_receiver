#ifndef __AT32_USART_H__
#define __AT32_USART_H__

#include "at32f421.h"
#include "util_queue.h"
#include "userconfig.h"

#define USART_RXFLAG_IDLE 	0
#define USART_RXFLAG_BUSY 	1
#define USART_RXFLAG_FINISH 2
#define USART_TXFLAG_IDLE 	0
#define USART_TXFLAG_BUSY 	1
#define USART_DELAYTIME 4


typedef struct
{
    util_queue_t tRXQueue;
    uint8_t chRXFinishTime;
    uint8_t chRXFlag;

    util_queue_t tTXQueue;
    uint8_t chTXFinishTime;
    uint8_t chTXFlag;

    usart_type *ptUsart;
} usartbuffer_t;

usartbuffer_t tUsart1Buffer;
usartbuffer_t tUsart2Buffer;
usartbuffer_t tUsart3Buffer;
usartbuffer_t tUart4Buffer;
usartbuffer_t tUart5Buffer;

void BSP_UsartInit(void);

void USART1_TimeOutCounter(void);
void USART2_TimeOutCounter(void);
void USART3_TimeOutCounter(void);
void UART4_TimeOutCounter(void);
void UART5_TimeOutCounter(void);
uint16_t usart_sendData(uint8_t chUsartNum, uint8_t *pchSendData, uint16_t hwLength);
uint16_t usart_receiveData(uint8_t chUsartNum, uint8_t *pchReceiveData);

uint16_t bsp_UsartSendData(uint8_t *pchSendData,uint16_t hwLength);
uint16_t bsp_UsartReceiveData(uint8_t *pchReceiveData);
#endif
