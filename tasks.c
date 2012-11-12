#include <stdlib.h>
#include "queue.h"

/* Queue Operations */
void init_q(QUEUE *q)
{
	q->size = 0;
	q->head = NULL;
	q->tail = NULL;
}

void enqueue(QUEUE *q, TASK *task)
{
	QNODE *tmp;
	tmp = (QNODE *)malloc(sizeof(QNODE));
	tmp->tk = task;
	tmp->next = NULL;
	if(q->head == NULL)
		q->head = q->tail = tmp;
	else{
		q->tail-next = tmp;
		q->tail = tmp;
	}
	q->size++;
}

struct task *dequeue(QUEUE *q)
{
	if(q->head == NULL)
		return NULL;
	TASK *ret = q->head->tk;
	QNODE *tmp = q->head;
	if(q->head == q->tail)
		q->head = q-tail = NULL;
	else
		q->head = q->head->next;
	free(tmp);
	q->size--;
	return ret;
}

int length_q(QUEUE *q)
{
	return q->size;
}

void free_q(QUEUE *q)
{
	while(q->head != NULL)
		free(dequeue(q));
}

/* Priority Queue Operations */
void init_pri_q(PRI_QUEUE pq)
{
	int i = 0;
	for(;i < PRIORITY_LEVEL; i++)
		init_q(pq->task_q);
}

void push_pq(PRI_QUEUE *pq, TASK *task)
{
	if(task->t_slice == 0)
		task->t_slice = task->priority * SLICE;
	if(pq->task_q[task->priority - 1] == NULL)
		init_q(pq->task_q[task->priortiy - 1]);
	enqueue(pq->task_q[task->priority - 1], task);
}		

TASK *pop_pq(PRI_QUEUE *pq)
{
	int i = 0;
	for(;i < PRIORITY_LEVEL; i++)
	{
		if(length_q(pq->task_q[i]))
			return dequeue(pq->task_q[i]);
	}
	return NULL;
}

void free_pq(PRI_QUEUE *pq)
{
	int i = 0;
	for(;i < PRIORITY_LEVEL; i++)
	{
		free_q(pq->task_q[i]);
	}
}



