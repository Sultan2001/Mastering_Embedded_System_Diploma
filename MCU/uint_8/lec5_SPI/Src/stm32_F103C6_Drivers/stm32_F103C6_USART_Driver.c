/*
 * stm32_F103C6_USART_Driver.c
 *
 *  Created on: Aug 10, 2024
 *      Author: mohamed sultan
 */


#include "stm32_F103C6_USART_Driver.h"

//-----------------------------
// GV
//-----------------------------

IRQ_pointers_FUN_t USART_ISR[3] = {NULL } ;


//-----------------------------
//Macros Configuration References
//-----------------------------





/*@ref Module_REF_NAME_define
 */




/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */
static uint_32 calc_baudrate(uint_32 clk , uint_32 baudrate)
{
	uint_32 USARTDIV_Mul100,USARTDIV,DIV_Mantissa_Mul100,DIV_Fraction;
	uint_32 ret=0;
	// USARTDIV = DIV_Mantissa + (DIV_Fraction / 16)
	// Tx/ Rx baud = fCK /  (16*USARTDIV)
	// note -  Mul100 to avoid floating number
	USARTDIV_Mul100 = (clk*100)/(16*baudrate);
	USARTDIV= (clk)/(16*baudrate); // = DIV_Mantissa
	DIV_Mantissa_Mul100  = USARTDIV *100;
	DIV_Fraction =  ((USARTDIV_Mul100 - DIV_Mantissa_Mul100)*16)/100;
	ret = (USARTDIV <<4) | (DIV_Fraction & 0xf);

	return ret;

}

static void Enable_NVIC(uint_8 UART_NUM)
{
	switch(UART_NUM)
	{
	case 0:
		NVIC_IRQ37_USART1_Enable();
		break;

	case 1:
		NVIC_IRQ38_USART2_Enable();
		break;

	case 2 :
		NVIC_IRQ39_USART3_Enable();
		break;


	}
}

static void Disable_NVIC(uint_8 UART_NUM)
{
	switch(UART_NUM)
	{
	case 0:
		NVIC_IRQ37_USART1_Disable();
		break;

	case 1:
		NVIC_IRQ38_USART2_Disable();
		break;

	case 2 :
		NVIC_IRQ39_USART3_Disable();
		break;


	}
}
void MCAL_UART_Init(USART_t * USARTx , USART_PinConfig_t * UART_Config)
{

	uint_32 clk = 0;
	uint_8 n=0; // Uart number

	//Enable clock
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_EN();
		clk = MCAL_RCC_GetPCLCK1Ferq();
		n=0;
	}
	else if (USARTx == USART2)
	{
		RCC_USART2_CLK_EN();
		clk = MCAL_RCC_GetPCLCK2Ferq();
		n=1;
	}
	else if (USARTx == USART3)
	{
		RCC_USART3_CLK_EN();
		clk = MCAL_RCC_GetPCLCK2Ferq();
		n=2;
	}

	//Enable USART
	// Bit 13 UE: USART enable
	SET_BIT(USARTx->CR1 , 13);
	// USART Mode Enable (TX , RX , TX RX)
	USARTx->CR1 |= UART_Config->USART_Mode;
	//Program the M bit in USART_CR1 to define the word length.
	//Bit 12 M: Word length
	USARTx->CR1 |=UART_Config->Payload_Length;
	// Program the number of stop bits in USART_CR2.
	USARTx->CR2 |= UART_Config->stop_Bits;
	// Program parity bit
	USARTx->CR1 |=UART_Config->Parity;
	// Program Flow control
	USARTx->CR3 |=UART_Config->HwflowCtrl;
	// Select the desired baud rate using the USART_BRR register
	USARTx->BRR = calc_baudrate(clk , UART_Config->BaudRate);

	// Enable Or disable NVIC
	if(UART_Config->IRQ_Enable.All_IRQ !=0)
	{
		Enable_NVIC(n);

		if(UART_Config->IRQ_Enable.IRQ.Transmit_data_register_empty)
		{
			// Bit 7 TXEIE: TXE interrupt enable
			SET_BIT(USARTx->CR1 , 7);

			USART_ISR[n].Transmit_data_register_empty_IRQ_CallBack = UART_Config->P_FUN.Transmit_data_register_empty_IRQ_CallBack;


		}
		if(UART_Config->IRQ_Enable.IRQ.Received_data_ready_to_be_read)
		{

			// Bit 5 RXNEIE: RXNE interrupt enable
			SET_BIT(USARTx->CR1 , 5);
			USART_ISR[n].Received_data_ready_to_be_read_IRQ_CallBack = UART_Config->P_FUN.Received_data_ready_to_be_read_IRQ_CallBack;

		}
		if(UART_Config->IRQ_Enable.IRQ.Transmission_complete)
		{
			// Bit 6 TCIE: Transmission complete interrupt enable
			SET_BIT(USARTx->CR1 , 6);
			USART_ISR[n].Transmission_complete_IRQ_CallBack = UART_Config->P_FUN.Transmission_complete_IRQ_CallBack;

		}

	}
	else
	{
		Disable_NVIC(n);
	}


}
void MCAL_UART_DEInit(USART_t * USARTx)
{
	uint_8 n=0;
	if(USARTx == USART1)
	{
		RCC_USART1_Reset();
		n=0;
	}
	if(USARTx == USART2)
	{
		RCC_USART2_Reset();
		n=1;
	}
	if(USARTx == USART3)
	{
		RCC_USART3_Reset();
		n=2;
	}
	Disable_NVIC(n);


}

void MCAL_UART_GPIO_Set_Pins( USART_t * UARTx)
{

	GPIO_PinConfig_t pin;


	if(UARTx == USART1)
	{
		//UART1
		/*
		 * TX			A9
		 * RX			A10
		 * CTS			A11
		 * RTS			A12
		 */

		// TX			A9
		pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
		pin.GPIO_PinNumber = GPIO_PIN_9;
		pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOA, &pin);

		// RX			A10
		pin.GPIO_Mode = GPIO_MODE_AF_INPUT;
		pin.GPIO_PinNumber = GPIO_PIN_10;
		pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOA, &pin);
		// Program Flow control
		if(READ_BIT(UARTx->CR3 , 9))
		{
			//CTS Enable
			//CTS			A11
			pin.GPIO_Mode = GPIO_MODE_AF_INPUT;
			pin.GPIO_PinNumber = GPIO_PIN_11;
			pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOA, &pin);
		}
		if(READ_BIT(UARTx->CR3 , 9))
		{
			//RTS enable
			//RTS			A12
			pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			pin.GPIO_PinNumber = GPIO_PIN_12;
			pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOA, &pin);
		}


	}
	else if(UARTx == USART2)
	{
		//UART2
		/*
		 * TX			A2
		 * RX			A3
		 * CTS			A0
		 * RTS			A1
		 */


		// TX			A2
		pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
		pin.GPIO_PinNumber = GPIO_PIN_2;
		pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOA, &pin);

		// RX			A3
		pin.GPIO_Mode = GPIO_MODE_AF_INPUT;
		pin.GPIO_PinNumber = GPIO_PIN_3;
		pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOA, &pin);
		// Program Flow control
		if(READ_BIT(UARTx->CR3 , 9))
		{
			//CTS Enable
			//CTS			A0
			pin.GPIO_Mode = GPIO_MODE_AF_INPUT;
			pin.GPIO_PinNumber = GPIO_PIN_0;
			pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOA, &pin);
		}
		if(READ_BIT(UARTx->CR3 , 9))
		{
			//RTS enable
			//RTS			A1
			pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			pin.GPIO_PinNumber = GPIO_PIN_1;
			pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOA, &pin);
		}


	}
	else if(UARTx == USART2)
	{
		//UART3
		/*
		 * TX			B10
		 * RX			B11
		 * CTS			B13
		 * RTS			B14
		 */


		// TX			B10
		pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
		pin.GPIO_PinNumber = GPIO_PIN_10;
		pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOB, &pin);

		// RX			B11
		pin.GPIO_Mode = GPIO_MODE_AF_INPUT;
		pin.GPIO_PinNumber = GPIO_PIN_11;
		pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOB, &pin);
		// Program Flow control
		if(READ_BIT(UARTx->CR3 , 9))
		{
			//CTS Enable
			//CTS			B13
			pin.GPIO_Mode = GPIO_MODE_AF_INPUT;
			pin.GPIO_PinNumber = GPIO_PIN_13;
			pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOB, &pin);
		}
		if(READ_BIT(UARTx->CR3 , 9))
		{
			//RTS enable
			//RTS			B14
			pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			pin.GPIO_PinNumber = GPIO_PIN_14;
			pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOB, &pin);
		}


	}


}
void MCAL_UART_SendData(USART_t * USARTx , uint_16 data , enum Polling_mechism PollingEN)
{
	// wait until TXE flag is set in the SR
	if(PollingEN == Enable)
	{
		while(!READ_BIT(USARTx->SR , 7));
	}

	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//	because it is replaced by the parity.
	//	 When receiving with the parity enabled, the value read in the MSB bit is the received parity
	//	 bit.


	// Bit 12 M: Word length
	// check Word length
	if(READ_BIT(USARTx->CR1 , 12))
	{
		//9 Data bits
		USARTx->DR = data & (uint_16)0x1FF;

	}
	else
	{
		//8 Data bits
		USARTx->DR = data & (uint_16)0xFF;
	}







}

void MCAL_UART_ReceiveData(USART_t * USARTx , uint_16 * data , enum Polling_mechism PollingEN)
{
	//	 When a character is received
	//	 • The RXNE bit is set. It indicates that the content of the shift register is transferred to the
	//		RDR
	if(PollingEN == Enable)
	{
		while(!READ_BIT(USARTx->SR , 5));
	}





	// Bit 12 M: Word length
	// check Word length
	if(READ_BIT(USARTx->CR1 , 12))
	{
		//9 Data bits

		//  Bit 10 PCE: Parity control enable
		// Check Parity control bit is enable OR NOT
		if(READ_BIT(USARTx->CR1 , 10))
		{
			// Parity control enable
			*data = (USARTx->DR)&(0xff);
		}
		else
		{
			// // Parity control disable
			*data = USARTx->DR;
		}




	}
	else
	{
		//8 Data bits

		//  Bit 10 PCE: Parity control enable
		// Check Parity control bit is enable OR NOT
		if(READ_BIT(USARTx->CR1 , 10))
		{
			// Parity control enable
			*data = (USARTx->DR)&(0x7f);
		}
		else
		{
			// // Parity control disable
			*data = (USARTx->DR) & (0xff);
		}


	}




}
void MCAL_UART_Wait_TD(USART_t * USARTx)
{



}



void USART1_IRQHandler()
{
	if(READ_BIT(USART1->SR , 7 ) & READ_BIT(USART1->CR1 , 7 ))
	{
		// Data is transferred to the shift register
		USART_ISR[0].Transmit_data_register_empty_IRQ_CallBack();
	}

	if(READ_BIT(USART1->SR ,5 ) & READ_BIT(USART1->CR1 , 5 ))
	{
		// 1: A USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR register
		RESET_BIT(USART1->SR ,5 );
		USART_ISR[0].Received_data_ready_to_be_read_IRQ_CallBack();
	}

	if(READ_BIT(USART1->SR ,6 ) & READ_BIT(USART1->CR1 , 6 ))
	{
		//  Bit 6 TC: Transmission complete
		RESET_BIT(USART1->SR ,6 );
		USART_ISR[0].Transmission_complete_IRQ_CallBack();
	}

}
void USART2_IRQHandler()
{
	if(READ_BIT(USART2->SR , 7 ) & READ_BIT(USART2->CR1 , 7 ))
	{
		// Data is transferred to the shift register
		USART_ISR[1].Transmit_data_register_empty_IRQ_CallBack();
	}

	if(READ_BIT(USART2->SR ,5 ) & READ_BIT(USART2->CR1 , 5 ))
	{
		// 1: A USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR register
		RESET_BIT(USART2->SR ,5 );
		USART_ISR[1].Received_data_ready_to_be_read_IRQ_CallBack();
	}

	if(READ_BIT(USART2->SR ,6 ) & READ_BIT(USART2->CR1 , 6 ))
	{
		//  Bit 6 TC: Transmission complete
		RESET_BIT(USART2->SR ,6 );
		USART_ISR[1].Transmission_complete_IRQ_CallBack();
	}
}
void USART3_IRQHandler()
{
	if(READ_BIT(USART3->SR , 7 ) & READ_BIT(USART3->CR1 , 7 ))
	{
		// Data is transferred to the shift register
		USART_ISR[2].Transmit_data_register_empty_IRQ_CallBack();
	}

	if((READ_BIT(USART3->SR ,5 )) & READ_BIT(USART3->CR1 , 5 ))
	{
		// 1: A USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR register
		RESET_BIT(USART3->SR ,5 );
		USART_ISR[2].Received_data_ready_to_be_read_IRQ_CallBack();
	}

	if(READ_BIT(USART3->SR ,6 ) & READ_BIT(USART3->CR1 , 6 ))
	{
		//  Bit 6 TC: Transmission complete
		RESET_BIT(USART3->SR ,6 );
		USART_ISR[2].Transmission_complete_IRQ_CallBack();
	}
}
