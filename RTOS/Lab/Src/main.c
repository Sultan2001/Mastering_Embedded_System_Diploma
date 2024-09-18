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
Task_ref Task4;
uint_8 task1_bit=0;
uint_8 task2_bit=0;
uint_8 task3_bit=0;
uint_8 task4_bit=0;
Mutex_ref mutex1;
uint_32 test_resource =10;

Mutex_ref mutex2;
uint_32 test_resource2 =20;


void Read_Control_Reg(uint_32* value );
void Read_IPSR_Reg(uint_32* value );

uint_32 os_svc_set(uint_32 a,uint_32 b,uint_32 SVC_ID   );
void OS_SVC(uint_32 * Stack_frame);
uint_8 svc_value ;

void task1()
{
	static uint_32 counter =0;
	while(1)
	{
		task1_bit ^=1;
		counter++;
if(counter == 100)
{
	MyRTOS_AcquireMutex(&mutex1, &Task1);
	MyRTOS_ActivateTask(&Task4);
	MyRTOS_AcquireMutex(&mutex2, &Task1);
}
if(counter ==200)
{

	counter=0;
	MyRTOS_ReleaseMutex(&mutex1);
}


	}
}
void task2()
{
static uint_32 counter =0;
	while(1)
	{
		task2_bit ^=1;
		counter++;
		if(counter == 100)
		{
			MyRTOS_ActivateTask(&Task3);
		}
		if(counter ==200)
		{
			counter=0;
			MyRTOS_TerminateTask(&Task2);
		}

	}
}
void task3()
{
	static uint_32 counter =0;

	while(1)
	{
		task3_bit ^=1;
		counter++;
		if(counter == 100)
				{
					MyRTOS_ActivateTask(&Task4);
				}
				if(counter ==200)
				{
					counter=0;
					MyRTOS_TerminateTask(&Task3);
				}
	}
}

void task4()
{
	static uint_32 counter =0;
	while(1)
	{
		task4_bit ^=1;
		counter++;

		if(counter == 10)
		{
			MyRTOS_AcquireMutex(&mutex2, &Task4);
			MyRTOS_AcquireMutex(&mutex1, &Task4);

		}
				if(counter ==200)
				{
					counter=0;
					MyRTOS_ReleaseMutex(&mutex1);
					MyRTOS_TerminateTask(&Task4);
				}
	}
}

int main(void)
{
	//HW init , Clock tree , Reset Controller
	HW_init();
	MyRTOS_init();

	mutex1.Payload = &test_resource;
	strcpy(mutex1.MutexName , "mutex1");

	mutex2.Payload = &test_resource2;
	strcpy(mutex2.MutexName , "mutex2");

	Task1.stack_size=512;
	Task1.P_taskEntry =task1;
	Task1.priorty =4;
	strcpy(Task1.TaskName , "task1");
	Task2.stack_size=512;
	Task2.P_taskEntry =task2;
	Task2.priorty =3;
	strcpy(Task2.TaskName , "task2");

	Task3.stack_size=512;
	Task3.P_taskEntry =task3;
	Task3.priorty =2;
	strcpy(Task3.TaskName , "task3");

	Task4.stack_size=512;
	Task4.P_taskEntry =task4;
	Task4.priorty =1;
	strcpy(Task4.TaskName , "task4");

	MyRTOS_CreateTask(&Task1);
	MyRTOS_CreateTask(&Task2);
	MyRTOS_CreateTask(&Task3);
	MyRTOS_CreateTask(&Task4);

	MyRTOS_ActivateTask(&Task1);
//	MyRTOS_ActivateTask(&Task2);
//	MyRTOS_ActivateTask(&Task3);
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

