/*
 * stm32_F103C6_SPI_Driver.h
 *
 *  Created on: Aug 17, 2024
 *      Author: mohamed sultan
 */

#ifndef STM32_F103C6_DRIVERS_INC_STM32_F103C6_SPI_DRIVER_H_
#define STM32_F103C6_DRIVERS_INC_STM32_F103C6_SPI_DRIVER_H_


#define SPI_Master_Slave_Bit		2


//-----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"
#include "stm32_F103C6_GPIO_Driver.h"


//-----------------------------
//User type definitions (structures)
//-----------------------------



typedef union
{
	struct
	{
		uint_8 TXE:1; 		//TX Buffer empty interrupt
		uint_8 RXNE:1; 		//RX Buffer not empty interrupt
		uint_8 ERRI:1; 		//ERROR interrupt
		uint_8 Reserved:5;

	}S_IRQ_SRC;

	uint_8 all_IRQ;

}IRQ_SRC;
typedef struct
{
	uint_16 Device_Mode;				// specifies the SPI operating Mode @ref SPI_Device_Mode_define

	uint_16 Communication_Mode;			// specifies the SPI Bidirectional  Mode state  @ref SPI_Communication_Mode_define
	uint_8 Slave_Mode;					// specifies the SPI slave device Number ( point to point OR multi slave) @ref SPI_Slave_Mode_define

	uint_16 Frame_Format;				// specifies the LSB OR MSB  @ref SPI_Frame_Format_define

	uint_16 DataSize;					// specifies the DataSize  @ref  SPI_DataSize_define

	uint_16 CLKPolarity;				// specifies the CLKPolarity  @ref  SPI_CLKPolarity_define

	uint_16 CLKPhase;			     	// specifies the CLKPhase  @ref  SPI_CLKPhase_define

	uint_16 NSS;			     	    // specifies  whether  the NSS Signal is managed by
										// Hardware(NSS pin )  OR  Software (SSI Bit) @ref  SPI_NSS_define

	uint_16 SPI_BaudRatePrescaler;	    // @ref  SPI_BaudRatePrescaler_define

	IRQ_SRC IRQ_Enable;				// @ref  SPI_IRQ_Enable_define

	void(*P_IRQ_CallBack)(IRQ_SRC irq_src);
}SPI_Config;





//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref SPI_Device_Mode_define
#define SPI_Device_Mode_Master				(uint_16)(1<<SPI_Master_Slave_Bit)			//Bit2 = 1 in CR1
#define SPI_Device_Mode_Slave				(uint_16)(0)		   					//Bit2 = 0 in CR1


// @ref SPI_Communication_Mode_define

//Bits 10 , 14 , 15 in CR1
#define SPI_Communication_Mode_2_lines_Full_duplex			(uint_16)(0)
#define SPI_Communication_Mode_2_lines_Receive_only			(uint_16)(1<<10)
#define SPI_Communication_Mode_1_line_Receive_only			(uint_16)(1<<15) // and bit 14 = 0
#define SPI_Communication_Mode_1_line_transmit_only			(uint_16)((1<<15) | (1<<14))

//@ref SPI_Slave_Mode_define
#define SPI_Slave_Mode_Point_to_Point			(uint_8)0
#define SPI_Slave_Mode_multi_slave			    (uint_8)1

//@ref SPI_Frame_Format_define
#define SPI_Frame_Format_MSB			(uint_16)(0)		    //Bit7 = 0 in CR1
#define SPI_Frame_Format_LSB			(uint_16)(1<<7)			//Bit7 = 1 in CR1

// @ref  SPI_DataSize_define
#define SPI_DataSize_8Bit				(uint_16)(0)		    //Bit11 = 0 in CR1
#define SPI_DataSize_16Bit				(uint_16)(1<<11)		//Bit11 = 1 in CR1

//@ref  SPI_CLKPolarity_define
#define SPI_CLKPolarity_high_level_idle_state   (uint_16)(1<<1)		    //Bit1 = 1 in CR1
#define SPI_CLKPolarity_low_level_idle_state	(uint_16)(0)		    //Bit1 = 0 in CR1


//@ref  SPI_CLKPhase_define
#define  SPI_CLKPhase_1_edge_first_data_capture_edge				(uint_16)(0)		    //Bit0 = 0 in CR1
#define  SPI_CLKPhase_2_edge_first_data_capture_edge				(uint_16)(1<<0)		    //Bit0 = 1 in CR1

//@ref  SPI_NSS_define
//Hardware
#define SPI_NSS_By_Hardware_Slave									(uint_16)(0)		            //Bit9 = 0 in CR1
#define SPI_NSS_By_Hardware_Master_SS_Output_Enable					(uint_16)(1<<2)					//CR2 bit2=1 and CR1 bit9 =0
#define SPI_NSS_By_Hardware_Master_SS_Output_Disable				(uint_16)~(1<<2)				//CR2 bit2=0 and CR1 bit9 =0
//Software
#define SPI_NSS_By_Software_Active_HIGH								(uint_16)((1<<9)|(1<<8))		//Bit9 = 1 and Bit8 = 1 in CR1
#define SPI_NSS_By_Software_Active_LOW								(uint_16)(1<<9)		            //Bit9 = 1 and Bit8 = 0 in CR1





//@ref  SPI_BaudRatePrescaler_define
//Bits 3:5  CR1
#define SPI_BaudRatePrescaler_fPCLK_by_2		(uint_16)(0)
#define SPI_BaudRatePrescaler_fPCLK_by_4		(uint_16)(1<<3)
#define SPI_BaudRatePrescaler_fPCLK_by_8		(uint_16)(0b010<<3)
#define SPI_BaudRatePrescaler_fPCLK_by_16		(uint_16)(0b011<<3)
#define SPI_BaudRatePrescaler_fPCLK_by_32		(uint_16)(0b100<<3)
#define SPI_BaudRatePrescaler_fPCLK_by_64		(uint_16)(0b101<<3)
#define SPI_BaudRatePrescaler_fPCLK_by_128		(uint_16)(0b110<<3)
#define SPI_BaudRatePrescaler_fPCLK_by_256		(uint_16)(0b111<<3)



// @ref  SPI_IRQ_Enable_define
// for each IRQ source
#define 	SPI_IRQ_Enable_Enable				(uint_8)1
#define 	SPI_IRQ_Enable_Disable				(uint_8)0
//put in all_IRQ in variable
#define 	SPI_IRQ_Enable_all_Disable			(uint_8)0



/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/


void MCAL_SPI_Init(SPI_t * SPIx , SPI_Config * SPI_config);
void MCAL_SPI_DeInit(SPI_t * SPIx);
void MCAL_SPI_GPIO_Set_Pins(SPI_t * SPIx);
void MCAL_SPI_SendData(SPI_t * SPIx , uint_16 data , enum Polling_mechism PollingEN);
void MCAL_SPI_ReceiveData(SPI_t * SPIx , uint_16 * data , enum Polling_mechism PollingEN);
void MCAL_SPI_Send_and_ReceiveData(SPI_t * SPIx , uint_16 * data , enum Polling_mechism PollingEN);

#endif /* STM32_F103C6_DRIVERS_INC_STM32_F103C6_SPI_DRIVER_H_ */
