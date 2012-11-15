#include "tasks.h"

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
		q->tail->next = tmp;
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
		q->head = q->tail = NULL;
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
		dequeue(q);
}

/* Exponential Queue Operations */
void init_eq(EXP_QUEUE *eq)
{
	int i = 0;
	for(;i < PRIORITY_LEVEL; i++)
		init_q(eq->task_q[i]);
}

void push_eq(EXP_QUEUE *eq, TASK *task)
{
	if(task->t_slice == 0)
		task->t_slice = task->priority * SLICE;
	if(eq->task_q[task->priority - 1] == NULL)
		init_q(eq->task_q[task->priority - 1]);
	enqueue(eq->task_q[task->priority - 1], task);
}		

TASK *pop_eq(EXP_QUEUE *eq)
{
	int i = 0;
	for(;i < PRIORITY_LEVEL; i++)
	{
		if(length_q(eq->task_q[i]))
			return dequeue(eq->task_q[i]);
	}
	return NULL;
}

void free_eq(EXP_QUEUE *eq)
{
	int i = 0;
	for(;i < PRIORITY_LEVEL; i++)
	{
		free_q(eq->task_q[i]);
	}
}



