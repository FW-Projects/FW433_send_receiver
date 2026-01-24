/* add user code begin Header */
/**
 **************************************************************************
 * @file     main.c
 * @brief    main program
 **************************************************************************
 *                       Copyright notice & Disclaimer
 *
 * The software Board Support Package (BSP) that is made available to
 * download from Artery official website is the copyrighted work of Artery.
 * Artery authorizes customers to use, copy, and distribute the BSP
 * software and its related documentation for the purpose of design and
 * development in conjunction with Artery microcontrollers. Use of the
 * software is governed by this copyright notice and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
 * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
 * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
 * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
 * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 **************************************************************************
 */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "at32f421_wk_config.h"
#include "wk_crc.h"
#include "wk_tmr.h"
#include "wk_usart.h"
#include "wk_wdt.h"
#include "wk_gpio.h"
#include "wk_system.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */

#include "tmt.h"
#include "433_receiver.h"
#include "iap.h"
#include "FW433_handle.h"
#include "flash_handle.h"
#include "asrpro_handle.h"
#include "usart_send_handle.h"
#include "at32f421_int.h"
/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */
#define LED_HANDLE_TIME 100
/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */

/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */

/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */

/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */
void recevier433_task(void);
void iap_command_handle(void);
void flash_task(void);
void iap_task(void);
void asrpro_task(void);
void usart_send_task(void);
void led_task(void);
void uart_error(void);
/* add user code end 0 */

/**
 * @brief main function.
 * @param  none
 * @retval none
 */
int main(void)
{
  /* add user code begin 1 */

  /* add user code end 1 */

  /* system clock config. */
  wk_system_clock_config();

  /* config periph clock. */
  wk_periph_clock_config();

  /* nvic config. */
  wk_nvic_config();

  /* timebase config. */
  wk_timebase_init();

  /* init gpio function. */
  wk_gpio_config();

  /* init usart1 function. */
  wk_usart1_init();

  /* init usart2 function. */
  wk_usart2_init();

  /* init crc function. */
  wk_crc_init();

  /* init wdt function. */
  wk_wdt_init();

  /* init tmr3 function. */
  wk_tmr3_init();

  /* add user code begin 2 */

  tmt_init();
  tmt.create(recevier433_task, TASK_433_TIME);
  tmt.create(iap_task, IAP_HANDLE_TIME);
  tmt.create(flash_task, FLASH_HANDLE_TIME);
  tmt.create(asrpro_task, VOICE_HANDLE_TIME);
  tmt.create(usart_send_task, USART_SEND_HANDLE_TIME);
  tmt.create(led_task, LED_HANDLE_TIME);
  gpio_bits_reset(GPIOB, GPIO_PINS_1);

  FW433_Init(&sFW433_t);
  wk_delay_ms(2000);
  usart_flag_clear(USART2, USART_RDBF_FLAG); // clear interrupt flag
  usart_interrupt_enable(USART2, USART_RDBF_INT, TRUE);
  /* add user code end 2 */

  while (1)
  {
    /* add user code begin 3 */
    tmt.run();

    /* add user code end 3 */
  }
}

/* add user code begin 4 */
/**
 * @brief  iap task function
 * @param  none
 * @retval none
 */
void iap_task(void)
{
  iap_command_handle();
}

/**
 * @brief  recevier433 task function
 * @param  none
 * @retval none
 */
void recevier433_task(void)
{
  recevier_handle();
}

/**
 * @brief  flash task function
 * @param  none
 * @retval none
 */
void flash_task(void)
{
  FlashProc();
}

/**
 * @brief  voice task function
 * @param  none
 * @retval none
 */
void asrpro_task(void)
{
  asrpro_Handle();
}

/**
 * @brief  usart task function
 * @param  none
 * @retval none
 */
void usart_send_task(void)
{
  usart_send_handle();
}

/**
 * @brief  led task function
 * @param  none
 * @retval none
 */
void led_task(void)
{
  if (sFW433_t.Receiver_handle.led_times != 0x00)
  {
    sFW433_t.Receiver_handle.led_times--;
    if (gpio_output_data_bit_read(GPIOA, GPIO_PINS_5) == false)
      gpio_bits_set(GPIOA, GPIO_PINS_5);
    else if (gpio_output_data_bit_read(GPIOA, GPIO_PINS_5) == true)
      gpio_bits_reset(GPIOA, GPIO_PINS_5);
  }
  else
  {
    sFW433_t.Receiver_handle.led_times = 0x00;
    gpio_bits_reset(GPIOA, GPIO_PINS_5);
  }
}

/* add user code end 4 */
