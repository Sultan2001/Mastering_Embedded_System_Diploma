/**
 ******************************************************************************
 * @file           : main.c
 * @author         : mohamed sultan
 * @brief          : Main program body
 ******************************************************************************
 */

#include "stm32_F103C6_GPIO_Driver.h"
#include "stm32_F103C6_EXTI_Driver.h"
#include "stm32f103x6.h"
#include "core_cm3.h"
#include "Scheduler.h"
#include "string.h"









Task_ref Task1;
Task_ref Task2 ;
Task_ref Task3;
uint_8 task1_bit=0;
uint_8 task2_bit=0;
uint_8 task3_bit=0;
void Read_Control_Reg(uint_32* value );
void Read_IPSR_Reg(uint_32* value );

uint_32 os_svc_set(uint_32 a,uint_32 b,uint_32 SVC_ID   );
void OS_SVC(uint_32 * Stack_frame);
uint_8 svc_value ;

void task1()
{
	while(1)
	{
		task1_bit ^=1;

	}
}
void task2()
{
	while(1)
	{
		task2_bit ^=1;

	}
}
void task3()
{
	while(1)
	{
		task3_bit ^=1;

	}
}


int main(void)
{
//HW init , Clock tree , Reset Controller
	HW_init();
	 MyRTOS_init();

		Task1.stack_size=1024;
		Task1.P_taskEntry =task1;
		Task1.priorty =2;
		strcpy(Task1.TaskName , "task1");
	Task2.stack_size=1024;
	Task2.P_taskEntry =task2;
	Task2.priorty =2;
	strcpy(Task2.TaskName , "task2");

	Task3.stack_size=1024;
	Task3.P_taskEntry =task3;
	Task3.priorty =2;
	strcpy(Task3.TaskName , "task3");
	MyRTOS_CreateTask(&Task1);
	MyRTOS_CreateTask(&Task2);
	MyRTOS_CreateTask(&Task3);
	MyRTOS_ActivateTask(&Task1);
	MyRTOS_ActivateTask(&Task2);
	MyRTOS_ActivateTask(&Task3);
	MyRTOS_Start_OS();
	while(1)
	{

	}
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

