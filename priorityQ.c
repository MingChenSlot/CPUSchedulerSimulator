/*
 * priorityQ.c
 *
 *  Created on: Nov 29, 2012
 *      Author: gjing
 */

#include "priorityQ.h"

/*  this file has functions to test a red-black tree of integers */
void IntDest(void* a) {
  free((int*)a);
}

int IntComp(const void* a,const void* b) {
  if( *(int*)a > *(int*)b) return(1);
  if( *(int*)a < *(int*)b) return(-1);
  return(0);
}

void IntPrint(const void* a) {
  printf("%i",*(int*)a);
}

void InfoPrint(void* a) {
	;
}

void InfoDest(void *a){
	;
}

void init_rq(void *rq){
	PRIORITYQUEUE* pq = (PRIORITYQUEUE*) rq;
	pq->size = 0;
	pq->tree = RBTreeCreate(IntComp,IntDest,InfoDest,IntPrint,InfoPrint);
}

void update_run_task(struct run_task *rt, int t){
	rt->rproc->t_exec += t;
	rt->rproc->t_cpu -= t;
	rt->rproc->t_slice -= t;
	rt->rproc->priority = -1 * (rt->rproc->t_cpu);
	if(rt->rproc->c_io)	
		rt->rproc->t_nex_io -= t;
	return;
}

int init_p(TASK *task)
{
	int p = (-1*(task->t_cpu));
	return p;
}

void push_rq(void *rq, TASK *task){
	PRIORITYQUEUE* pq = (PRIORITYQUEUE*) rq;
	int* t = (int*) malloc(sizeof(int));
	*t = -1*(task->t_cpu);
	task->t_slice = task->t_cpu;
	task->priority = *t;
	RBTreeInsert(pq->tree,t,task);
	pq->size++;
}

struct task *pop_rq(void *rq){
	PRIORITYQUEUE* pq = (PRIORITYQUEUE*) rq;
	rb_red_blk_node* node;
	node = FindLargest(pq->tree, pq->tree->root->left);
	TASK* rt = (TASK*) node->info;
	if(rt != NULL){
		RBDelete(pq->tree, node);
		pq->size--;
	}
	return rt;
}

void free_rq(void *rq){
	PRIORITYQUEUE* temp = (PRIORITYQUEUE*) rq;
	RBTreeDestroy(temp->tree);
}
