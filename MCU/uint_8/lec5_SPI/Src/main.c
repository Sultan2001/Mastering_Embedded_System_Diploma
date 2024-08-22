/**
 ******************************************************************************
 * @file           : main.c
 * @author         : mohamed sulran
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
#include "Platform_Types.h"
#include "stm32_F103C6_SPI_Driver.h"
#include "stm32_F103C6_USART_Driver.h"

//#define SPI_MASTER_MODE
#define SPI_SLAVE_MODE


uint_16 data;

void UART_CALLBack()
{

#ifdef SPI_MASTER_MODE
	MCAL_UART_ReceiveData(USART1, &data, Disable);
	//MCAL_UART_SendData(USART1, data, Enable);
	//SPI Send data
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_State_RESET);
	MCAL_SPI_Send_and_ReceiveData(SPI1, &data, Enable);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_State_SET);
	MCAL_UART_SendData(USART1, data, Enable);

#endif


}

#ifdef SPI_SLAVE_MODE
void SPI_CALLBack(IRQ_SRC SRC)
{
if(SRC.S_IRQ_SRC.RXNE)
{
	data='A';
	MCAL_SPI_Send_and_ReceiveData(SPI1, &data, Disable);
	MCAL_UART_SendData(USART1, data, Enable);

}
}
#endif
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

	SPI_Config spi_cfg;
	spi_cfg.CLKPhase=SPI_CLKPhase_2_edge_first_data_capture_edge;
	spi_cfg.CLKPolarity=SPI_CLKPolarity_high_level_idle_state;
	spi_cfg.Communication_Mode=SPI_Communication_Mode_2_lines_Full_duplex;
	spi_cfg.Frame_Format=SPI_Frame_Format_MSB;
	spi_cfg.DataSize=SPI_DataSize_8Bit;
	spi_cfg.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_fPCLK_by_8; //PCLK = 8Mhz      PCLK/8

#ifdef SPI_MASTER_MODE
	spi_cfg.Device_Mode=SPI_Device_Mode_Master;
	spi_cfg.IRQ_Enable.all_IRQ = SPI_IRQ_Enable_all_Disable;
	spi_cfg.NSS=SPI_NSS_By_Software_Active_HIGH;

	//Config Slave select pin from GPIO
	GPIO_PinConfig_t pin;
	pin.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
	pin.GPIO_PinNumber = GPIO_PIN_0;
	MCAL_GPIO_Init(GPIOA, &pin);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_State_SET);
#endif

#ifdef SPI_SLAVE_MODE
	spi_cfg.Device_Mode=SPI_Device_Mode_Slave;
	spi_cfg.Slave_Mode = SPI_Slave_Mode_Point_to_Point;
	spi_cfg.NSS=SPI_NSS_By_Hardware_Slave;
	spi_cfg.IRQ_Enable.S_IRQ_SRC.RXNE=SPI_IRQ_Enable_Enable;
	spi_cfg.P_IRQ_CallBack = SPI_CALLBack;

#endif

	MCAL_SPI_Init(SPI1, &spi_cfg);
	MCAL_SPI_GPIO_Set_Pins(SPI1);


	while(1)
	{


	}
}
