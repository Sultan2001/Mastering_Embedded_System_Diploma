/**
 ******************************************************************************
 * @file           : main.c
 * @author         : mohamed sultan
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

#include "stm32_F103C6_GPIO_Driver.h"
#include "stm32_F103C6_EXTI_Driver.h"
#include "stm32f103x6.h"
typedef enum
{
	privileged,
	nonprivileged


}CPU_Access_Level;

void Read_Control_Reg(uint_32* value );
void Read_IPSR_Reg(uint_32* value );
void switch_CPU_Access_Level(CPU_Access_Level Level);
uint_32 os_svc_set(uint_32 a,uint_32 b,uint_32 SVC_ID   );
void OS_SVC(uint_32 * Stack_frame);
uint_8 svc_value ;
uint_32 val1 =0;
uint_32 val2 =3;
uint_32 val3 =3 , val4,val5;
void RCC_init()
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

}
void GPIO_init()
{
	GPIO_PinConfig_t PinConfg;
	PinConfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinConfg.GPIO_PinNumber=GPIO_PIN_0;
	PinConfg.GPIO_OUTPUT_Speed=GPIO_SPEED_10MHz;
	MCAL_GPIO_Init(GPIOA, &PinConfg);

}
void EXTI_CallBack()
{

	MCAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);

}

void EXTI_init()
{
	EXTI_PinConfig_t EXTI_config;
	EXTI_config.EXTI_Pin = EXTI10PB10;
	EXTI_config.Trigger_Case = EXTI_Trigger_RISING;
	EXTI_config.IRQ_EN=EXTI_IRQ_Enable;
	EXTI_config.P_IRQ_CallBack=EXTI_CallBack;
	MCAL_EXTI_GPIO_Init(&EXTI_config);

}

int main(void)
{
	RCC_init();
	GPIO_init();
	EXTI_init();
	 val1 = os_svc_set(3,2,1);
	 val2 = os_svc_set(3,2,2);
	 val3 = os_svc_set(3,2,3);
	while(1)
	{

	}
}
uint_32 os_svc_set(uint_32 a,uint_32 b,uint_32 SVC_ID)
{
	uint_32 ret_val;
	switch(SVC_ID)
	{
	case 1:
		__asm("SVC #0x1");
		break;

	case 2:
		__asm("SVC #0x2");
		break;
	case 3 :
		__asm("SVC #0x3");
		break;
	}

	__asm("mov %0 , R0 "
			:"=r" (ret_val));
	return ret_val;
}

__attribute((naked))  void SVC_Handler()
{
__asm("TST LR , #0x4 \n\t"
		"ITE EQ \n\t"
		"MRSEQ R0 , MSP \n\t"
		"MRSNE R0 , PSP \n\t"
		"b OS_SVC");
}

void OS_SVC(uint_32 * Stack_frame)
{
	uint_32 result=0 , arg1,arg2;
	 svc_value = (uint_8)*((uint_8 *)(Stack_frame[6])-2);
	 arg1=Stack_frame[0];
	 arg2=Stack_frame[1];

	 switch(svc_value)
	 {
	 case 1:
		 //sum
		 result = arg1 + arg2;
	 		break;

	 	case 2:
	 		 result = arg1 -  arg2;
	 		 break;
	 	case 3 :
	 		 result = arg1 * arg2;

	 		break;


	 }
	 Stack_frame[0] = result; // address R0 in stack
}

void Read_Control_Reg(uint_32* value )
{
	__asm("NOP  \n\t NOP \n\t NOP");

	__asm("MRS  %[out] , CONTROL"
			:[out] "=r" (*value) );

	__asm("NOP  \n\t NOP \n\t NOP");
}


void Read_IPSR_Reg(uint_32* value )
{
	__asm("NOP  \n\t NOP \n\t NOP");

	__asm("MRS  %[out] , IPSR"
			:[out] "=r" (*value) );

	__asm("NOP  \n\t NOP \n\t NOP");
}

void switch_CPU_Access_Level(CPU_Access_Level Level)
{
// control REG
//	[0] nPRIV Defines the Thread mode privilege level:
//	0 = Privileged
//	1 = Unprivileged.
	switch(Level)
	{
	case privileged:
		__asm("MRS r0 , CONTROL \n\t"
				"LSR r0 , r0 ,#0x1 \n\t"
				"LSL r0 , r0 ,#0x1 \n\t"
				"MSR CONTROL , r0");
		break;

	case nonprivileged:
		__asm("MRS r0 , CONTROL \n\t"
				"ORR r0 , r0 ,#0x1 \n\t"
				"MSR CONTROL , r0");
		break;

	}

}

