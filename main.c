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

	QUEUE q;
	init_q(&q);
	printf("Queue Initiated\n");
	enqueue(&q, t + 1);
	enqueue(&q, t + 5);
	printf("Enqueue Finished\n");
	printf("Length is %d\n", length_q(&q));
	printf("arrive t is %d\n", dequeue(&q)->t_arrive);
	printf("Dequeue Finished\n");
	printf("Length is %d\n", length_q(&q));
	free_q(&q);
	printf("Free Finished\n");
	printf("Length is %d\n", length_q(&q));

	return 1;
}
