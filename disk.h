#ifndef DISK_H_
#define DISK_H_

#include "queue.h"
#include "exp_queue.h"
#include "priorityQ.h"

/* IO operations */
void handle_compl_io(void *, QUEUE *, QUEUE *, int);
void update_io_time(QUEUE *, int);
void new_io(QUEUE *wq, struct run_task *rt);
int next_io(QUEUE *wq);

#endif
