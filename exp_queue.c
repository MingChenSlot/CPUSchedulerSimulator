#include "exp_queue.h"

/* Exponential Queue Operations */
void init_rq(void *rq)
{
	READY_QUEUE *eq;
	eq = (READY_QUEUE *) rq;
	int i = 0;
	for(;i < PRIORITY_LEVEL; i++){
		if(!(eq->task_q[i] = (QUEUE *)malloc(sizeof(QUEUE)))){
			fprintf(stderr, "Malloc Queue Failed!\n");
			exit(1);
		}
		init_q(eq->task_q[i]);
	}
}

void update_run_task(struct run_task *rt, int t)
{
	rt->rproc->t_exec += t;
	rt->rproc->t_cpu -= t;
	rt->rproc->t_slice -= t;
	if(rt->rproc->c_io)
		rt->rproc->t_nex_io -= t;
	return;
}

int init_p(TASK *task){
	return (PRIORITY_LEVEL - 1);
}

void push_rq(void *rq, TASK *task)
{	
	READY_QUEUE *eq;
	eq = (READY_QUEUE *) rq;
	if(task->priority < 0 || task->priority >= PRIORITY_LEVEL){
		fprintf(stderr, "Invalid Priority!\n");
		exit(1);
	}

	if(task->t_slice == 0){
		/* Use full time slice */
		if(task->t_exec > 0 && task->priority) 
			task->priority--;
	}
	else{ /* Use less than half of its time slice */
		if(get_tslice(task->priority) < task->t_slice * 2){
			if(task->priority < (PRIORITY_LEVEL - 1))
				task->priority++;
		}
	}
	task->t_slice = get_tslice(task->priority);
	enqueue(eq->task_q[task->priority], task);
}		

TASK *pop_rq(void *rq)
{
	READY_QUEUE *eq;
	eq = (READY_QUEUE *) rq;
	int i = PRIORITY_LEVEL - 1;
	for(;i >= 0; i--)
	{
		if(len(eq->task_q[i]))
			return dequeue(eq->task_q[i]);
	}
	return NULL;
}

void free_rq(void *rq)
{
	READY_QUEUE *eq;
	eq = (READY_QUEUE *) rq;
	int i = 0;
	for(;i < PRIORITY_LEVEL; i++)
	{
		free_q(eq->task_q[i]);
		free(eq->task_q[i]);
	}
}

int get_tslice(int priority)
{
	int t_slice = SLICE;
	int i = PRIORITY_LEVEL - 1;
	for(; i > priority; i--)
		t_slice *= 2;
	return t_slice;
}

