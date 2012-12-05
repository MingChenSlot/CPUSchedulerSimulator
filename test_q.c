/*
 * main.c
 *
 *  Created on: Nov 14, 2012
 *      Author: ming
 */

#include "exp_queue.h"
#include "queue.h"

int main()
{
	TASK t[10];
	int i;
	for(i=0; i<10; i++)
	{
		t[i].c_io = t[i].t_arrive = t[i].t_cpu = t[i].t_io = i;
		t[i].t_slice = t[i].t_exec =  0;
		t[i].priority = 7;
	}
	EXP_QUEUE q;
	init_eq(&q);
	printf("EQueue Initiated\n");
//	enqueue(&q, t + 1);
//	enqueue(&q, t + 5);
	push_eq(&q, t + 1);
	push_eq(&q, t + 5);
	printf("Enqueue Finished\n");
	TASK* tmp;
	tmp = peek(q.task_q[7]);
	tmp->t_cpu = 0;
	/* use up time slice */
	tmp = pop_eq(&q);
 	tmp->t_exec = 1;
	tmp->t_slice = 0;
	printf("cpu time is %d\n", tmp->t_cpu);
	push_eq(&q, tmp);
//	printf("Length is %d\n", length_q(&q));
//	printf("arrive t is %d\n", dequeue(&q)->t_arrive);
//	printf("arrive t is %d\n", pop_eq(&q)->t_arrive);
//	printf("Dequeue Finished\n");
	printf("arrive t is %d\n", pop_eq(&q)->t_arrive);
	tmp = pop_eq(&q);
	printf("arrive t is %d\n", tmp->t_arrive);
	printf("time slice is %d\n", tmp->t_slice);
	printf("priority is %d\n", tmp->priority);
	/* use less than half of time slice */
	tmp->t_slice = 15;
	push_eq(&q, tmp);
	push_eq(&q, t + 3);
	push_eq(&q, t + 4);
	tmp = pop_eq(&q);
	printf("arrive t is %d\n", tmp->t_arrive);
	printf("time slice is %d\n", tmp->t_slice);
	printf("priority is %d\n", tmp->priority);
	free_eq(&q);
	printf("Free Finished\n");
//	printf("Length is %d\n", length_q(&q));

	return 1;
}
