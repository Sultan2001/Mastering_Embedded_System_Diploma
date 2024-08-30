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

#include "stm32_F103C6_GPIO_Driver.h"
#include "stm32_F103C6_EXTI_Driver.h"
#include "stm32f103x6.h"
void Read_Control_Reg(uint_32* value );
void Read_IPSR_Reg(uint_32* value );

uint_32 val1 =0;
uint_32 val2 =3;
uint_32 val3 =3 , val4,val5;
void RCC_init()
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

}
void GPIO_init()
{
	GPIO_PinConfig_t PinConfg;
	PinConfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinConfg.GPIO_PinNumber=GPIO_PIN_0;
	PinConfg.GPIO_OUTPUT_Speed=GPIO_SPEED_10MHz;
	MCAL_GPIO_Init(GPIOA, &PinConfg);

}
void EXTI_CallBack()
{
	// lab6
		// CPU in handler mode
	Read_IPSR_Reg(&val5);
	MCAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
}

void EXTI_init()
{
	EXTI_PinConfig_t EXTI_config;
	EXTI_config.EXTI_Pin = EXTI10PB10;
	EXTI_config.Trigger_Case = EXTI_Trigger_RISING;
	EXTI_config.IRQ_EN=EXTI_IRQ_Enable;
	EXTI_config.P_IRQ_CallBack=EXTI_CallBack;
	MCAL_EXTI_GPIO_Init(&EXTI_config);

}
int main(void)
{
	RCC_init();
	GPIO_init();
	EXTI_init();

	__asm("NOP  \n\t NOP \n\t NOP");
//move 0xff to val1
__asm("mov %0 , #0xff"
		:"=r" (val1)		// first output parameters

		);

	__asm("NOP  \n\t NOP \n\t NOP");
// move val2 to r0
__asm("mov r0 , %0"
		:				// first output parameters
		:"r"(val2)		// second  input parameters
		);

	__asm("NOP  \n\t NOP \n\t NOP");

	// add val1 and val2 in val3
	__asm("add %0,%1,%2"
			:"=r" (val3)  				// first output parameters
			:"r" (val1) , "r" (val2)   // second  input parameters
			);
	__asm("NOP  \n\t NOP \n\t NOP");
// lab6
	// CPU in thread mode
	Read_Control_Reg(&val4);

	while(1)
	{

	}
}

void Read_Control_Reg(uint_32* value )
{
	__asm("NOP  \n\t NOP \n\t NOP");

	__asm("MRS  %[out] , CONTROL"
			:[out] "=r" (*value) );

	__asm("NOP  \n\t NOP \n\t NOP");
}


void Read_IPSR_Reg(uint_32* value )
{
	__asm("NOP  \n\t NOP \n\t NOP");

	__asm("MRS  %[out] , IPSR"
			:[out] "=r" (*value) );

	__asm("NOP  \n\t NOP \n\t NOP");
}
