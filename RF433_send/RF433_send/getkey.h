#ifndef __getkey_H__
#define __getkey_H__
#define uint8_t unsigned char
#define uint16_t unsigned int
#define key_init 1             // 按键初始化代号
#define key_wobble 2           // 捎抖代号
#define key_press 3            // 有键按下代号
#define keylong_stat 4         // 长按键起始代号
#define key_long_on 5          // 长按键连发代号
#define key_period 6           // 按键释放代号
#define keylong_pepione 1000    // 长按键时间常数代号
#define key_continue_period 50 // 按键连发周期常数代号
#define keydown_ent 1          // 单击
#define keyup_ent 2
#define key_long 3
#define key_continue 4 // 长按健

#define key_null 0
#define key_air_up 1
#define key_temp_down 2
#define key_temp_up 3
#define key_ch3 4
#define key_ch1 5
#define KEY_Switch_handle 6
#define key_ch4 7
#define key_ch2 8
#define key_air_down 9
#define key_clear 10
#define key_reset 11
extern volatile uint8_t inkey_number; // 保存按键代号值
extern volatile uint8_t key_stat;
extern volatile uint16_t key_time;
uint8_t key_scan(void);
get_key(void);
void keygpio_init(void);
#endif