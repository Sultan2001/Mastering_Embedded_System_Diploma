/*
 * CortexMX_OS_Porting.h
 *
 *  Created on: Sep 11, 2024
 *       Author: mohamed sultan
 */

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_

//#include "ARMCM3.h"
#include "core_cm3.h"
#include "Platform_Types.h"

extern  uint_32 _estack;
extern  uint_32 _eheap;

#define MAIN_STACK_SIZE		3072			// 3 KB


#define OS_Set_PSP(address)				__asm volatile("MOV R0, %[IN] \n\t MSR PSP, R0" : : [IN] "r" (address))
#define OS_Get_PSP(address)				__asm volatile("MRS R0, PSP \n\t MOV %[OUT], R0" : [OUT] "=r" (address))

#define OS_SWITCH_SP_to_PSP				__asm volatile("MRS R0, CONTROL \n\t MOV R1, #0x02 \n\t \
														ORR R0, R0, R1 \n\t MSR CONTROL, R0")

#define OS_SWITCH_SP_to_MSP				__asm volatile("MRS R0, CONTROL \n\t MOV R1, #0x05 \n\t \
														AND R0, R0, R1 \n\t MSR CONTROL, R0")

#define OS_Switch_to_Unprivileged		__asm volatile("MRS R0, CONTROL \n\t MOV R1, #0x01 \n\t \
														ORR R0, R0, R1 \n\t MSR CONTROL, R0")

#define OS_Switch_to_Privileged			__asm volatile("MRS R0, CONTROL \n\t MOV R1, #0x06 \n\t \
														AND R0, R0, R1 \n\t MSR CONTROL, R0")





void HW_init();
void Trigger_OS_PendSV(void);
void OS_Start_Ticker();








#endif /* INC_CORTEXMX_OS_PORTING_H_ */
