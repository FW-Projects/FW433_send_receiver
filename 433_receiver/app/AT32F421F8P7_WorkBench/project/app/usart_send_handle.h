#ifndef __USART_SEND_HANDLE_H
#define __USART_SEND_HANDLE_H

#include "at32f421.h"
#include <stdbool.h>


#define USART_SEND_HANDLE_TIME 5

void usart_send_handle(void);
//void usart_receiver_handle(void);
void usart1_send_byte(u8 *p,u16 length);




#endif