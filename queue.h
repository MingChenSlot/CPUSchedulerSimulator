/*
 *   queue.h
 *   
 *   Created on: Nov 11, 2012
 */
#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include "error.h"
#define CMD_LENGTH 10
#define NUM_PARAMETERS 4
#define BLOCK_SIZE 8192
#define IO_TIME 10
#define MIN_T 1
#define INF 1000000
#define TRUE 1
#define FALSE 0

typedef struct task
{
	char cmd[CMD_LENGTH - 1];
	int t_finish; /* the time program is finished. */
	int t_exec; /* execution time */
	int t_arrive;
	int t_cpu;	/* remaining CPU time needed */
	int c_io;	/* remaining I/O operations needed */
	int t_nex_io; /* remaining time for next io operation */
	int priority; /* 0 - 7 */
	int t_io_slice;
	int t_io;	/* remaining time for finishing current I/O operation */
	int t_slice;/* remaining execution time within one time slice */
}TASK;

#define IDLE 0
#define RUNNING 1
#define SWITCH_OUT 2
#define SWITCH_IN 3

struct run_task
{
	TASK *rproc;
	int status; /* have four status: IDLE, RUNNING, SWITCH_OFF, SWITCH_IN */
	int set; /* denote whether the process is put back into correct queue */
};

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

/* Queue Operations */
void init_q(QUEUE *q);
void enqueue(QUEUE *q, TASK *task);
struct task *dequeue(QUEUE *q);
int len(QUEUE *q);
void free_q(QUEUE *q);
TASK *peek(QUEUE *q);

#endif /* QUEUE_H_*/
