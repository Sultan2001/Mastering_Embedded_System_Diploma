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




extern void H_fault_Handler(){

for( int i = 0 ; i<50000; i++);
}