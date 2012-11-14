/*
 * main.c
 *
 *  Created on: Nov 14, 2012
 *      Author: ming
 */

#include <stdlib.h>
#include "tasks.h"

void main()
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
	enqueue(&q, t + 1);
	enqueue(&q, t + 5);
	printf("Length is %d", length_q(&q));
	printf("arrive t is %d", dequeue(&q)->t_arrive);
	printf("Length is %d", length_q(&q));
	free_q(&q);
	printf("Length is %d", length_q(&q));

	return;
}
