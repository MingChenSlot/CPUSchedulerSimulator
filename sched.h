#include "queue.h"
#include "exp_queue.h"
#include "priorityQ.h"

#ifndef SCHED_H_
#define SCHED_H_

/* Schedule Functions */
int sched_take_out_proc(struct run_task *, QUEUE *, TASK *, int);
int sched_compl_io(QUEUE *wq);
int sched_nex_io(struct run_task*);
int sched_new_prog(TASK *nex_proc, int time);
int put_proc_on_cpu(struct run_task *rt, void *rq);
void take_out_proc(struct run_task*);
void settle_proc(struct run_task *rt, void *, QUEUE *, int);

/* time slice */
int nex_tslice(struct run_task *rt);

#endif /* SCHED_H_ */
