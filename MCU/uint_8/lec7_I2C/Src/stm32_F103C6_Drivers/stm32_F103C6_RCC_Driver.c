/*
 * stm32_F103C6_RCC_Driver.c
 *
 *  Created on: Aug 10, 2024
 *      Author: mohamed sultan
 */

#include "stm32_F103C6_RCC_Driver.h"

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
static const uint_8 HCLC_table[] ={0,0,0,0,1,2,3,4};
static const uint_8 sys_CLCK_table[] ={0,0,0,0,0,0,0,0,2,3,4,5,6,7,8,9};
uint_32 MCAL_RCC_Getsys_CLCKFerq()
{
	uint_32 clk=0;

//	 Bits 3:2 SWS: System clock switch status
//	 Set and cleared by hardware to indicate which clock source is used as system clock.
//	 00: HSI oscillator used as system clock
//	 01: HSE oscillator used as system clock
//	 10: PLL used as system clock
//	 11: not applicable

	switch((RCC->CFGR >>2) & 0b11)
	{
	case 0 :
		clk = HSI;
		break;
	case 1:
		//need calculation
		clk = HSE;
		break;
	case 2:
		//need calculation
		clk = 16000000;
		break;

	}
	return clk;
}
uint_32 MCAL_RCC_GetHCLCKFerq()
{
	//Bits 7:4HPRE: AHB prescaler
return (MCAL_RCC_Getsys_CLCKFerq() >> sys_CLCK_table[((RCC->CFGR)>>4) & 0xf]);
}
uint_32 MCAL_RCC_GetPCLCK1Ferq()
{
	// Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	return( MCAL_RCC_GetHCLCKFerq() >> HCLC_table[((RCC->CFGR)>>8) & 0b111]) ;

}
uint_32 MCAL_RCC_GetPCLCK2Ferq()
{

	//  Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	return( MCAL_RCC_GetHCLCKFerq() >> HCLC_table[((RCC->CFGR)>>11) & 0b111]) ;
}

