#include "crc32.h"
#include "at32f421_crc.h"
#include "wk_crc.h"

uint32_t CRC32_Calculate(uint8_t *pData, uint32_t length)
{
    //��λCRC������
    uint32_t crc = 0xFFFFFFFF; // CRC��ʼֵ

    //��32λ��д������
    uint32_t *word_ptr = (uint32_t *)pData;
    uint32_t word_count = length / 4;


    for (uint32_t i = 0; i < word_count; i++)
    {
        CRC->dt = __REV(word_ptr[i]); // �ֽ���ת
    }

    //����ʣ����ֽڣ���4�ı�����
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

    //��ȡCRC���
    return CRC->dt ^ 0xFFFFFFFF; // CRC���ȡ��
}