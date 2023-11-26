//startup.c
// Eng mohamed sultan

#include "platform_Types.h"
extern void main();



extern uint_32 _stack_top;
extern uint_32 _E_text;
extern uint_32 _S_Data;
extern uint_32 _E_Data;
extern uint_32 _S_bss;
extern uint_32 _E_bss;



void reset_Handler();
void NMI_Handler()__attribute__((weak,alias("reset_Handler")));
void H_fault_Handler()__attribute__((weak,alias("reset_Handler")));
void MM_fault_Handler()__attribute__((weak,alias("reset_Handler")));
void Bus_fault_Handler()__attribute__((weak,alias("reset_Handler")));
void usage_fault_Handler()__attribute__((weak,alias("reset_Handler")));

uint_32 vectors[] __attribute__((section(".vectors"))) = {
(uint_32)&_stack_top,    /* stack top */
(uint_32)&reset_Handler,
(uint_32)&NMI_Handler,
(uint_32)&H_fault_Handler,
(uint_32)&MM_fault_Handler,
(uint_32)&Bus_fault_Handler,
(uint_32)&usage_fault_Handler,
};



void reset_Handler()
{

	// copy data section from flash to ram
	uint_32 _Data_size= (uint_8 *)&_E_Data - (uint_8 *)&_S_Data;
	uint_8 * P_src=(uint_8 *)&_E_text;
	uint_8 * P_dst=(uint_8 *)&_S_Data;
	for(int i=0; i<_Data_size ; i++)
	{
		*P_dst = *P_src;
		P_dst++;
		P_src++;
	}


	// init bss section
    uint_32 _bss_size= (uint_8 *)&_E_bss - (uint_8 *)&_S_bss;
	uint_8 * P_start_bss=(uint_8 *)&_S_bss;
	for(int i=0; i<_bss_size; i++)
	{
		*P_start_bss = (uint_8)0;
		P_start_bss++;
	}

// jump to main
	main();

}
