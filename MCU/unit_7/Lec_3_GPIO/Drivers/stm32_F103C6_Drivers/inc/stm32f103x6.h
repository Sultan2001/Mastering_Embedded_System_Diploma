/*
 * stm32f103x6.h
 *
 *  Created on: Aug 5, 2024
 *      Author: UAS
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_


//-----------------------------
//Includes
//-----------------------------
#include "stdlib.h"
#include <stdint.h>
#include "Platform_Types.h"

//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_Memory_BASE						0x08000000UL
#define System_Memory_BASE						0x1FFFF000UL
#define SRAM_Memory_BASE						0x20000000UL


#define Peripherals_BASE						0x40000000UL
#define Cortex_M3_Internal_Peripherals_BASE		0xE0000000UL


//-----------------------------
//Base addresses for AHB  Peripherals
//-----------------------------
 // RCC
#define RCC_BASE								 0x40021000UL



//-----------------------------
//Base addresses for APB1  Peripherals
//-----------------------------





//-----------------------------
//Base addresses for APB2  Peripherals
//-----------------------------
// GPIO
// A,B fully included in LQFP48 Package
#define GBIOA_BASE								 0x40010800UL
#define GBIOB_BASE								 0x40010C00UL

// C,D Partial included in LQFP48 Package
#define GBIOC_BASE								 0x40011000UL
#define GBIOD_BASE								 0x40011400UL

// E not included in LQFP48 Package
#define GBIOE_BASE								 0x40011800UL

//EXTI
#define EXTI_BASE								 0x40010400UL

//AFIO
#define AFIO_BASE								 0x40010000UL





//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint_32	 CRL;
	vuint_32	 CRH;
	vuint_32	 IDR;
	vuint_32	 ODR;
	vuint_32	 BSRR;
	vuint_32	 BRR;
	vuint_32	 LCKR;

}GPIO_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	vuint_32	 CR;
	vuint_32	 CFGR;
	vuint_32	 CIR;
	vuint_32	 APB2RSTR;
	vuint_32	 APB1RSTR;
	vuint_32	 AHBENR;
	vuint_32	 APB2ENR;
	vuint_32	 APB1ENR;
	vuint_32	 BDCR;
	vuint_32	 CSR;
	vuint_32	 AHBSTR;
	vuint_32	 CFGR2;


}RCC_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	vuint_32	 IMR;
	vuint_32	 EMR;
	vuint_32	 RTSR;
	vuint_32	 FTSR;
	vuint_32	 SWIER;
	vuint_32	 PR;


}EXTI_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	vuint_32	 EVCR;
	vuint_32	 MAPR;
	vuint_32	 EXTICR1;
	vuint_32	 EXTICR2;
	vuint_32	 EXTICR3;
	vuint_32	 EXTICR4;
	vuint_32	 RESERVED0;
	vuint_32	 MAPR2;

}AFIO_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA					((GPIO_t *) GBIOA_BASE)
#define GPIOB					((GPIO_t *) GBIOB_BASE)
#define GPIOC					((GPIO_t *) GBIOC_BASE)
#define GPIOD					((GPIO_t *) GBIOD_BASE)
#define GPIOE					((GPIO_t *) GBIOE_BASE)

#define RCC						((RCC_t *) RCC_BASE)

#define AFIO					((AFIO_t *) AFIO_BASE)

#define EXTI					((EXTI_t *) EXTI_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLK_EN()     (RCC->APB2ENR |=1<<2)
#define RCC_GPIOB_CLK_EN()     (RCC->APB2ENR |=1<<3)
#define RCC_GPIOC_CLK_EN()     (RCC->APB2ENR |=1<<4)
#define RCC_GPIOD_CLK_EN()     (RCC->APB2ENR |=1<<5)
#define RCC_GPIOE_CLK_EN()     (RCC->APB2ENR |=1<<6)

#define RCC_AFIO_CLK_EN()     (RCC->APB2ENR |=1<<0)


//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define READ_BIT(NUM,POS)	(((NUM)>>POS)&1)
#define SET_BIT(NUM,POS)	((NUM) |= 1<<POS)
#define RESET_BIT(NUM,POS)	((NUM) &= ~(1<<POS))
#define TOGGLE_BIT(NUM,POS)	((NUM) ^= 1<<POS)






#endif /* INC_STM32F103X6_H_ */
