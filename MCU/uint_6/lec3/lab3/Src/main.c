/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Ahmed khaled khalaf
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
#include "stdint.h"
#define RCC_BASE		0x40021000
//Set and cleared by software to enable PLL.
//Cleared by hardware when entering Stop or Standby mode. This bit can not be reset if the
//PLL clock is used as system clock or is selected to become the system clock. Software
//must disable the USB OTG FS clock before clearing this bit.
//0: PLL OFF
//1: PLL ON
#define RCC_CR			*(volatile uint32_t*)(RCC_BASE + 0x00)
		/*
		 * Microcontroller clock output
		Set and cleared by software.
		00xx: No clock
		0100: System clock (SYSCLK) selected
		0101: HSI clock selected
		0110: HSE clock selected
		0111: PLL clock divided by 2 selected
		1000: PLL2 clock selected
		1001: PLL3 clock divided by 2 selected
		1010: XT1 external 3-25 MHz oscillator clock selected (for Ethernet)
		1011: PLL3 clock selected (for Ethernet)
		 */

#define	RCC_CFGR		*(volatile uint32_t*)(RCC_BASE + 0x04)

void CLK_init (void)
{
	/*
		Bit 24 PLLON: PLL enable
		Set and cleared by software to enable PLL.
		Cleared by hardware when entering Stop or Standby mode. This bit can not be reset if the
		PLL clock is used as system clock or is selected to become the system clock. Software
		must disable the USB OTG FS clock before clearing this bit.
		0: PLL OFF
		1: PLL ON
	 */
	RCC_CR |= (1<<24);


	/*
		Bits 3:2 SWS[1:0]: System clock switch status
		Set and cleared by hardware to indicate which clock source is used as system clock.
		00: HSI oscillator used as system clock
		01: HSE oscillator used as system clock
		10: PLL used as system clock
		11: Not applicable
	 */
	RCC_CFGR |= (0b10<<2);

	/*
		Bits 1:0 SW[1:0]: System clock Switch
		Set and cleared by software to select SYSCLK source.
		Set by hardware to force HSI selection when leaving Stop and Standby mode or in case of failure of
		the HSE oscillator used directly or indirectly as system clock (if the Clock Security System is
		enabled).
		00: HSI selected as system clock
		01: HSE selected as system clock
		10: PLL selected as system clock
		11: Not allowed*/

	RCC_CFGR |= (0b10<<0);
	/*
		Bits 21:18 PLLMUL[3:0]: PLL multiplication factor
		These bits are written by software to define the PLL multiplication factor. They can be written only
		when PLL is disabled.
		000x: Reserved
		0010: PLL input clock x 4
		0011: PLL input clock x 5
		0100: PLL input clock x 6
		0101: PLL input clock x 7
		0110: PLL input clock x 8
		0111: PLL input clock x 9
		10xx: Reserved
		1100: Reserved
		1101: PLL input clock x 6.5
		111x: Reserved */
	RCC_CFGR |= (0b0110<<18);

	/*
		Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
		Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
		0xx: HCLK not divided
		100: HCLK divided by 2
		101: HCLK divided by 4
		110: HCLK divided by 8
		111: HCLK divided by 16
		Caution: Software must configure these bits ensure that the frequency in this domain does not
		exceed 36 MHz.
	 */

	RCC_CFGR |= (0b100<<8);


	/*
	 	Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
		Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
		0xx: HCLK not divided
		100: HCLK divided by 2
		101: HCLK divided by 4
		110: HCLK divided by 8
		111: HCLK divided by 1
		*/
	RCC_CFGR |= (0b100<<11);
}

int main(void)
{
	CLK_init();
	while(1)
	{

	}
}
