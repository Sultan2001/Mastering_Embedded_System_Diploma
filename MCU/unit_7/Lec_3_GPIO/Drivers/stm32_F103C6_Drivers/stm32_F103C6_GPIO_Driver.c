/*
 *  stm32_F103C6_GPIO_Driver.c
 *
 *  Created on: Aug 5, 2024
 *  	Author: Mohamed Sultan
 */

//-----------------------------
//Includes
//-----------------------------

#include "stm32_F103C6_GPIO_Driver.h"

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

static uint_8 get_CRLH_postion(uint_16 PinNumber);






/**================================================================
 * @Fn			- MCAL_GPIO_Init
 * @brief 		- Initializes the GPIOx PINy according to the specified parameters in PinConfig
 * @param [in]	- GPIOx : where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	- PinConfig: pointer to GPIO_PinConfig_t structure  that contains
 * 				  the configuration information for the specified GPIO Pin
 * @retval 		- none
 * Note			- none
 */
void MCAL_GPIO_Init (GPIO_t * GPIOx , GPIO_PinConfig_t * PinConfig)
{
	//CRL pin 0 --> 7
	//CRL pin 8 --> 15
	uint_8 pin_postion = get_CRLH_postion(PinConfig->GPIO_PinNumber);
	uint_8 PIN_config_data =0;



	vuint_32 * ConfigReg = NULL;
	ConfigReg = PinConfig->GPIO_PinNumber < GPIO_PINS_8 ? &GPIOx->CRL : &GPIOx->CRH;
	//Clear CNF & MODE
	(*ConfigReg) &= ~ (0xf<<pin_postion);
	switch(PinConfig->GPIO_Mode)
	{
	case GPIO_MODE_OUTPUT_AF_OD:
	case GPIO_MODE_OUTPUT_AF_PP:
	case GPIO_MODE_OUTPUT_OD:
	case GPIO_MODE_OUTPUT_PP:
		PIN_config_data = (((PinConfig->GPIO_Mode - 4) << 2) | PinConfig->GPIO_OUTPUT_Speed) & 0x0f;
		(*ConfigReg) |= (PIN_config_data << pin_postion);
		break;
	case GPIO_MODE_Analog:
	case GPIO_MODE_INPUT_FLO:

		PIN_config_data = PinConfig->GPIO_Mode << 2 ;
		//Write on CRL OR CRH
		(*ConfigReg) |= (PIN_config_data << pin_postion);
		break;
	case GPIO_MODE_AF_INPUT:
		PIN_config_data = GPIO_MODE_INPUT_FLO << 2 ;
		//Write on CRL OR CRH
		(*ConfigReg) |= (PIN_config_data << pin_postion);
		break;

	case GPIO_MODE_INPUT_PU:
	case GPIO_MODE_INPUT_PD:
		PIN_config_data = GPIO_MODE_INPUT_PU << 2 ;
		//Write on CRL OR CRH
		(*ConfigReg) |= (PIN_config_data << pin_postion);

		if(PinConfig->GPIO_Mode == GPIO_MODE_INPUT_PU)
		{
			(GPIOx->ODR) |=  PinConfig->GPIO_PinNumber;
		}
		else
		{
			(GPIOx->ODR) &= ~(PinConfig->GPIO_PinNumber);
		}

		break;
	}

}

/**================================================================
 * @Fn			- MCAL_GPIO_DeInit
 * @brief 		- Reset All the GPIO Register
 * @param [in]	- GPIOx : where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval 		- none
 * Note			- none
 */
void MCAL_GPIO_DeInit (GPIO_t * GPIOx )
{
	if(GPIOx == GPIOA)
	{
		(RCC->APB1RSTR) |=1<<2;
		(RCC->APB1RSTR) &=~(1<<2);
	}
	else if(GPIOx == GPIOB)
	{
		(RCC->APB1RSTR) |=1<<3;
		(RCC->APB1RSTR) &=~(1<<3);
	}
	else if(GPIOx == GPIOC)
	{
		(RCC->APB1RSTR) |=1<<4;
		(RCC->APB1RSTR) &=~(1<<4);
	}
	else if(GPIOx == GPIOD)
	{
		(RCC->APB1RSTR) |=1<<5;
		(RCC->APB1RSTR) &=~(1<<5);
	}

	else if(GPIOx == GPIOE)
	{
		(RCC->APB1RSTR) |=1<<6;
		(RCC->APB1RSTR) &=~(1<<6);
	}


}



/**================================================================
 * @Fn			- MCAL_GPIO_ReadPin
 * @brief 		- Read specific PIN
 * @param [in]	- GPIOx : where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	- pinNumber: Set Pin Number according to @ref GPIO_PINS_define
 * @retval 		- the Input Pin value (two value based on @ref GPIO_PINS_State_define)
 * Note			- none
 */
uint_8 MCAL_GPIO_ReadPin (GPIO_t * GPIOx , uint_16 pinNumber)
{
	uint_8 logic=0;
	if((GPIOx->IDR & pinNumber) != (uint_32) GPIO_PINS_State_RESET)
	{
		logic =GPIO_PINS_State_SET;
	}
	else
	{
		logic =GPIO_PINS_State_RESET;
	}

return logic;

}


/**================================================================
 * @Fn			- MCAL_GPIO_ReadPort
 * @brief 		- Read specific Port
 * @param [in]	- GPIOx : where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval 		- the Input Port
 * Note			- none
 */
uint_16 MCAL_GPIO_ReadPort (GPIO_t * GPIOx )
{
	uint_16 Portvalue=(uint_16)GPIOx->IDR;
	return Portvalue;

}




/**================================================================
 * @Fn			- MCAL_GPIO_WritePin
 * @brief 		- Write Logic in  specific PIN
 * @param [in]	- GPIOx : where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	- pinNumber: Set Pin Number according to @ref GPIO_PINS_define
 * @param [in]   - value : the Output Pin value (two value based on @ref GPIO_PINS_State_define)
 * @retval 		- none
 * Note			- none
 */
void MCAL_GPIO_WritePin (GPIO_t * GPIOx ,uint_16 pinNumber, uint_8 value)
{
	if(value != GPIO_PINS_State_RESET)
	{
		//GPIOx->ODR |=  pinNumber; OR

//	     GPIOx_BSRR
//		 BSy: Port x Set bit y (y= 0 .. 15)
//		 These bits are write-only and can be accessed in Word mode only.
//		 0: No action on the corresponding ODRx bit
//		 1: Set the corresponding ODRx bit
		GPIOx->BSRR =(uint_32) pinNumber;

	}
	else
	{
//		 GPIOx_BRR
//		 Bits 15:0BRy: Port x Reset bit y (y= 0 .. 15)
//		 These bits are write-only and can be accessed in Word mode only.
//	     0: No action on the corresponding ODRx bit
//		 1: Reset the corresponding ODRx bit
		GPIOx->BRR = (uint_32)pinNumber;
	}
}

/**================================================================
 * @Fn			- MCAL_GPIO_WritePort
 * @brief 		- Write Logic in  specific Port
 * @param [in]	- GPIOx : where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in]   - value : the Output Port value
 * @retval 		- none
 * Note			- none
 */
void MCAL_GPIO_WritePort (GPIO_t * GPIOx,uint_16 value )
{
	GPIOx->ODR=(uint_32)value;
}

/**================================================================
 * @Fn			- MCAL_GPIO_ToggelPin
 * @brief 		- Toggle specific PIN
 * @param [in]	- GPIOx : where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	- pinNumber: Set Pin Number according to @ref GPIO_PINS_define
 * @retval 		- none
 * Note			- none
 */

void MCAL_GPIO_TogglePin (GPIO_t * GPIOx ,uint_16 pinNumber)
{
	GPIOx->ODR ^=pinNumber;
}

/**================================================================
 * @Fn			- MCAL_GPIO_LockPin
 * @brief 		- Lock specific PIN
 * @param [in]	- GPIOx : where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	- pinNumber: Set Pin Number according to @ref GPIO_PINS_define
 * @retval 		- OK if PinConfig is Locked Or ERROR if Pin Not Locked according to @ref GPIO_LOCK_PIN_define
 * Note			- none
 */
uint_8 MCAL_GPIO_LockPin (GPIO_t * GPIOx ,uint_16 pinNumber)
{
//	 Bit 16 LCKK[16]: Lock key
//	 This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
//	 0: Port configuration lock key not active
//	 1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
//	 LOCK key writing sequence:
//	 Write 1
//	 Write 0
//	 Write 1
//	 Read 0
//	 Read 1 (this read is optional but confirms that the lock is active)
//	 Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
//	 Any error in the lock sequence will abort the lock.
//	 Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
//	 These bits are read write but can only be written when the LCKK bit is 0.
//	 0: Port configuration not locked
//	 1: Port configuration locked.

	// 	select pin to LOCK it
	GPIOx->LCKR = pinNumber;
	//	 LOCK key writing sequence:
	SET_BIT(GPIOx->LCKR , 16);
	RESET_BIT(GPIOx->LCKR , 16);
	SET_BIT(GPIOx->LCKR , 16);
	// cheak
	if(READ_BIT(GPIOx->LCKR , 16))
	{
		return GPIO_LOCK_PIN_OK;
	}
	else
	{
		return GPIO_LOCK_PIN_ERROR;
	}

}

static uint_8 get_CRLH_postion(uint_16 PinNumber)
{
	uint_8 ret =0;
	switch(PinNumber)
	{
	case GPIO_PINS_0 :
	case GPIO_PINS_8 :
		ret=0;
		break;
	case GPIO_PINS_1 :
	case GPIO_PINS_9 :
		ret=4;
		break;
	case GPIO_PINS_2 :
	case GPIO_PINS_10 :
		ret=8;
		break;
	case GPIO_PINS_3 :
	case GPIO_PINS_11 :
		ret=12;
		break;
	case GPIO_PINS_4 :
	case GPIO_PINS_12 :
		ret=16;
		break;
	case GPIO_PINS_5 :
	case GPIO_PINS_13 :
		ret=20;
		break;
	case GPIO_PINS_6 :
	case GPIO_PINS_14 :
		ret=24;
		break;
	case GPIO_PINS_7 :
	case GPIO_PINS_15 :
		ret=28;
		break;
	}
	return ret;
}
