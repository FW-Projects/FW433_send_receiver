#ifndef __CRC32_H
#define __CRC32_H

#include "at32f421.h"

#define CRC32_HANDLE_TIME 10

uint32_t CRC32_Calculate(uint8_t *pData, uint32_t length);

#endif