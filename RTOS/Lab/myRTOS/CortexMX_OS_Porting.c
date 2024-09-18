/*
 * CortexMX_OS_Porting.c
 *
 *  Created on: Sep 11, 2024
 *      Author: mohamed sultan
 */


#include "CortexMX_OS_Porting.h"





























void HW_init()
{
// init Clock tree (RCC -> systick timer & CPU ) MHZ
	//8 MHZ
	// 1 count -> 0.125 us
	// x count -> 1 ms
	// x = 8000 count


	__NVIC_SetPriority(PendSV_IRQn , 15);
}


__attribute((naked))  void SVC_Handler()
{
__asm("TST LR , #0x4 \n\t"
		"ITE EQ \n\t"
		"MRSEQ R0 , MSP \n\t"
		"MRSNE R0 , PSP \n\t"
		"b OS_SVC");
}

void HardFault_Handler ()
{
	while(1);
}
void MemManage_Handler()
{
	while(1);
}
void BusFault_Handler()
{
	while(1);
}
void UsageFault_Handler()
{
	while(1);
}

void Trigger_OS_PendSV(void)
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void OS_Start_Ticker()
{
	SysTick_Config(8000); // 1 ms
}

