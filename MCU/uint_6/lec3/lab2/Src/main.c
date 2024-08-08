/**
 ******************************************************************************
 * @file           : main.c
 * @author         : mohamed sultan
 * @brief          : Main program body
 ******************************************************************************
 */

#include "Platform_Types.h"

#define RCC_BASE   0x40021000
#define PORTA_BASE 0x40010800

#define RCC_APB2ENR *((vuint_32 *)(RCC_BASE + 0x18))
#define GPIO_CRH    *((vuint_32 *)(PORTA_BASE + 0x04))
#define GPIO_ODR    *((vuint_32 *)(PORTA_BASE + 0x0C))
#define RCC_CFGR   *((vuint_32 *)(RCC_BASE + 0x04))



vuint_32 i=0;

typedef union {
	vuint_32 all_fields;
	struct{
		vuint_32 reserved :13;
		vuint_32 pin13:1;

	}Pin;


}R_ODR_t;

volatile R_ODR_t *R_ODR =(volatile R_ODR_t*)(PORTA_BASE + 0x0C);
int main(void)
{

	/*
	 *  Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	 Set and cleared by software to control the division factor of the APB high-speed clock
	(PCLK2).
	 0xx: HCLK not divided
	 100: HCLK divided by 2
	 	 101: HCLK divided by 4
	 110: HCLK divided by 8
	 111: HCLK divided by 16
	 *
	 */
	RCC_CFGR |=(0b101<<11);


	/*
	 *  Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
 Set and cleared by software to control the division factor of the APB low-speed clock
(PCLK1).
 Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
 0xx: HCLK not divided
 	 100: HCLK divided by 2
 101: HCLK divided by 4
 110: HCLK divided by 8
 111: HCLK divided by 16
	 *
	 */
	RCC_CFGR |=(0b100<<8);

	RCC_APB2ENR |=1<<2;
	GPIO_CRH &=0xff0fffff;
	GPIO_CRH |=0x00200000;

	while(1)
	{
		//GPIO_ODR |=1<<13;//set bit 3
		R_ODR->Pin.pin13=1;
		for( i = 0 ; i<50000; i++);

		//GPIO_ODR &=~(1<<13); // clear bit 13
		R_ODR->Pin.pin13=0;
		for(i = 0 ; i<50000; i++);

	}

	return 0;
}


