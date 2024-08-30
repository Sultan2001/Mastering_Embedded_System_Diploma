/*
 * stm32_F103C6_GPIO_Driver.h
 *
 *  Created on: Aug 5, 2024
 *      Author: Mohamed sultan
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVER_H_
#define INC_STM32_F103C6_GPIO_DRIVER_H_




//-----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"
//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
uint_16	GPIO_PinNumber; 	//	specifies the GPIO pins to be configured
							// this parameter must be a value of @ref GPIO_PIN_define

uint_8 GPIO_Mode;     		//	specifies the Operating mode for the selected pin
							// this parameter can be a value of @ref GPIO_MODE_define

uint_8 GPIO_OUTPUT_Speed;	//specifies the Speed for the selected pin
							// this parameter can be a value of @ref GPIO_SPEED_define

}GPIO_PinConfig_t;




//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref GPIO_PIN_define
#define GPIO_PIN_0			((uint_16)0x0001)		// Pin 0 selected
#define GPIO_PIN_1			((uint_16)0x0002)		// Pin 1 selected  10
#define GPIO_PIN_2			((uint_16)0x0004)		// Pin 2 selected  100
#define GPIO_PIN_3			((uint_16)0x0008)		// Pin 3 selected  1000
#define GPIO_PIN_4			((uint_16)0x0010)		// Pin 4 selected  1 0000
#define GPIO_PIN_5			((uint_16)0x0020)		// Pin 5 selected  10 0000
#define GPIO_PIN_6			((uint_16)0x0040)		// Pin 6 selected  100 0000
#define GPIO_PIN_7			((uint_16)0x0080)		// Pin 7 selected  1000 0000
#define GPIO_PIN_8			((uint_16)0x0100)		// Pin 8 selected  1 0000 0000
#define GPIO_PIN_9			((uint_16)0x0200)		// Pin 9 selected  10 0000 0000
#define GPIO_PIN_10		((uint_16)0x0400)		// Pin 10 selected 100 0000 0000
#define GPIO_PIN_11		((uint_16)0x0800)		// Pin 11 selected
#define GPIO_PIN_12		((uint_16)0x1000)		// Pin 12 selected
#define GPIO_PIN_13		((uint_16)0x2000)		// Pin 13 selected
#define GPIO_PIN_14		((uint_16)0x4000)		// Pin 14 selected
#define GPIO_PIN_15		((uint_16)0x8000)		// Pin 15 selected 1000 0000 0000 0000 = 32,768 DEC


//@ref GPIO_MODE_define
#define GPIO_MODE_Analog			0 		// Analog mode
#define GPIO_MODE_INPUT_FLO			1		// Floating input
#define GPIO_MODE_INPUT_PU			2		// Input with pull-up
#define GPIO_MODE_INPUT_PD			3		// Input with pull-down
#define GPIO_MODE_OUTPUT_PP			4		// General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD			5		// General purpose output Open-drain
#define GPIO_MODE_OUTPUT_AF_PP		6		//  Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD		7		// Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT			8		// Alternate function INPUT



//@ref GPIO_SPEED_define
#define GPIO_SPEED_10MHz	1 //Output mode, max speed 10 MHz.
#define GPIO_SPEED_2MHz 	2 //Output mode, max speed 2 MHz.
#define GPIO_SPEED_50MHz 	3 //Output mode, max speed 50 MHz


//@ref GPIO_PIN_State_define
#define GPIO_PIN_State_SET 	1
#define GPIO_PIN_State_RESET 	0


//@ref GPIO_LOCK_PIN_define
#define GPIO_LOCK_PIN_OK       	    1
#define GPIO_LOCK_PIN_ERROR         1




/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/


void MCAL_GPIO_Init (GPIO_t * gpio , GPIO_PinConfig_t * pin);
void MCAL_GPIO_DeInit (GPIO_t * GPIOx );

uint_8 MCAL_GPIO_ReadPin (GPIO_t * GPIOx ,uint_16 pinNumber);
uint_16 MCAL_GPIO_ReadPort (GPIO_t * GPIOx );

void MCAL_GPIO_WritePin (GPIO_t * GPIOx ,uint_16 pinNumber, uint_8 value);
void MCAL_GPIO_WritePort (GPIO_t * GPIOx,uint_16 value );

void MCAL_GPIO_TogglePin (GPIO_t * GPIOx ,uint_16 pinNumber);

uint_8 MCAL_GPIO_LockPin (GPIO_t * GPIOx ,uint_16 pinNumber);

#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
