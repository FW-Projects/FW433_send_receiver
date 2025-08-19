#include "crc32.h"
#include "at32f421_crc.h"
#include "wk_crc.h"

uint32_t CRC32_Calculate(uint8_t *pData, uint32_t length)
{
    //复位CRC计算器
    uint32_t crc = 0xFFFFFFFF; // CRC初始值

    //按32位字写入数据
    uint32_t *word_ptr = (uint32_t *)pData;
    uint32_t word_count = length / 4;


    for (uint32_t i = 0; i < word_count; i++)
    {
        CRC->dt = __REV(word_ptr[i]); // 字节序反转
    }

    //处理剩余的字节（非4的倍数）
    uint8_t *byte_ptr = (uint8_t *)(pData + word_count);
    uint32_t remaining_bytes = length % 4;

    if(remaining_bytes > 0)
    {
        uint32_t last_word = 0;
        for (uint32_t j = 0; j < remaining_bytes; j++)
        {
            last_word |= (byte_ptr[j] << (8 * j));
        }
        CRC->dt = last_word; 
    }

    //读取CRC结果
    return CRC->dt ^ 0xFFFFFFFF; // CRC结果取反
}