/*
 *   exp_queue.h
 *   
 *   Created on: Nov 11, 2012
 */
#include "queue.h"

#ifndef EXP_QUEUE_H_
#define EXP_QUEUE_H_

#define SLICE 10
#define PRIORITY_LEVEL 8


typedef struct ready_queue
{
	QUEUE* task_q[PRIORITY_LEVEL];
}READY_QUEUE;


/* Exponential Queue Operations */
void init_rq(void *rq);
int init_p(TASK *task);
void push_rq(void *rq, TASK *task);
struct task *pop_rq(void *rq);
void free_rq(void *rq);
int get_tslice(int priority);

#endif /* EXP_QUEUE_H_*/
