/*
 * Scheduler.h
 *
 *  Created on: Sep 11, 2024
 *        Author: mohamed sultan
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "CortexMX_OS_Porting.h"
#include "Platform_Types.h"
//#include "My_RTOS_FIFO.h"


typedef enum{
 NOERROR,
 Ready_Queue_init_Error,
 Task_exceeded_Stack_size,


}MyRTOS_ERROR_ID;

typedef enum
{
	SVC_ActivateTask,
	SVC_TerminateTask,
	SVC_TaskWaitingTime
}SVC_ID;
typedef struct
{
	uint_32 stack_size;
	uint_8 priorty;
	void (*P_taskEntry)(void);
	uint_8 AutoStart;
	uint_32 _S_PSP_Task;     // NOT Entered by  the user
	uint_32 _E_PSP_Task;    // NOT Entered by  the user
	uint_32 * Current_PSP; // NOT Entered by  the user
	uint_8 TaskName[20];
	enum{
		Suspend,
		Running,
		Waiting,
		Ready
	}Task_State; // NOT Entered by  the use


	struct{
		enum{
			Enable,
			Disable
		}Blocking;
		uint_32 Ticks_count;
	}TimingWaiting;



}Task_ref;

//APIs
MyRTOS_ERROR_ID MyRTOS_init();
MyRTOS_ERROR_ID MyRTOS_CreateTask (Task_ref * Tref);
void MyRTOS_ActivateTask(Task_ref * Tref);
void MyRTOS_TerminateTask(Task_ref * Tref);
void MyRTOS_Start_OS();
void MyRTOS_TaskWating(uint_32 ticks,Task_ref * Tref);

#endif /* INC_SCHEDULER_H_ */
