/*
 *   tasks.h
 *   
 *   Created on: Nov 11, 2012
 */

#ifndef TASKS_H_
#define TASKS_H_

#define SLICE 10
#define PRIORITY_LEVEL 8

typedef struct task
{
	int t_compl; // overall completion time
	int t_arrive;
	int t_cpu;	// remaining CPU time needed
	int c_io;	// remaining I/O operations needed
	int priority;
	int t_io;	// remaining time for finishing current I/O operation
	int t_slice;// remaining execution time within one time slice
}TASK;

typedef struct queue_node
{
	struct queue_node *next;
	TASK *tk;
}QNODE;

typedef struct queue
{
	QNODE *head;
	QNODE *tail;
	int size;
}QUEUE;

typedef struct exp_queue
{
	QUEUE* task_q[PRIORITY_LEVEL];
}EXP_QUEUE;

/* Queue Operations */
void init_q(QUEUE *q);
void enqueue(QUEUE *q, TASK *task);
struct task *dequeue(QUEUE *q);
int length_q(QUEUE *q);
void free_q(QUEUE *q);

/* Exponential Queue Operations */
void init_eq(EXP_QUEUE *eq);
void push_eq(EXP_QUEUE *eq, TASK *task);
struct task *pop_eq(EXP_QUEUE *eq);
void free_eq(EXP_QUEUE *eq);

#endif /* TASKS_H_*/
