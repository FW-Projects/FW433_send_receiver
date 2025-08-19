/* add user code begin Header */
/**
  **************************************************************************
  * @file     wk_tmr.c
  * @brief    work bench config program
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
#include "wk_tmr.h"

/* add user code begin 0 */

/* add user code end 0 */

/**
  * @brief  init tmr3 function.
  * @param  none
  * @retval none
  */
void wk_tmr3_init(void)
{
  /* add user code begin tmr3_init 0 */

  /* add user code end tmr3_init 0 */

  gpio_init_type gpio_init_struct;
  tmr_input_config_type  tmr_input_struct;

  gpio_default_para_init(&gpio_init_struct);

  /* add user code begin tmr3_init 1 */

  /* add user code end tmr3_init 1 */

  /* configure the tmr3 CH2 pin */
  gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE7, GPIO_MUX_1);
  gpio_init_struct.gpio_pins = GPIO_PINS_7;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(GPIOA, &gpio_init_struct);

  /* configure counter settings */
  tmr_cnt_dir_set(TMR3, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR3, TMR_CLOCK_DIV1);
  tmr_period_buffer_enable(TMR3, FALSE);
  tmr_base_init(TMR3, 60000, 39);

  /* configure primary mode settings */
  tmr_sub_sync_mode_set(TMR3, FALSE);
  tmr_primary_mode_select(TMR3, TMR_PRIMARY_SEL_RESET);

  /* configure channel 2 input settings */
  tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_2;
  tmr_input_struct.input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
  tmr_input_struct.input_polarity_select = TMR_INPUT_BOTH_EDGE;
  tmr_input_struct.input_filter_value = 0;
  tmr_input_channel_init(TMR3, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);

  tmr_counter_enable(TMR3, TRUE);

  /**
   * Users need to configure TMR3 interrupt functions according to the actual application.
   * 1. Call the below function to enable the corresponding TMR3 interrupt.
   *     --tmr_interrupt_enable(...)
   * 2. Add the user's interrupt handler code into the below function in the at32f421_int.c file.
   *     --void TMR3_GLOBAL_IRQHandler(void)
   */

  /* add user code begin tmr3_init 2 */
 tmr_interrupt_enable(TMR3, TMR_C2_INT, TRUE);
  /* add user code end tmr3_init 2 */
}

/* add user code begin 1 */

/* add user code end 1 */
