/**
 ******************************************************************************
 * @file           : main.c
 * @author         : mohamed sultan
 * @brief          : Main program body
 ******************************************************************************
 */

#include "Platform_Types.h"


#define SYSCTL_RCGC2_R       *((vuint_32 *)(0x400FE108))
#define GPIO_PORTF_DATA_R     *((vuint_32 *)(0x400253FC))
#define GPIO_PORTF_DIR_R     *((vuint_32 *)(0x40025400))
#define GPIO_PORTF_DEN_R    *((vuint_32 *)(0x4002551C))




vuint_32 i=0;



int main(void)
{

SYSCTL_RCGC2_R = 0x20;
//delay to make sure GPIOf is up and running
for (i=0; i<200 ; i++);

GPIO_PORTF_DIR_R |=1<<3;
GPIO_PORTF_DEN_R |=1<<3;


	

	while(1)
	{
		GPIO_PORTF_DATA_R |=1<<3;

		for( i = 0 ; i<50000; i++);

		GPIO_PORTF_DATA_R &=~(1<<3);
		for(i = 0 ; i<50000; i++);

	}

	return 0;
}





