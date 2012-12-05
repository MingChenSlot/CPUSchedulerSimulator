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
	if(!(tmp = (QNODE *)malloc(sizeof(QNODE)))){
		fprintf(stderr, "Malloc Qnode Failed!\n");
		exit(1);
	}
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

int len(QUEUE *q)
{
	return q->size;
}

void free_q(QUEUE *q)
{
	while(q->head != NULL)
		dequeue(q);
}

TASK *peek(QUEUE *q)
{
	if(!len(q))
		return NULL;
	else
		return q->head->tk;
}


