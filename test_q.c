/*
 * main.c
 *
 *  Created on: Nov 14, 2012
 *      Author: ming
 */

#include "tasks.h"

int main()
{
	TASK t[10];
	int i;
	for(i=0; i<10; i++)
	{
		t[i].c_io = t[i].t_arrive = t[i].t_compl = t[i].t_cpu = t[i].t_io = i;
		t[i].t_slice = 0;
		t[i].priority = 1;
	}
	EXP_QUEUE q;
	init_eq(&q);
	printf("EQueue Initiated\n");
//	enqueue(&q, t + 1);
//	enqueue(&q, t + 5);
	push_eq(&q, t + 1);
	push_eq(&q, t + 5);
	t[4].priority = 4;
	t[8].priority = 7;
	push_eq(&q, t + 4);
	push_eq(&q, t + 8);
	printf("Enqueue Finished\n");
//	printf("Length is %d\n", length_q(&q));
//	printf("arrive t is %d\n", dequeue(&q)->t_arrive);
	printf("arrive t is %d\n", pop_eq(&q)->t_arrive);
	printf("Dequeue Finished\n");
	printf("arrive t is %d\n", pop_eq(&q)->t_arrive);
	TASK *tmp = pop_eq(&q);
	printf("arrive t is %d\n", tmp->t_arrive);
	printf("time slice is %d\n", tmp->t_slice);
	free_eq(&q);
	printf("Free Finished\n");
//	printf("Length is %d\n", length_q(&q));

	return 1;
}
