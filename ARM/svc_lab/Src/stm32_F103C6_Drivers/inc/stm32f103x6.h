/*
 * stm32f103x6.h
 *
 *  Created on: Aug 5, 2024
 *      Author: mohamed sultan
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


// NVIC register map
#define NVIC_BASE								 0xE000E100UL
#define NVIC_ISER0								*(vuint_32*)(NVIC_BASE + 0x00)  // set IRQ 0 -> 31
#define NVIC_ISER1								*(vuint_32*)(NVIC_BASE + 0x04)  // set IRQ 32 -> 63
#define NVIC_ISER2								*(vuint_32*)(NVIC_BASE + 0x08)	// set IRQ 64 -> 67
#define NVIC_ICER0								*(vuint_32*)(NVIC_BASE + 0x80)	// Clear IRQ 0 -> 31
#define NVIC_ICER1								*(vuint_32*)(NVIC_BASE + 0x84)	// Clear IRQ 32 -> 63
#define NVIC_ICER2								*(vuint_32*)(NVIC_BASE + 0x88)	// Clear IRQ 64 -> 67



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
	vuint_32	 EXTICR[4];
//	vuint_32	 EXTICR1;
//	vuint_32	 EXTICR2;
//	vuint_32	 EXTICR3;
//	vuint_32	 EXTICR4;
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
//clock ICER Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLK_EN()     (RCC->APB2ENR |=1<<2)
#define RCC_GPIOB_CLK_EN()     (RCC->APB2ENR |=1<<3)
#define RCC_GPIOC_CLK_EN()     (RCC->APB2ENR |=1<<4)
#define RCC_GPIOD_CLK_EN()     (RCC->APB2ENR |=1<<5)
#define RCC_GPIOE_CLK_EN()     (RCC->APB2ENR |=1<<6)

#define RCC_AFIO_CLK_EN()     (RCC->APB2ENR |=1<<0)

//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC IRQ enable/disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//enable
#define NVIC_IRQ6_EXTI0_Enable()				(NVIC_ISER0 |= 1<<6)		// (NVIC_ISER0 |= 1<<EXTI0_IRQ)
#define NVIC_IRQ7_EXTI1_Enable()				(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Enable()				(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Enable()				(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Enable()				(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Enable()				(NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Enable()			(NVIC_ISER1 |= 1<<8) // 40 - 32 = 8

//disable

#define NVIC_IRQ6_EXTI0_Disable()				(NVIC_ICER0 |= 1<<6)		// (NVIC_ICER0 |= 1<<EXTI0_IRQ)
#define NVIC_IRQ7_EXTI1_Disable()				(NVIC_ICER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Disable()				(NVIC_ICER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Disable()				(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Disable()				(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Disable()			(NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Disable()			(NVIC_ICER1 |= 1<<8) // 40 - 32 = 8



//-*-*-*-*-*-*-*-*-*-*-*-
//IVT: Interrupt Vector table IRQ
//-*-*-*-*-*-*-*-*-*-*-*
#define EXTI0_IRQ		6
#define EXTI1_IRQ		7
#define EXTI2_IRQ		8
#define EXTI3_IRQ		9
#define EXTI4_IRQ		10
#define EXTI5_IRQ		23
#define EXTI6_IRQ		23
#define EXTI7_IRQ		23
#define EXTI8_IRQ		23
#define EXTI9_IRQ		23
#define EXTI10_IRQ		40
#define EXTI11_IRQ		40
#define EXTI12_IRQ		40
#define EXTI13_IRQ		40
#define EXTI14_IRQ		40
#define EXTI15_IRQ		40



//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define READ_BIT(NUM,POS)	(((NUM)>>POS)&1)
#define SET_BIT(NUM,POS)	((NUM) |= 1<<POS)
#define RESET_BIT(NUM,POS)	((NUM) &= ~(1<<POS))
#define TOGGLE_BIT(NUM,POS)	((NUM) ^= 1<<POS)






#endif /* INC_STM32F103X6_H_ */