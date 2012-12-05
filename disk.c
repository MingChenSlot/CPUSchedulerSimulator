#include "disk.h"

void handle_compl_io(void *rq, QUEUE *wq, QUEUE *oq, int time)
{
	TASK *tmp;
	tmp = dequeue(wq);
	
//	printf("io count remain for %s is %d\n", tmp->cmd, tmp->c_io);
	tmp->c_io--;
	assert(tmp->c_io >= 0);
	if(tmp->t_cpu != 0){
		push_rq(rq, tmp);
	}
	else{
		if(tmp->c_io > 0){
			tmp->t_io = IO_TIME;
			enqueue(wq, tmp);
		}
		else{
			assert(tmp->t_arrive < time);
			tmp->t_finish = time;
			enqueue(oq, tmp);
		}
	}
}

void update_io_time(QUEUE *wq, int t)
{
	if(peek(wq))
		peek(wq)->t_io -= t;
	return;
}

void new_io(QUEUE *wq, struct run_task *rt)
{
	rt->rproc->t_io = IO_TIME;
	rt->rproc->t_nex_io = rt->rproc->t_io_slice;

	if(peek(wq) == NULL)
		rt->rproc->t_io += 1; /* Take out needs one ms */

	enqueue(wq, rt->rproc);
	rt->set = TRUE;
//	printf("New IO is finished.\n");
}

int next_io(QUEUE *wq)
{
	if(peek(wq) == NULL)
		return INF;
	else
		return peek(wq)->t_io;
}
 


