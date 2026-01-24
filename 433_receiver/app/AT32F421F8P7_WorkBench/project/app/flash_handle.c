#include "flash_handle.h"
#include "FW433_handle.h"

uint16_t data_check(uint32_t address)
{
    static uint16_t data;
    data = flash_wred_halfword(address);

    if (data == 0xffff)
    {
        return FALSE;
    }
    else
    {
        return data;
    }
}

uint16_t data_check_len(uint32_t address, uint8_t len)
{
    volatile uint16_t data;
    uint8_t i;

    for (i = 0; i < len; i += DATA_SIZE)
    {
        data = flash_wred_halfword(address + i);

        if (data == 0xFFFF)
        {
            break;
        }
    }

    return data;
}

void FlashProc(void)
{
#if 1
    static flash_handle_t sflash;
    static uint16_t last_address_code;
    static bool last_Right_code_flag;
    static uint16_t flash_version = 0;
    static uint8_t flash_count = 0;
    static uint8_t first_start_flag = FALSE;
    static uint16_t a_ver;
    static uint16_t b_ver;

    switch (sflash.state)
    {
    case FLASH_START:
        if (FALSE == first_start_flag)
        {
            /* 检测主存储区和备份存储区数据 */
            if (data_check_len(A_LAST_ADDRESS_CODE_ADDRESS, FLASH_MENBER) != 0xFFFF && data_check_len(B_LAST_ADDRESS_CODE_ADDRESS, FLASH_MENBER) != 0xFFFF)
            {
                /* 检查哪个区的数据最新 */
                a_ver = flash_wred_halfword(A_FLASH_VERSION_ADDRESS);
                b_ver = flash_wred_halfword(B_FLASH_VERSION_ADDRESS);

                if (a_ver > b_ver)
                {
                    sFW433_t.Receiver_handle.Address_code = flash_wred_halfword(A_LAST_ADDRESS_CODE_ADDRESS);
                    sFW433_t.Receiver_handle.Right_code_flag = flash_wred_halfword(A_LAST_RIGHT_CODE_FLAG_ADDRESS);
                }
                else
                {
                    sFW433_t.Receiver_handle.Address_code = flash_wred_halfword(B_LAST_ADDRESS_CODE_ADDRESS);
                    sFW433_t.Receiver_handle.Right_code_flag = flash_wred_halfword(B_LAST_RIGHT_CODE_FLAG_ADDRESS);
                }
            }
            /* check area a data  */
            else if (data_check_len(A_LAST_ADDRESS_CODE_ADDRESS, FLASH_MENBER) != 0xFFFF)
            {
                sFW433_t.Receiver_handle.Address_code = flash_wred_halfword(A_LAST_ADDRESS_CODE_ADDRESS);
                sFW433_t.Receiver_handle.Right_code_flag = flash_wred_halfword(A_LAST_RIGHT_CODE_FLAG_ADDRESS);
            }
            /* check area b data  */
            else if (data_check_len(B_LAST_ADDRESS_CODE_ADDRESS, FLASH_MENBER) != 0xFFFF)
            {
                sFW433_t.Receiver_handle.Address_code = flash_wred_halfword(B_LAST_ADDRESS_CODE_ADDRESS);
                sFW433_t.Receiver_handle.Right_code_flag = flash_wred_halfword(B_LAST_RIGHT_CODE_FLAG_ADDRESS);
            }
            else
            {
                sFW433_t.Receiver_handle.Address_code = 0x0000;
                sFW433_t.Receiver_handle.Right_code_flag = 0;
            }

            if (sFW433_t.Receiver_handle.Address_code >= 0xffff || sFW433_t.Receiver_handle.Address_code < 0x0000)
            {
                sFW433_t.Receiver_handle.Address_code = 0x0000;
            }

            if (sFW433_t.Receiver_handle.Right_code_flag != 1 && sFW433_t.Receiver_handle.Right_code_flag != 0)
                sFW433_t.Receiver_handle.Right_code_flag = 0;

            last_address_code = sFW433_t.Receiver_handle.Address_code;
            last_Right_code_flag = sFW433_t.Receiver_handle.Right_code_flag;
            first_start_flag = TRUE;
        }
        else
        {
            sflash.state = FLASH_DIRECT_DATA;
            break;
        }

        break;

    case FLASH_DIRECT_DATA:
        if (last_address_code != sFW433_t.Receiver_handle.Address_code ||
            last_Right_code_flag != sFW433_t.Receiver_handle.Right_code_flag)
        {
            flash_unlock();

            if (flash_count % 2 != FALSE)
            {
                flash_sector_erase(A_LAST_ADDRESS_CODE_ADDRESS);

                flash_halfword_program(A_LAST_ADDRESS_CODE_ADDRESS, sFW433_t.Receiver_handle.Address_code);
                flash_halfword_program(A_LAST_RIGHT_CODE_FLAG_ADDRESS, sFW433_t.Receiver_handle.Right_code_flag);
            }
            else
            {
                flash_sector_erase(B_LAST_ADDRESS_CODE_ADDRESS);

                flash_halfword_program(B_LAST_ADDRESS_CODE_ADDRESS, sFW433_t.Receiver_handle.Address_code);
                flash_halfword_program(B_LAST_RIGHT_CODE_FLAG_ADDRESS, sFW433_t.Receiver_handle.Right_code_flag);
            }

            last_address_code = sFW433_t.Receiver_handle.Address_code;
            last_Right_code_flag = sFW433_t.Receiver_handle.Right_code_flag;
            sflash.state++;
            break;
        }

        break;
    case FLASH_FINSH:
        if (flash_count % 2 != FALSE)
        {
            flash_halfword_program(A_FLASH_VERSION_ADDRESS, flash_version);
        }
        else
        {
            flash_halfword_program(B_FLASH_VERSION_ADDRESS, flash_version);
        }
        flash_lock();
        flash_version++;
        flash_count++;
        sflash.state = FLASH_DIRECT_DATA;
        break;
    }

#endif
}
