/*
 * stm32_F103C6_EXTI_Driver.c
 *
 *  Created on: Aug 7, 2024
 *      Author: mohamed sultan
 */


//-----------------------------
//Includes
//-----------------------------

#include "stm32_F103C6_EXTI_Driver.h"


//-----------------------------
//GV
//-----------------------------


static void(*GP_IRQ_CallBack[15])(void);
//-----------------------------
//Macros Configuration References
//-----------------------------

#define AFIO_GPIO_EXTI_Mapping(x)		((x) == GPIOA?0:\
										 (x) == GPIOB?1:\
										 (x) == GPIOC?2:\
										 (x) == GPIOD?3:0)
/*@ref Module_REF_NAME_define
*/


/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/
//Enable OR Disable NVIC
void ENABLE_NVIC(uint_8 LineNumber)
{
	switch(LineNumber)
	{
	case EXTI0:
		NVIC_IRQ6_EXTI0_Enable();
		break;
	case EXTI1:
		NVIC_IRQ7_EXTI1_Enable();
		break;
	case EXTI2:
		NVIC_IRQ8_EXTI2_Enable();
		break;
	case EXTI3:
		NVIC_IRQ9_EXTI3_Enable();
		break;
	case EXTI4:
		NVIC_IRQ10_EXTI4_Enable();
		break;

	case EXTI5:
	case EXTI6:
	case EXTI7:
	case EXTI8:
	case EXTI9:

		NVIC_IRQ23_EXTI5_9_Enable();
		break;
	case EXTI10:
	case EXTI11:
	case EXTI12:
	case EXTI13:
	case EXTI14:
	case EXTI15:
		NVIC_IRQ40_EXTI10_15_Enable();
		break;
	}
}
void DISABLE_NVIC(uint_8 LineNumber)
{
	switch(LineNumber)
	{
	case EXTI0:
		NVIC_IRQ6_EXTI0_Disable();
		break;
	case EXTI1:
		NVIC_IRQ7_EXTI1_Disable();
		break;
	case EXTI2:
		NVIC_IRQ8_EXTI2_Disable();
		break;
	case EXTI3:
		NVIC_IRQ9_EXTI3_Disable();
		break;
	case EXTI4:
		NVIC_IRQ10_EXTI4_Disable();
		break;

	case EXTI5:
	case EXTI6:
	case EXTI7:
	case EXTI8:
	case EXTI9:

		NVIC_IRQ23_EXTI5_9_Disable();
		break;
	case EXTI10:
	case EXTI11:
	case EXTI12:
	case EXTI13:
	case EXTI14:
	case EXTI15:
		NVIC_IRQ40_EXTI10_15_Disable();
		break;
	}
}
void EXTI_GPIO_Update(EXTI_PinConfig_t * EXTI_Config)
{
// 1- Pin configuration
	GPIO_PinConfig_t Pin_CFG={
									.GPIO_Mode=GPIO_MODE_AF_INPUT,
									.GPIO_PinNumber =  EXTI_Config->EXTI_Pin.GPIO_Pin
								};
	MCAL_GPIO_Init(EXTI_Config->EXTI_Pin.GPIO_Port, &Pin_CFG);

// 2- Update AFIO  to Route between EXTI Line With PORT A,B,C,D
	uint_8 AFIO_EXTICR_index = EXTI_Config->EXTI_Pin.EXTI_InputLineNumber / 4;

	uint_8 AFIO_EXTICR_bit_postion =  (EXTI_Config->EXTI_Pin.EXTI_InputLineNumber % 4)*4;

	// Clear the four bits
	AFIO->EXTICR[AFIO_EXTICR_index] &= ~(0x0f<<AFIO_EXTICR_bit_postion);
	// set the data
	AFIO->EXTICR[AFIO_EXTICR_index] |= ( (AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_Pin.GPIO_Port) & 0x0f) << AFIO_EXTICR_bit_postion );;
// 3- Update Rising and falling trigger
	//clear the four bits
	EXTI->RTSR &= ~(1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
	EXTI->FTSR &= ~(1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
	//set the data
	if(EXTI_Config->Trigger_Case == EXTI_Trigger_FALLING )
	{
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
	}
	else if(EXTI_Config->Trigger_Case == EXTI_Trigger_RISING_AND_FALLING)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);

	}
	else //EXTI_Trigger_RISING
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
	}
// 4- Enable Interrupt mask register
	EXTI->IMR |=1<<(EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
//5- Enable OR Disable NVIC

	if(EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		ENABLE_NVIC(EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
		GP_IRQ_CallBack[EXTI_Config->EXTI_Pin.EXTI_InputLineNumber]=EXTI_Config->P_IRQ_CallBack;

	}
	else
	{
		DISABLE_NVIC(EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
		GP_IRQ_CallBack[EXTI_Config->EXTI_Pin.EXTI_InputLineNumber]=NULL;

	}

}

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t * EXTI_Config)
{
	EXTI_GPIO_Update(EXTI_Config);
}
void MCAL_EXTI_GPIO_DeInit()
{
	EXTI->IMR   = 0x00000000;
	EXTI->EMR   = 0x00000000;
	EXTI->RTSR  = 0x00000000;
	EXTI->FTSR  = 0x00000000;
	EXTI->SWIER = 0x00000000;
	EXTI->PR    = 0xFFFFFFFF; //rc_w1  : cleared by writing a ‘1’ into the bit.
	 NVIC_IRQ6_EXTI0_Disable();
	 NVIC_IRQ7_EXTI1_Disable();
	 NVIC_IRQ8_EXTI2_Disable();
	 NVIC_IRQ9_EXTI3_Disable();
	 NVIC_IRQ10_EXTI4_Disable();
	 NVIC_IRQ23_EXTI5_9_Disable();
	 NVIC_IRQ40_EXTI10_15_Disable();


}

void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t * EXTI_Config)
{
	EXTI_GPIO_Update(EXTI_Config);
}




void EXTI0_IRQHandler(void)
{
	//cleared by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR , 0);
	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler(void)
{
	//cleared by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR , 1);
	GP_IRQ_CallBack[1]();
}
void EXTI2_IRQHandler(void)
{
	//cleared by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR , 2);
	GP_IRQ_CallBack[2]();
}
void EXTI3_IRQHandler(void)
{
	//cleared by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR , 3);
	GP_IRQ_CallBack[3]();
}
void EXTI4_IRQHandler(void)
{
	//cleared by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR , 4);
	GP_IRQ_CallBack[4]();
}
void EXTI9_5_IRQHandler(void)
{
	if(READ_BIT(EXTI->PR , 5)){SET_BIT(EXTI->PR , 5); GP_IRQ_CallBack[5]();}
	if(READ_BIT(EXTI->PR , 6)){SET_BIT(EXTI->PR , 6); GP_IRQ_CallBack[6]();}
	if(READ_BIT(EXTI->PR , 7)){SET_BIT(EXTI->PR , 7); GP_IRQ_CallBack[7]();}
	if(READ_BIT(EXTI->PR , 8)){SET_BIT(EXTI->PR , 8); GP_IRQ_CallBack[8]();}
	if(READ_BIT(EXTI->PR , 9)){SET_BIT(EXTI->PR , 9); GP_IRQ_CallBack[9]();}
}
void EXTI15_10_IRQHandler(void)
{
	if(READ_BIT(EXTI->PR , 10)){SET_BIT(EXTI->PR , 10); GP_IRQ_CallBack[10]();}
	if(READ_BIT(EXTI->PR , 11)){SET_BIT(EXTI->PR , 11); GP_IRQ_CallBack[11]();}
	if(READ_BIT(EXTI->PR , 12)){SET_BIT(EXTI->PR , 12); GP_IRQ_CallBack[12]();}
	if(READ_BIT(EXTI->PR , 13)){SET_BIT(EXTI->PR , 13); GP_IRQ_CallBack[13]();}
	if(READ_BIT(EXTI->PR , 14)){SET_BIT(EXTI->PR , 14); GP_IRQ_CallBack[14]();}
	if(READ_BIT(EXTI->PR , 15)){SET_BIT(EXTI->PR , 15); GP_IRQ_CallBack[15]();}

}
