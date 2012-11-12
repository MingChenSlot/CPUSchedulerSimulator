/*
 *   tasks.h
 *   
 *   Created on: Nov 11, 2012
 */

#ifndef TASKS_H_
#define TASKS_H_

#define SLICE 10
#define PRIORITY_LEVEL 8

typedef struct 
{
	int t_compl; // overall completion time
	int t_arrive;
	int t_cpu;	// remaining CPU time needed
	int c_io;	// remaining I/O operations needed
	int priority;
	int t_io;	// remaining time for finishing current I/O operation
	int t_slice;// remaining execution time within one time slice
}TASK;

typedef queue_node
{
	struct queue_node *next;
	TASK *tk;
}QNODE;

typedef struct queue
{
	TASK *head;
	TASK *tail;
	int size;
}QUEUE;

typedef struct pri_queue
{
	QUEUE *task_q[PRIORITY_LEVEL);
}PRI_QUEUE;

/* Queue Operations */
void init_q(QUEUE *q);
void enqueue(QUEUE *q, TASK *task);
struct task *dequeue(QUEUE *q);
int length_q(QUEUE *q);
void free_q(QUEUE *q);

/* Priority Queue Operations */
void init_pri_q(PRI_QUEUE pq);
void push_pq(PRI_QUEUE *pq, TASK *task);
struct task *pop_pq(PRI_QUEUE *pq);
int length_pq(PRI_QUEUE *pq);
void free_pq(PRI_QUEUE *pq);

#endif /* TASKS_H_*/
