/*
 * priorityQ.h
 *
 *  Created on: Nov 29, 2012
 *      Author: gjing
 */

#ifndef PRIORITYQ_H_
#define PRIORITYQ_H_

#include "red_black_tree.h"
#include "queue.h"

typedef struct PRIORITYQUEUE {
	rb_red_blk_tree* tree;
	int size;
} PRIORITYQUEUE;

/*functions for creating priority queue*/
void IntDest(void* a);
int IntComp(const void* a,const void* b);
void IntPrint(const void* a);
void InfoPrint(void* a);
void InfoDest(void *a);

/* operations */
void init_rq(void *rq);
void update_run_task(struct run_task *, int);
int init_p(TASK *task);
void push_rq(void *rq, TASK *task);
struct task *pop_rq(void *rq);
void free_rq(void *rq);

#endif /* PRIORITYQ_H_ */
