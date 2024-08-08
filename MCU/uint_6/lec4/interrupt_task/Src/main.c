/**
 ******************************************************************************
 * @file           : main.c
 * @author         : mohamed sultan
 * @brief          : Main program body
 ******************************************************************************
 */

#include "Platform_Types.h"

#define RCC_BASE   	0x40021000
#define PORTA_BASE 	0x40010800
#define EXTI_BASE 	0x40010400
#define AFIO 		0x40010000
#define RCC_APB2ENR *((vuint_32 *)(RCC_BASE + 0x18))
#define GPIO_CRH    *((vuint_32 *)(PORTA_BASE + 0x04))
#define GPIO_ODR    *((vuint_32 *)(PORTA_BASE + 0x0C))
#define GPIO_CRL   *((vuint_32 *)(PORTA_BASE + 0x00))
#define AFIO_EXTICR1    *((vuint_32 *)(AFIO + 0x08))


#define EXTI_IMR    *((vuint_32 *)(EXTI_BASE + 0x00))
#define EXTI_RTSR    *((vuint_32 *)(EXTI_BASE + 0x08))
#define EXTI_PR    *((vuint_32 *)(EXTI_BASE + 0x14))

#define NVIC  *((vuint_32 *)(0xE000E100))

void clock_init()
{
 //IOPAEN: IO port A clock enable
	RCC_APB2ENR |=1<<2;
	// AFIOEN: Alternate function IO clock enable
	RCC_APB2ENR |=1<<0;
}

void GPIO_init()
{
	GPIO_CRH &=0xff0fffff;
	GPIO_CRH |=0x00200000;
	//pin A0 : 01: Floating input (reset state)
	GPIO_CRL |=1<<2;
}
vuint_32 i=0;




int main(void)
{
	clock_init();
	GPIO_init();
	AFIO_EXTICR1 |=0b0000<<0;
// ENEBLE EXTL0
	EXTI_IMR|=1<<0;

// Rising edge detection
	EXTI_RTSR |=1<<0;
// NVIC enable IRQ 6
	NVIC |=(1<<6);



	while(1)
	{




	}

	return 0;
}




void EXTI0_IRQHandler()
{
	EXTI_PR |=1<<0; //clear flag
	GPIO_ODR ^=1<<13;//toggel bit 3
}
