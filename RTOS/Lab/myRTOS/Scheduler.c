/*
 * Scheduler.c
 *
 *  Created on: Sep 11, 2024
 *      Author: UAS  Author: mohamed sultan
 */


#include "Scheduler.h"
#include "My_RTOS_FIFO.h"
static void MY_RTOS_Create_Main_Stack();
static void MyRTOS_idelTask();
static void  MyRTOSCreateStack(Task_ref * Tref);
static void Update_FIFO();
static void Decide_whatNext();
uint_32 ticks=0;
struct{
	Task_ref * OSTasks[100];
	uint_32 _S_MSP_TASK;
	uint_32 _E_MSP_TASK;
	uint_32 PSP_Task_Locator;
	uint_32 NO_Of_Active_Tasks;
	Task_ref * CurrentTask;
	Task_ref * NextTask;

	enum {
		OSsuspend,
		OSRuning
	}OSmodeID;


}OS_Control;

FIFO_Buf_t Ready_Queue;
Task_ref * Ready_Queue_FIFO[100];

Task_ref MyRTOS_IdelTask;





MyRTOS_ERROR_ID MyRTOS_init()
{
	MyRTOS_ERROR_ID error=NOERROR;

	// update OS mode (OS suspend)
	OS_Control.OSmodeID = OSsuspend;
	//specify the main Stack for OS
	MY_RTOS_Create_Main_Stack();

	//Create OS Ready Queue
	if(FIFO_init(&Ready_Queue,Ready_Queue_FIFO,100) != FIFO_no_error)
	{
		error = Ready_Queue_init_Error;
	}

	// configure IDLE Task
	strcpy(MyRTOS_IdelTask.TaskName , "idleTask");
	MyRTOS_IdelTask.priorty = 255;
	MyRTOS_IdelTask.P_taskEntry= MyRTOS_idelTask;
	MyRTOS_IdelTask.stack_size=300;
	MyRTOS_CreateTask(&MyRTOS_IdelTask);


	return error;
}

static void os_svc_set(SVC_ID ID )
{

	switch(ID)
	{
	case SVC_ActivateTask:
		__asm("SVC #0x00");
		break;

	case SVC_TerminateTask:
		__asm("SVC #01");
		break;
	case SVC_TaskWaitingTime :
		__asm("SVC #0x02");
		break;
	}


}
static void Update_FIFO()
{
	Task_ref * Ptask;
	Task_ref * PNextTask;
	uint_32 i=0;
	while(i<OS_Control.NO_Of_Active_Tasks)
	{
		Ptask = OS_Control.OSTasks[i];
		PNextTask = OS_Control.OSTasks[i+1];

		if(Ptask->Task_State != Suspend)
		{

			/*
			 * 	//This if we reach to the end of the scheduler table
				if(OS_Control.NO_Of_Active_Tasks == (i+1))
				{
					FIFO_Enqueue_Item(&Ready_Queue, Ptask);
								Ptask->Task_State = Ready;
								break;
				}

				else if(PNextTask->Task_State == Suspend)
				{
					FIFO_Enqueue_Item(&Ready_Queue, Ptask);
					Ptask->Task_State = Ready;
					temp = Ptask;
				}

			 */

			//This if we reach to the end of the scheduler table
			if(OS_Control.NO_Of_Active_Tasks == (i+1))
			{
				FIFO_Enqueue_Item(&Ready_Queue, Ptask);
				Ptask->Task_State = Ready;
				break;
			}
			//This if the next task is low priority from the current then we push current to ready queue
			else if(Ptask->priorty < PNextTask ->priorty)
			{
				FIFO_Enqueue_Item(&Ready_Queue, Ptask);
				Ptask->Task_State = Ready;
				break;
			}
			else if(Ptask->priorty == PNextTask ->priorty)
			{
				FIFO_Enqueue_Item(&Ready_Queue, Ptask);
				Ptask->Task_State = Ready;
			}
			else if(Ptask->priorty >  PNextTask ->priorty)
			{
				//This can't happen because we sorted the scheduler table by bubble sort

			}
		}


		i++;
	}

}
static void Decide_whatNext()
{

	//This in case The Queue is empty and OS_Control.CurrentTask->Task_State != Suspend_State
	//This happen when we have only one task and this task is interrupting by svc
	//we need to continue in running it
	if(Ready_Queue.count == 0 && OS_Control.CurrentTask->Task_State != Suspend)
	{
		OS_Control.CurrentTask->Task_State = Running;

		//add Task to Ready Queue to run it till the task is terminate
		FIFO_Enqueue_Item(&Ready_Queue, OS_Control.CurrentTask);
		OS_Control.NextTask = OS_Control.CurrentTask;
	}
	else
	{
		//dequeue the top of ready queue because this is should running next
		FIFO_Dequeue_Item(&Ready_Queue, &OS_Control.NextTask);
		OS_Control.NextTask->Task_State = Running;

		//check if the next task priority is equal the current task priority to work with Round Robin Algorithm
		//check if the user doesn't terminate the current task so we will run it
		if((OS_Control.CurrentTask->priorty == OS_Control.NextTask->priorty) && (OS_Control.CurrentTask->Task_State != Suspend))
		{
			//enqueue the current task in the Ready Queue so that the other task will be on top and current will be after it
			//we do this because we run with Round Robin Algorithm
			FIFO_Enqueue_Item(&Ready_Queue, OS_Control.CurrentTask);
			OS_Control.CurrentTask->Task_State = Ready;
		}
	}
}

void BubbleSort()
{
	unsigned int i, j , n;
	Task_ref* temp ;
	uint_8 flag =0;
	n = OS_Control.NO_Of_Active_Tasks ;
	for (i = 0; i < n - 1; i++)
	{
		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++)
		{
			if (OS_Control.OSTasks[j]->priorty > OS_Control.OSTasks[j + 1]->priorty)
			{
				temp = OS_Control.OSTasks[j] ;
				OS_Control.OSTasks[j] = OS_Control.OSTasks[j + 1 ] ;
				OS_Control.OSTasks[j + 1] = temp ;
				flag=1;
			}
		}

		if (flag==0)  // if ==0 that means the Array is sorted
		{
			break;
		}

		flag =0;
	}
}
void MYRTOS_Update_Schadule_Tables()
{
	Task_ref * temp=NULL;


	//1- BubbleSort for tasks table
	BubbleSort();

	//2- free All  FIFO data
	while(FIFO_Dequeue_Item(&Ready_Queue, &temp) != FIFO_empty);

	//3- update FIFO (Ready queue)
	Update_FIFO();



}
void OS_SVC(uint_32 * Stack_frame)
{

	uint_8 svc_value = (uint_8)*((uint_8 *)(Stack_frame[6])-2);
	switch(svc_value)
	{
	case SVC_ActivateTask:
	case SVC_TerminateTask:
		//update Sch table
		MYRTOS_Update_Schadule_Tables();
		//if OS is Running
		if(OS_Control.OSmodeID == OSRuning)
		{
			if(strcmp(OS_Control.CurrentTask->TaskName, "idleTask") != 0)
			{
				// Decide what next
				Decide_whatNext();
				// trigger Os_PendSV (switch context )
				Trigger_OS_PendSV();
			}
		}


		break;
	case SVC_TaskWaitingTime :
		MYRTOS_Update_Schadule_Tables();
		break;
	}



}
static void MY_RTOS_Create_Main_Stack()
{
	OS_Control._S_MSP_TASK=(uint_32)&_estack;
	OS_Control._E_MSP_TASK=OS_Control._S_MSP_TASK - MAIN_STACK_SIZE;
	//Aligned 8 byte space between task psp and other
	OS_Control.PSP_Task_Locator = OS_Control._E_MSP_TASK -8 ;



}

static void MyRTOS_idelTask()
{
	while(1)
	{
		__asm("WFE");

	}
}
static void MyRTOSCreateStack(Task_ref * Tref)
{
	// Task Frame
	//=====  by processor=====
	/* (saved / restore ) Auto
	 * XPSR
	 * PC
	 * LR
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 *
	 * ==  manual ==
	 * r5 , r6 , r7 , r8 , r9 , r10 (saved / restore ) manual
	 */

	Tref->Current_PSP = (uint_32 *)Tref->_S_PSP_Task;

	Tref->Current_PSP--;
	*(Tref->Current_PSP)= 0x01000000; // XPSR

	Tref->Current_PSP--;
	*(Tref->Current_PSP)= (uint_32)Tref->P_taskEntry; // PC

	Tref->Current_PSP--;
	*(Tref->Current_PSP) = 0xFFFFFFFD; //DUMMY LR --> (EXECUTION RETURN CODE --> Thread Mode, PSP)


	//fill 13 General Purpose Register
	for(int i = 0; i < 13; i++)
	{
		Tref->Current_PSP--;
		*(Tref->Current_PSP) = 0;
	}

}
MyRTOS_ERROR_ID MyRTOS_CreateTask (Task_ref * Tref)
{
	MyRTOS_ERROR_ID error=NOERROR;
	//Create its own PSP stack
	// cheak Task stack size exceeded the psp stack or not
	Tref->_S_PSP_Task = OS_Control.PSP_Task_Locator;
	Tref->_E_PSP_Task = Tref->_S_PSP_Task - Tref->stack_size;

	if(Tref->_E_PSP_Task < (uint_32)&_eheap)
	{
		error = Task_exceeded_Stack_size;
	}
	else
	{
		//Aligned 8 byte space between task psp and other
		OS_Control.PSP_Task_Locator = Tref->_E_PSP_Task  -8 ;

		// init PSP Task stack
		MyRTOSCreateStack(Tref);
		// task state update --> suspend
		Tref->Task_State = Suspend;
		//Add Task to Scheduler Table
		OS_Control.OSTasks[OS_Control.NO_Of_Active_Tasks] = Tref;
		OS_Control.NO_Of_Active_Tasks++ ;


	}




	return error;
}


void MyRTOS_ActivateTask(Task_ref * Tref)
{
	Tref->Task_State = Waiting;
	os_svc_set(SVC_ActivateTask);

}
void MyRTOS_TerminateTask(Task_ref * Tref)
{
	Tref->Task_State = Suspend;
	os_svc_set(SVC_TerminateTask);
}
void MyRTOS_TaskWating(uint_32 ticks,Task_ref * Tref)
{
	Tref->Task_State = Suspend;
	Tref->TimingWaiting.Ticks_count=ticks;
	Tref->TimingWaiting.Blocking=Enable;
	os_svc_set(SVC_TerminateTask);
}

__attribute ((naked)) void PendSV_Handler(void)
{
	// Restore reg for current task

	/*
	 * 1. Get the Current_PSP from CPU registers
	 * |-------|
	 * |  xPSR |
	 * |  PC   |
	 * |  LR   |
	 * |  R12  |
	 * |  R3   |
	 * |  R2   |
	 * |  R1   |
	 * |  R0   |	<-- Current PSP
	 * |-------|
	 */
	OS_Get_PSP(OS_Control.CurrentTask->Current_PSP)	;

	/*
	 * 2. Save the registers from R4 to R11
	 * |-------|
	 * |  R4   |
	 * |  R5   |
	 * |  R6   |
	 * |  R7   |
	 * |  R8   |
	 * |  R9   |
	 * |  R10  |
	 * |  R11  |
	 * |-------|
	 */


	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %[OUT], R4" : [OUT] "=r" ((*OS_Control.CurrentTask->Current_PSP))); //R4

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %[OUT], R5" : [OUT] "=r" ((*OS_Control.CurrentTask->Current_PSP))); //R5

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %[OUT], R6" : [OUT] "=r" ((*OS_Control.CurrentTask->Current_PSP))); //R6

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %[OUT], R7" : [OUT] "=r" ((*OS_Control.CurrentTask->Current_PSP))); //R7

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %[OUT], R8" : [OUT] "=r" ((*OS_Control.CurrentTask->Current_PSP))); //R8

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %[OUT], R9" : [OUT] "=r" ((*OS_Control.CurrentTask->Current_PSP))); //R9

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %[OUT], R10" : [OUT] "=r" ((*OS_Control.CurrentTask->Current_PSP))); //R10

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile ("MOV %[OUT], R11" : [OUT] "=r" ((*OS_Control.CurrentTask->Current_PSP))); //R11


	//Restore The Context of the Next task
	if(OS_Control.NextTask != NULL)
	{
		OS_Control.CurrentTask = OS_Control.NextTask;
		OS_Control.NextTask = NULL;
	}

	/*
	 * 1. Write the values of registers from memory to CPU registers
	 * |-------|
	 * |  R4   |
	 * |  R5   |
	 * |  R6   |
	 * |  R7   |
	 * |  R8   |
	 * |  R9   |
	 * |  R10  |
	 * |  R11  |		<-- Current_PSP_Task
	 * |-------|
	 */
	__asm volatile ("MOV R11, %[IN]" : : [IN] "r" ((*OS_Control.CurrentTask->Current_PSP))); //R11
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile ("MOV R10, %[IN]" : : [IN] "r" ((*OS_Control.CurrentTask->Current_PSP))); //R10
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile ("MOV R9, %[IN]" : : [IN] "r" ((*OS_Control.CurrentTask->Current_PSP))); //R9
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile ("MOV R8, %[IN]" : : [IN] "r" ((*OS_Control.CurrentTask->Current_PSP))); //R8
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile ("MOV R7, %[IN]" : : [IN] "r" ((*OS_Control.CurrentTask->Current_PSP))); //R7
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile ("MOV R6, %[IN]" : : [IN] "r" ((*OS_Control.CurrentTask->Current_PSP))); //R6
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile ("MOV R5, %[IN]" : : [IN] "r" ((*OS_Control.CurrentTask->Current_PSP))); //R5
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile ("MOV R4, %[IN]" : : [IN] "r" ((*OS_Control.CurrentTask->Current_PSP))); //R4
	OS_Control.CurrentTask->Current_PSP++;

	/*
	 * 2.Set PSP with Current_PSP
	 */
	OS_Set_PSP(OS_Control.CurrentTask->Current_PSP);

	__asm("BX LR");

}



void MyRTOS_Start_OS()
{
	//Enter the OS in Running Mode instead of Suspend Mode
	OS_Control.OSmodeID= OSRuning;

	//Set Default Task --> IDLE Task
	OS_Control.CurrentTask = &MyRTOS_IdelTask;

	//Activate IDLE Task --> Run IDLE Task
	MyRTOS_ActivateTask(&MyRTOS_IdelTask);

	//Start Ticker --> 1ms
	OS_Start_Ticker();


	//Set PSP with PSP of Current Task
	OS_Set_PSP(OS_Control.CurrentTask->Current_PSP);

	//Set SP shadow to PSP instead of MSP
	OS_SWITCH_SP_to_PSP;

	//Switch from Privileged to Unprivileged
	OS_Switch_to_Unprivileged;

	//Run Current Task
	OS_Control.CurrentTask->P_taskEntry();
}
void MyRTOS_Update_TaskWaitingTime()
{
	for(int i =0 ; i< OS_Control.NO_Of_Active_Tasks ; i++)
	{
		if(OS_Control.OSTasks[i]->Task_State == Suspend)
		{
			if(OS_Control.OSTasks[i]->TimingWaiting.Blocking == Enable)
			{
				OS_Control.OSTasks[i]->TimingWaiting.Ticks_count--;
				if(OS_Control.OSTasks[i]->TimingWaiting.Ticks_count == 0)
				{
					OS_Control.OSTasks[i]->TimingWaiting.Blocking  = Disable;
					OS_Control.OSTasks[i]->Task_State = Waiting;
					os_svc_set(SVC_TaskWaitingTime);
				}
			}
		}
	}
}
void SysTick_Handler()

{
	MyRTOS_Update_TaskWaitingTime();
	Decide_whatNext();
	Trigger_OS_PendSV();
}
