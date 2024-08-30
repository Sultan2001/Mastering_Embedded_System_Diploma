/*
 * stm32_F103C6_SPI_Driver.c
 *
 *  Created on: Aug 17, 2024
 *      Author: mohamed sultan
 */
#include "stm32_F103C6_SPI_Driver.h"


// callBack
void(*GP_IRQ_CallBack[2])(IRQ_SRC irq_src) = {NULL , NULL};
static uint_8 slave_Mode[2];
static uint_16 NSS_Mode[2];
//-----------------------------
//Macros Configuration References
//-----------------------------
#define SPI1_index	 0
#define SPI2_index	 1
#define RXNEIE_Bit	 6					//CR2
#define ERRIE_Bit	 5					//CR2
#define TXEIE_Bit	 7					//CR2
//#define ERRIE_Bit	 5					//CR2
//#define ERRIE_Bit	 5					//CR2
//#define ERRIE_Bit	 5					//CR2
/*@ref Module_REF_NAME_define
 */


/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */



void MCAL_SPI_Init(SPI_t * SPIx , SPI_Config * SPI_config)
{
	uint_16 CR1_TEMP=0;
	uint_16 CR2_TEMP=0;
	// Enable Clock
	if(SPIx == SPI1)
	{
		RCC_SPI1_CLK_EN();
		//slave Mode point to point OR multi slave
		slave_Mode[SPI1_index]=SPI_config->Slave_Mode;
		//NSS config
		NSS_Mode[SPI1_index]=SPI_config->NSS;


	}
	else if(SPIx == SPI2)
	{
		RCC_SPI1_CLK_EN();
		//slave Mode point to point OR multi slave
		slave_Mode[SPI2_index]=SPI_config->Slave_Mode;
		//NSS config
		NSS_Mode[SPI2_index]=SPI_config->NSS;
	}
	// Bit 6 SPE: SPI enable
	CR1_TEMP |= 1<<6;
	// Slave OR MASTER
	CR1_TEMP |= SPI_config->Device_Mode;
	// Clock phase
	CR1_TEMP |= SPI_config->CLKPhase;
	// Clock Polarity
	CR1_TEMP |= SPI_config->CLKPolarity;
	// 8 bits Or 16 bits
	CR1_TEMP |= SPI_config->DataSize;
	// Communication_Mode
	CR1_TEMP |= SPI_config->Communication_Mode;
	// Baud Rate Prescaler
	CR1_TEMP |= SPI_config->SPI_BaudRatePrescaler;
	// LSB OR MSB
	CR1_TEMP |= SPI_config->Frame_Format;

	//========================= NSS =====================
	if(SPI_config->NSS == SPI_NSS_By_Hardware_Master_SS_Output_Enable)
	{
		CR2_TEMP |=SPI_NSS_By_Hardware_Master_SS_Output_Enable;


	}
	else if(SPI_config->NSS ==  SPI_NSS_By_Hardware_Master_SS_Output_Disable)
	{
		CR2_TEMP &=SPI_NSS_By_Hardware_Master_SS_Output_Disable;
	}
	else
	{
		CR1_TEMP |= SPI_config->NSS;
	}

	// ============== Interrupt ===============
	if(SPI_config->IRQ_Enable.all_IRQ != 0)
	{
		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable();
			GP_IRQ_CallBack[SPI1_index]=SPI_config->P_IRQ_CallBack;
		}
		else
		{
			NVIC_IRQ36_SPI2_Enable();
			GP_IRQ_CallBack[SPI2_index]=SPI_config->P_IRQ_CallBack;
		}

		if(SPI_config->IRQ_Enable.S_IRQ_SRC.RXNE)
		{
			//  Bit 6 RXNEIE: RX buffer not empty interrupt enable
			CR2_TEMP |= (1<<RXNEIE_Bit);
		}
		if(SPI_config->IRQ_Enable.S_IRQ_SRC.TXE)
		{
			//Bit 7 TXEIE: Tx buffer empty interrupt enable
			CR2_TEMP |= (1<<TXEIE_Bit);


		}
		if(SPI_config->IRQ_Enable.S_IRQ_SRC.ERRI)
		{
			//		Bit 5 ERRIE: Error interrupt enable
			//		This bit controls the generation of an interrupt when an error condition occurs (CRCERR,
			//		OVR, MODF in SPI mode and UDR, OVR in I2S mode).
			CR2_TEMP |= (1<<ERRIE_Bit);

		}


	}


	SPIx->CR1 = CR1_TEMP;
	SPIx->CR2 = CR2_TEMP;

}
void MCAL_SPI_DeInit(SPI_t * SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable();
		RCC_SPI1_Reset();
	}
	else
	{
		NVIC_IRQ36_SPI2_Disable();
		RCC_SPI2_Reset();
	}

}
void MCAL_SPI_GPIO_Set_Pins(SPI_t * SPIx)
{
	// ======================= SPIx_SCK  ================================//
	//	 Master 																Alternate function push-pull
	//	 Slave 																	Input floating

	// ======================= SPIx_MOSI==================================//
	//	 Full duplex / master 													Alternate function push-pull
	//	 Full duplex /  slave 													Input floating / Input pull-up
	//	 Simplex bidirectional data wire / master 								Alternate function push-pull
	//	 Simplex bidirectional data wire/ slave 								Not used. Can be used as a GPIO

	//==================== SPIx_MISO ====================================//
	//	 Full duplex / master                                                   Input floating /Input pull-up
	//	 Full duplex /  slave (point to point) 									Alternate function push-pull
	//	 Full duplex /  slave (multi-slave) 									Alternate function open drain
	//	 Simplex bidirectional data wire / master 								Not used. Can be used as a GPIO
	//	 Simplex bidirectional data wire/ slave (point to point) 				Alternate function push-pull
	//	 Simplex bidirectional data wire/ slave (multi-slave)					Alternate function open drain

	// =====================  SPIx_NSS=================================//
	//	 Hardware master /slave 												Input floating/ Input pull-up / Input pull-down
	//	 Hardware master/ NSS output enabled 									Alternate function push-pull
	//	 Software Not used. 													Can be used as a GPIO


	GPIO_PinConfig_t pin;


	if(SPIx == SPI1)
	{
		//SPI1
		// NSS    PA4
		// SCK    PA5
		// MISO   PA6
		// MOSI   PA7

		// Master OR Slave
		if(READ_BIT(SPIx->CR1 , SPI_Master_Slave_Bit))
		{
			// Master
			// SCK    PA5       Alternate function push-pull
			pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
			pin.GPIO_PinNumber = GPIO_PIN_5;
			MCAL_GPIO_Init(GPIOA, &pin);

			// MISO   PA6
			//	 Full duplex / master                   Input floating /Input pull-up
			pin.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			pin.GPIO_PinNumber = GPIO_PIN_6;
			MCAL_GPIO_Init(GPIOA, &pin);

			// MOSI   PA7
			//	 Full duplex / master 					Alternate function push-pull
			pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
			pin.GPIO_PinNumber = GPIO_PIN_7;
			MCAL_GPIO_Init(GPIOA, &pin);

			// NSS    PA4
			switch(NSS_Mode[SPI1_index])
			{
			case SPI_NSS_By_Hardware_Master_SS_Output_Enable:
				//Hardware master/ NSS output enabled 				Alternate function push-pull
				pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
				pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
				pin.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIO_Init(GPIOA, &pin);
				break;

			case SPI_NSS_By_Hardware_Master_SS_Output_Disable:
				//	 Hardware master /slave 			Input floating/ Input pull-up / Input pull-down
				pin.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				pin.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIO_Init(GPIOA, &pin);
				break;

			}



		}
		else
		{
			// Slave
			// SCK    PA5       Input floating
			pin.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			pin.GPIO_PinNumber = GPIO_PIN_5;
			MCAL_GPIO_Init(GPIOA, &pin);

			// MISO   PA6
			if(slave_Mode[SPI1_index]==SPI_Slave_Mode_Point_to_Point)
			{
				// Full duplex /  slave (point to point) 			Alternate function push-pull

				pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
				pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
				pin.GPIO_PinNumber = GPIO_PIN_6;
				MCAL_GPIO_Init(GPIOA, &pin);

			}
			else if(slave_Mode[SPI1_index]==SPI_Slave_Mode_multi_slave)
			{
				//	Full duplex /  slave (multi-slave) 			Alternate function open drain
				pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_OD;
				pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
				pin.GPIO_PinNumber = GPIO_PIN_6;
				MCAL_GPIO_Init(GPIOA, &pin);


			}

			// MOSI   PA7
			//	 Full duplex /  slave 							Input floating / Input pull-up
			pin.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			pin.GPIO_PinNumber = GPIO_PIN_7;
			MCAL_GPIO_Init(GPIOA, &pin);

			// NSS    PA4
			//	 Hardware master /slave 			Input floating/ Input pull-up / Input pull-down
			pin.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			pin.GPIO_PinNumber = GPIO_PIN_4;
			MCAL_GPIO_Init(GPIOA, &pin);


		}



	}
	else if(SPIx == SPI2)
	{
		//SPI2
		// NSS    PB12
		// SCK    PB13
		// MISO   PB14
		// MOSI   PB15

		// Master OR Slave
		if(READ_BIT(SPIx->CR1 , SPI_Master_Slave_Bit))
		{
			// Master
			// SCK    PB13       Alternate function push-pull
			pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
			pin.GPIO_PinNumber = GPIO_PIN_13;
			MCAL_GPIO_Init(GPIOB, &pin);

			// MISO   PB14
			//	 Full duplex / master                   Input floating /Input pull-up
			pin.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			pin.GPIO_PinNumber = GPIO_PIN_14;
			MCAL_GPIO_Init(GPIOB, &pin);

			// MOSI   PB15
			//	 Full duplex / master 					Alternate function push-pull
			pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
			pin.GPIO_PinNumber = GPIO_PIN_15;
			MCAL_GPIO_Init(GPIOB, &pin);

			// NSS    PB12
			switch(NSS_Mode[SPI1_index])
			{
			case SPI_NSS_By_Hardware_Master_SS_Output_Enable:
				//Hardware master/ NSS output enabled 				Alternate function push-pull
				pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
				pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
				pin.GPIO_PinNumber = GPIO_PIN_12;
				MCAL_GPIO_Init(GPIOB, &pin);
				break;

			case SPI_NSS_By_Hardware_Master_SS_Output_Disable:
				//	 Hardware master /slave 			Input floating/ Input pull-up / Input pull-down
				pin.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				pin.GPIO_PinNumber = GPIO_PIN_12;
				MCAL_GPIO_Init(GPIOB, &pin);
				break;

			}



		}
		else
		{
			// Slave
			// SCK    PB13       Input floating
			pin.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			pin.GPIO_PinNumber = GPIO_PIN_13;
			MCAL_GPIO_Init(GPIOB, &pin);

			// MISO   PB14
			if(slave_Mode[SPI2_index]==SPI_Slave_Mode_Point_to_Point)
			{
				// Full duplex /  slave (point to point) 			Alternate function push-pull

				pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
				pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
				pin.GPIO_PinNumber = GPIO_PIN_14;
				MCAL_GPIO_Init(GPIOB, &pin);

			}
			else if(slave_Mode[SPI2_index]==SPI_Slave_Mode_multi_slave)
			{
				//	Full duplex /  slave (multi-slave) 			Alternate function open drain
				pin.GPIO_Mode = GPIO_MODE_OUTPUT_AF_OD;
				pin.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
				pin.GPIO_PinNumber = GPIO_PIN_14;
				MCAL_GPIO_Init(GPIOB, &pin);


			}

			// MOSI   PB15
			//	 Full duplex /  slave 							Input floating / Input pull-up
			pin.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			pin.GPIO_PinNumber = GPIO_PIN_15;
			MCAL_GPIO_Init(GPIOB, &pin);

			// NSS    PB12
			//	 Hardware master /slave 			Input floating/ Input pull-up / Input pull-down
			pin.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			pin.GPIO_PinNumber = GPIO_PIN_12;
			MCAL_GPIO_Init(GPIOB, &pin);


		}

	}
}
void MCAL_SPI_SendData(SPI_t * SPIx , uint_16 data , enum Polling_mechism PollingEN)
{
	if(PollingEN == Enable)
	{
		//Bit 1 TXE: Transmit buffer empty
		//		0: Tx buffer not empty
		//		1: Tx buffer empty
		while(!READ_BIT( SPIx->SR , 1));

	}

	SPIx->DR = data;


}
void MCAL_SPI_ReceiveData(SPI_t * SPIx , uint_16 * data , enum Polling_mechism PollingEN)
{
	if(PollingEN == Enable)
	{
		//Bit 0 RXNE: Receive buffer not empty
		//		 0: Rx buffer empty
		//		 1: Rx buffer not empty
		while(!READ_BIT( SPIx->SR , 0));

	}

	*data = SPIx->DR;
}
void MCAL_SPI_Send_and_ReceiveData(SPI_t * SPIx , uint_16 * data , enum Polling_mechism PollingEN)
{
	//SendData
	if(PollingEN == Enable)
	{
		while(!READ_BIT( SPIx->SR , 1));
	}
	SPIx->DR = *data;
	//ReceiveData
	if(PollingEN == Enable)
	{
		while(!READ_BIT( SPIx->SR , 0));
	}
	*data = SPIx->DR;
}


/*
 * ===============================================
 * APIs IRQ
 * ===============================================
 */

void SPI1_IRQHandler ()
{
	IRQ_SRC IRQ;
	//SR reg Bit 0 RXNE: Receive buffer not empty
	IRQ.S_IRQ_SRC.RXNE = READ_BIT(SPI1->CR2 , RXNEIE_Bit ) & READ_BIT(SPI1->SR , 0);
	//SR reg Bit 1 TXE: Transmit buffer empty
	IRQ.S_IRQ_SRC.TXE = READ_BIT(SPI1->CR2 , TXEIE_Bit ) & READ_BIT(SPI1->SR , 1);
	IRQ.S_IRQ_SRC.ERRI = READ_BIT(SPI1->CR2 , ERRIE_Bit ) ;
	GP_IRQ_CallBack[0](IRQ);
}
void SPI2_IRQHandler ()
{
	IRQ_SRC IRQ;
	//SR reg Bit 0 RXNE: Receive buffer not empty
	IRQ.S_IRQ_SRC.RXNE = READ_BIT(SPI2->CR2 , RXNEIE_Bit ) & READ_BIT(SPI1->SR , 0);
	//SR reg Bit 1 TXE: Transmit buffer empty
	IRQ.S_IRQ_SRC.TXE = READ_BIT(SPI2->CR2 , TXEIE_Bit ) & READ_BIT(SPI1->SR , 1);
	IRQ.S_IRQ_SRC.ERRI = READ_BIT(SPI2->CR2 , ERRIE_Bit ) ;
	GP_IRQ_CallBack[1](IRQ);

}
