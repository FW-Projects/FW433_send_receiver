/* add user code begin Header */
/**
 **************************************************************************
 * @file     at32f421_int.c
 * @brief    main interrupt service routines.
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

/* includes ------------------------------------------------------------------*/
#include "at32f421_int.h"
#include "wk_system.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */
#include <math.h>
#include <stdlib.h>
#include "433_receiver.h"
#include "iap.h"
#include "tmt.h"
#include "iap_usart.h"
#include "FW433_Handle.h"
#include "asrpro_handle.h"
#include "usart_send_handle.h"
/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */

/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */
// uint32_t  valueTmp = 0;    //接收的数据
uint8_t state = 0; // 接收步骤
uint16_t holdTime = 0;
uint8_t data_433_buffer[3] = {0, 0, 0};
uint8_t usart1_tx_buffer[] = {0};
uint8_t usart1_rx_buffer[] = {0};
uint8_t usart1_tx_counter = 0;
uint8_t usart1_rx_counter = 0;
uint8_t usart1_tx_buffer_size = 20;
uint8_t usart1_rx_buffer_size = 20;


uint8_t usart2_rx_counter = 0;
uint16_t usart2_rx_buffer[4] = {0};
uint8_t usart2_rx_buffer_size = 4;


/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */

/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */

/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */

/* add user code end 0 */

/* external variables ---------------------------------------------------------*/
/* add user code begin external variables */

/* add user code end external variables */

/**
 * @brief  this function handles nmi exception.
 * @param  none
 * @retval none
 */
void NMI_Handler(void)
{
  /* add user code begin NonMaskableInt_IRQ 0 */

  /* add user code end NonMaskableInt_IRQ 0 */

  /* add user code begin NonMaskableInt_IRQ 1 */

  /* add user code end NonMaskableInt_IRQ 1 */
}

/**
 * @brief  this function handles hard fault exception.
 * @param  none
 * @retval none
 */
void HardFault_Handler(void)
{
  /* add user code begin HardFault_IRQ 0 */

  /* add user code end HardFault_IRQ 0 */
  /* go to infinite loop when hard fault exception occurs */
  while (1)
  {
    /* add user code begin W1_HardFault_IRQ 0 */

    /* add user code end W1_HardFault_IRQ 0 */
  }
}

/**
 * @brief  this function handles memory manage exception.
 * @param  none
 * @retval none
 */
void MemManage_Handler(void)
{
  /* add user code begin MemoryManagement_IRQ 0 */

  /* add user code end MemoryManagement_IRQ 0 */
  /* go to infinite loop when memory manage exception occurs */
  while (1)
  {
    /* add user code begin W1_MemoryManagement_IRQ 0 */

    /* add user code end W1_MemoryManagement_IRQ 0 */
  }
}

/**
 * @brief  this function handles bus fault exception.
 * @param  none
 * @retval none
 */
void BusFault_Handler(void)
{
  /* add user code begin BusFault_IRQ 0 */

  /* add user code end BusFault_IRQ 0 */
  /* go to infinite loop when bus fault exception occurs */
  while (1)
  {
    /* add user code begin W1_BusFault_IRQ 0 */

    /* add user code end W1_BusFault_IRQ 0 */
  }
}

/**
 * @brief  this function handles usage fault exception.
 * @param  none
 * @retval none
 */
void UsageFault_Handler(void)
{
  /* add user code begin UsageFault_IRQ 0 */

  /* add user code end UsageFault_IRQ 0 */
  /* go to infinite loop when usage fault exception occurs */
  while (1)
  {
    /* add user code begin W1_UsageFault_IRQ 0 */

    /* add user code end W1_UsageFault_IRQ 0 */
  }
}

/**
 * @brief  this function handles svcall exception.
 * @param  none
 * @retval none
 */
void SVC_Handler(void)
{
  /* add user code begin SVCall_IRQ 0 */

  /* add user code end SVCall_IRQ 0 */
  /* add user code begin SVCall_IRQ 1 */

  /* add user code end SVCall_IRQ 1 */
}

/**
 * @brief  this function handles debug monitor exception.
 * @param  none
 * @retval none
 */
void DebugMon_Handler(void)
{
  /* add user code begin DebugMonitor_IRQ 0 */

  /* add user code end DebugMonitor_IRQ 0 */
  /* add user code begin DebugMonitor_IRQ 1 */

  /* add user code end DebugMonitor_IRQ 1 */
}

/**
 * @brief  this function handles pendsv_handler exception.
 * @param  none
 * @retval none
 */
void PendSV_Handler(void)
{
  /* add user code begin PendSV_IRQ 0 */

  /* add user code end PendSV_IRQ 0 */
  /* add user code begin PendSV_IRQ 1 */

  /* add user code end PendSV_IRQ 1 */
}

/**
 * @brief  this function handles systick handler.
 * @param  none
 * @retval none
 */
void SysTick_Handler(void)
{
  /* add user code begin SysTick_IRQ 0 */

  /* add user code end SysTick_IRQ 0 */

  wk_timebase_handler();

  /* add user code begin SysTick_IRQ 1 */
  tmt.tick();
  /* add user code end SysTick_IRQ 1 */
}

/**
 * @brief  this function handles TMR3 handler.
 * @param  none
 * @retval none
 */
void TMR3_GLOBAL_IRQHandler(void)
{
  /* add user code begin TMR3_GLOBAL_IRQ 0 */
  //	uint8_t buf[3];
  static uint32_t valueTmp = 0; // 接收的数据
  static bool receive_flag = 0; // 数据接收完毕标志
  static uint16_t bitNums = 0;
  uint8_t de = gpio_input_data_bit_read(GPIOA, GPIO_PINS_7);
  tmr_flag_clear(TMR3, TMR_C2_FLAG);
  holdTime = tmr_channel_value_get(TMR3, TMR_SELECT_CHANNEL_2);
  tmr_counter_value_set(TMR3, 0);

  switch (state)
  {
  case 0:
  {
//    if (de == 1)
      state = 1; // 如果是高电平，那么是上升沿
  }
  break;
  case 1:
  {
//    if (de == 0 && holdTime >= StartLevelTime_H_MIN && holdTime <= StartLevelTime_H_MAX)
	   if (de == 0 )
    {
      // 检测到下降沿，起始信号高电平维持时间
      state = 2;
    }
    else
      state = 1;
  }
  break;
  case 2:
  {
    if ((de == 1) && (holdTime >= StartLevelTime_L_MIN) && (holdTime <= StartLevelTime_L_MAX))
    {
      // 检测到上升沿，起始信号低电平维持时间
      bitNums = 0; // 符合要求，清0接收到的位数和数据。准备开始接收
      valueTmp = 0;
      receive_flag = 0;
      state = 3;
    }
    else
      state = 1; // 不符合要求直接回到状态1，不用回到状态0，因为不需要判断同步信号的高电平
                 // 持续时间，低电平满足需求即
  }
  break;
  case 3: // 信号高电平结束
  {
    if (de == 0)
    {
      valueTmp <<= 1;                                                       // 向左移位，让出位置存数据
      if (holdTime >= OneLevelTime_H_MIN && holdTime <= OneLevelTime_H_MAX) // 符合数据1的高部分
      {
        valueTmp += 1;
        state = 4;
      }
      else if (holdTime >= ZeroLevelTime_H_MIN && holdTime <= ZeroLevelTime_H_MAX) // 符合数据0的高部分
      {
        state = 5;
      }
      else
        state = 1;
      bitNums += 1;
      if (bitNums >= 24)
      {
        receive_flag = 1; // 一次接收数据完毕
        data_433_buffer[0] = valueTmp >> 16;
        data_433_buffer[1] = valueTmp >> 8;
        data_433_buffer[2] = valueTmp;

        state = 1;
      }
    }
    else
      state = 1;
  }
  break;
  case 4: // 判断数据1的低电平持续时间是否符合要求
  {
    if (de == 1 && holdTime >= OneLevelTime_L_MIN && holdTime <= OneLevelTime_L_MAX)
    {
      state = 3; // 符合数据1的低电平时间要求，回到3重新接收下一个数据。
    }
    else
      state = 1;
  }
  break;
  case 5: // 判断数据0的低电平时间是否符合要求
  {
    if (de == 1 && holdTime >= ZeroLevelTime_L_MIN && holdTime >= ZeroLevelTime_L_MIN && holdTime <= ZeroLevelTime_L_MAX)
    {
      state = 3; // 符合要求，接收下一个数据。
    }
    else
      state = 1;
  }
  break;
  default:
    state = 0;
    break;
  }
  /* add user code end TMR3_GLOBAL_IRQ 0 */

  /* add user code begin TMR3_GLOBAL_IRQ 1 */

  /* add user code end TMR3_GLOBAL_IRQ 1 */
}

/**
 * @brief  this function handles USART1 handler.
 * @param  none
 * @retval none
 */
void USART1_IRQHandler(void)
{
  /* add user code begin USART1_IRQ 0 */

  /* read data usart*/
  if (USART1->ctrl1_bit.rdbfien != RESET)
  {
    if (usart_interrupt_flag_get(USART1, USART_RDBF_FLAG) != RESET)
    {
      /* read one byte from the receive data register */
      usart1_rx_buffer[usart1_rx_counter++] = usart_data_receive(USART1);
      if (usart1_rx_counter >= usart1_rx_buffer_size)
      {
        usart1_rx_counter = 0;                    // reset counter
        usart_flag_clear(USART1, USART_RDBF_INT); // clear interrupt flag
      }
    }
  }
  /* add user code end USART1_IRQ 0 */
  /* add user code begin USART1_IRQ 1 */
  /* add user code end USART1_IRQ 1 */
}

/**
 * @brief  this function handles USART2 handler.
 * @param  none
 * @retval none
 */
void USART2_IRQHandler(void)
{
  /* add user code begin USART2_IRQ 0 */
  if (usart_interrupt_flag_get(USART2, USART_RDBF_FLAG) != RESET)
  {
    /* read one byte from the receive data register */
    usart2_rx_buffer[usart2_rx_counter++] = usart_data_receive(USART2);
    if (usart2_rx_counter >= usart2_rx_buffer_size)
    {
      Asrpro_Rx_buffer[0] = usart2_rx_buffer[0];
      Asrpro_Rx_buffer[1] = usart2_rx_buffer[1];
      Asrpro_Rx_buffer[2] = usart2_rx_buffer[2];
	  Asrpro_Rx_buffer[3] = usart2_rx_buffer[3];	
	
      usart2_rx_counter = 0;                    // reset counter
      usart_flag_clear(USART2, USART_RDBF_INT); // clear interrupt flag
		Rx_usart2_finish_flag = true;
    }
  }
  /* add user code end USART2_IRQ 0 */
  /* add user code begin USART2_IRQ 1 */

  /* add user code end USART2_IRQ 1 */
}

/* add user code begin 1 */

/* add user code end 1 */
