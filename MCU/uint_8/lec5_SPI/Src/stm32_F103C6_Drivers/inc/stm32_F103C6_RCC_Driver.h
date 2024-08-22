/*
 * stm32_F103C6_RCC_Driver.h
 *
 *  Created on: Aug 10, 2024
 *      Author: mohamed sultan
 */

#ifndef STM32_F103C6_DRIVERS_INC_STM32_F103C6_RCC_DRIVER_H_
#define STM32_F103C6_DRIVERS_INC_STM32_F103C6_RCC_DRIVER_H_



//-----------------------------
//Includes
//-----------------------------
#include "Platform_Types.h"
#include "stm32f103x6.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------


//-----------------------------
//Macros Configuration References
//-----------------------------
#define HSI 8000000
#define HSE 8000000

/*@ref Module_REF_NAME_define
*/


/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

uint_32 MCAL_RCC_Getsys_CLCKFerq();
uint_32 MCAL_RCC_GetHCLCKFerq();
uint_32 MCAL_RCC_GetPCLCK1Ferq();
uint_32 MCAL_RCC_GetPCLCK2Ferq();

#endif /* STM32_F103C6_DRIVERS_INC_STM32_F103C6_RCC_DRIVER_H_ */
