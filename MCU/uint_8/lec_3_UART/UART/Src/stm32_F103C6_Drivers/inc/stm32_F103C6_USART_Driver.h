/*
 * stm32_F103C6_USART_Driver.h
 *
 *  Created on: Aug 10, 2024
 *      Author: mohamed sultan
 */

#ifndef STM32_F103C6_DRIVERS_INC_STM32_F103C6_USART_DRIVER_H_
#define STM32_F103C6_DRIVERS_INC_STM32_F103C6_USART_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"
#include "stm32_F103C6_RCC_Driver.h"
#include "stm32_F103C6_GPIO_Driver.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef union{
	 struct
	{
		uint_16    Transmit_data_register_empty :1 ;
		uint_16    CTS_flag :1 ;
		uint_16    Transmission_complete :1 ;
		uint_16    Received_data_ready_to_be_read :1 ;
		uint_16    Overrun_error_detected :1 ;
		uint_16    Idle_line_detected :1 ;
		uint_16    Parity_error :1 ;
		uint_16    BreakFlag :1 ;
		uint_16    NoiseFlag_Overrun_error_and_Framing_error_in_multibuffer_communication :1;
		uint_16    reserved :7;
	}IRQ;
	uint_16 All_IRQ;

}IRQ_Enable_t;



typedef struct
{
	void(*Transmit_data_register_empty_IRQ_CallBack)();				// 1 : Data is transferred to the shift register
	void(*CTS_flag_IRQ_CallBack)();
	void(*Transmission_complete_IRQ_CallBack)();
	void(*Received_data_ready_to_be_read_IRQ_CallBack)();
	void(*Overrun_error_detected_IRQ_CallBack)();
	void(*Idle_line_detected_IRQ_CallBack)();
	void(*Parity_error_IRQ_CallBack)();
	void(*BreakFlag_IRQ_CallBack)();
	void(*NoiseFlag_Overrun_error_and_Framing_error_in_multibuffer_communication_IRQ_CallBack)();

}IRQ_pointers_FUN_t;

typedef struct
{
	uint_32 USART_Mode;			// specifies TX/RX Enable/Disable
								//this parameter must be set based on @ref USART_Mode_define

	uint_32 BaudRate;			// this number configures UART communication baud rate
								//this parameter must be set based on @ref USART_BaudRate_define

	uint_32 Payload_Length;		//specifies the number of data bits transmitted or received in a frame
								//this parameter must be set based on @ref USART_Payload_Length_define

	uint_32 Parity;				// specifies THE Parity MODE (even , odd , none)
								//this parameter must be set based on @ref USART_Parity_define

	uint_32 stop_Bits;			// specifies the number of stop bits transmitted
								//this parameter must be set based on @ref USART_stopBits_define

	uint_32 HwflowCtrl;			//specifies whether the Hardware flowControl mode is Enable OR Disable
								//this parameter must be set based on @ref USART_HwflowCtrl_define

	IRQ_Enable_t IRQ_Enable;	// Enable OR Disable UART IRQ  TX/RX
								//this parameter must be set based on @ref USART_IRQ_Enable_define

	IRQ_pointers_FUN_t P_FUN;

}USART_PinConfig_t;

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref USART_Mode_define
#define USART_Mode_RX		(uint_32)(1<<2) // Bit 2 RE: Receiver enable
#define USART_Mode_TX		(uint_32)(1<<3) //Bit 3 TE: Transmitter enable
#define USART_Mode_TX_RX	(uint_32)((1<<2) | (1<<3) )

//@ref USART_BaudRate_define
#define USART_BaudRate_2400						2400
#define USART_BaudRate_9600						9600
#define USART_BaudRate_19200					19200
#define USART_BaudRate_57600					57600
#define USART_BaudRate_115200					115200
#define USART_BaudRate_230400					230400
#define USART_BaudRate_460000					460000
#define USART_BaudRate_921600					921600
#define USART_BaudRate_2250000					2250000
#define USART_BaudRate_4500000					4500000

//@ref USART_Payload_Length_define
#define USART_Payload_Length_8bits				(uint_32)0			// 0: 1 Start bit, 8 Data bits | Bit 12 M: Word length
#define USART_Payload_Length_9bits				(uint_32)(1<<12)	// 1: 1 Start bit, 9 Data bits | Bit 12 M: Word length


//@ref USART_Parity_define
#define USART_Parity_even						(uint_32)((1<<10)
#define USART_Parity_odd						(uint_32)((1<<10)|(1<<9))
#define USART_Parity_none						(uint_32)0


//@ref USART_stopBits_define
//Bits 13:12 STOP: STOP bits
// These bits are used for programming the stop bits.
#define USART_stopBits_1						(uint_32)(0)
#define USART_stopBits_half						(uint_32)(0b01<<12)
#define USART_stopBits_2						(uint_32)(0b10<<12)
#define USART_stopBits_1_half					(uint_32)(0b11<<12)


//@ref USART_HwflowCtrl_define

#define USART_HwflowCtrl_none							(uint_32)0
#define USART_HwflowCtrl_RTS							(uint_32)(1<<8)
#define USART_HwflowCtrl_CTS							(uint_32)(1<<9)
#define USART_HwflowCtrl_RTS_CTS						(uint_32)((1<<9)|(1<<8))


//@ref USART_IRQ_Enable_define
#define USART_IRQ_Enable_Enable				(uint_8)1
#define USART_IRQ_Enable_Disable			(uint_8)0

enum Polling_mechism
{
	Enable,
	Disable
};


/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/


void MCAL_UART_Init(USART_t * USARTx , USART_PinConfig_t * UART_Config);
void MCAL_UART_DEInit(USART_t * USARTx);

void MCAL_UART_GPIO_Set_Pins( USART_t * UARTx);
void MCAL_UART_SendData(USART_t * USARTx , uint_16 data , enum Polling_mechism PollingEN);

void MCAL_UART_ReceiveData(USART_t * USARTx , uint_16 * data , enum Polling_mechism PollingEN);
void MCAL_UART_Wait_TD(USART_t * USARTx);

#endif /* STM32_F103C6_DRIVERS_INC_STM32_F103C6_USART_DRIVER_H_ */
