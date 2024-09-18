/*
 * My_RTOS_FIFO.h
 *
 *  Created on: Sep 11, 2024
 *       Author: mohamed sultan
 */

#ifndef INC_MY_RTOS_FIFO_H_
#define INC_MY_RTOS_FIFO_H_





/*
 * ------------
 * | Includes |
 * ------------
 */
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "Scheduler.h"

//select element type of FIFO
#define FIFO_element_type 	Task_ref*

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//FIFO Definition:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct
{
	FIFO_element_type *base;
	FIFO_element_type *tail;
	FIFO_element_type *head;
	uint32_t length;
	uint32_t count;
}FIFO_Buf_t;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//FIFO States:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef enum
{
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_null
}FIFO_Buf_Status;

/*
 * ======================================================================
 * 			APIs Supported by "MY RTOS FIFO"
 * ======================================================================
 */
FIFO_Buf_Status FIFO_init (FIFO_Buf_t *P_fifo, FIFO_element_type *buf, uint32_t length);
FIFO_Buf_Status FIFO_IS_FULL(FIFO_Buf_t *P_fifo);
FIFO_Buf_Status FIFO_IS_EMPTY(FIFO_Buf_t *P_fifo);
FIFO_Buf_Status FIFO_Enqueue_Item(FIFO_Buf_t *P_fifo, FIFO_element_type item);
FIFO_Buf_Status FIFO_Dequeue_Item(FIFO_Buf_t *P_fifo, FIFO_element_type *item);
void FIFO_Print (FIFO_Buf_t *P_fifo);










#endif /* INC_MY_RTOS_FIFO_H_ */
