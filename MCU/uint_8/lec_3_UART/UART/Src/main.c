/**
 ******************************************************************************
 * @file           : main.c
 * @author         : mohamed sultan
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "stm32f103x6.h"
#include "stm32_F103C6_USART_Driver.h"

uint_16 data;

void UART_CALLBack()
{
	MCAL_UART_ReceiveData(USART1, &data, Disable);
	 MCAL_UART_SendData(USART1, data, Enable);
}
void Clock_init()
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();

	RCC_AFIO_CLK_EN();

}
int main(void)
{

	Clock_init();
	USART_PinConfig_t uart_cfg;
	uart_cfg.BaudRate=USART_BaudRate_9600;
	uart_cfg.HwflowCtrl = USART_HwflowCtrl_none;
	uart_cfg.stop_Bits = USART_stopBits_1;
	uart_cfg.USART_Mode = USART_Mode_TX_RX;
	uart_cfg.Parity = USART_Parity_none;
	uart_cfg.Payload_Length = USART_Payload_Length_8bits;
	uart_cfg.IRQ_Enable.IRQ.Received_data_ready_to_be_read=USART_IRQ_Enable_Enable;
	uart_cfg.P_FUN.Received_data_ready_to_be_read_IRQ_CallBack=UART_CALLBack;
	MCAL_UART_Init(USART1, &uart_cfg);
	MCAL_UART_GPIO_Set_Pins(USART1);

   while(1)
   {
	  // MCAL_UART_ReceiveData(USART1, &data, Enable);
	  // MCAL_UART_SendData(USART1, data, Enable);


   }
}
