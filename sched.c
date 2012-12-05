#include "sched.h"

/* Time Operations */
int nex_tslice(struct run_task *rt)
{
	int min;
	if(rt->status == SWITCH_OUT || rt->status == SWITCH_IN){
		min = MIN_T;
	}else if(rt->status == RUNNING){
		/* use up time slice */
		min = rt->rproc->t_slice;
		/* process terminates */
		if(rt->rproc->t_cpu < min)
			min = rt->rproc->t_cpu;
		/* IO blocks */
		if(rt->rproc->c_io && rt->rproc->t_nex_io < min)
			min = rt->rproc->t_nex_io;
	}else
		min = INF;
	return min;
}



/* Process Operations */
int put_proc_on_cpu(struct run_task *rt, void *rq)
{
	TASK *tmp = pop_rq(rq);
	if(tmp == NULL)
		return FALSE;
	else{
		rt->rproc = tmp;
		rt->status = RUNNING;
		rt->set = FALSE;
	}
	return TRUE;
}

void take_out_proc(struct run_task *rt)
{
	rt->status = SWITCH_OUT;
}

void settle_proc(struct run_task *rt, void *rq, QUEUE *oq, int time)
{
	if(rt->rproc->t_cpu == 0){
		assert(rt->rproc->t_arrive < time);
		rt->rproc->t_finish = time;	
		enqueue(oq, rt->rproc);
	}
	else
		push_rq(rq, rt->rproc);
	rt->set = TRUE;
}	

/* Schedule Query */
int sched_take_out_proc(struct run_task *rt, QUEUE *wq, TASK *arr_prog, int time)
{
	if(rt->status == RUNNING){	
		
		if(!rt->rproc->t_slice){
	//		printf("Use up time slice.\n");
			return TRUE;
		}
		if(!rt->rproc->t_cpu){
	//		printf("Terminates.\n");
			return TRUE;
		}
		
		if(!rt->rproc->t_nex_io && rt->rproc->c_io){
	//		printf("New IO Interrupt.\n");
			return TRUE;
		}

		TASK *p_wq = peek(wq);
		if(p_wq){
			if(!p_wq->t_io && p_wq->t_cpu && (peek(wq)->priority > rt->rproc->priority)){
	//			printf("IO Completion Interrupt.\n");
				return TRUE;
			}
		}

		if(arr_prog){
			if((arr_prog->t_arrive <= time) && arr_prog->priority > rt->rproc->priority){
	//			printf("New Program Interrupt.\n");
				return TRUE;
			}
		}
	}

	return FALSE;
}

int sched_compl_io(QUEUE *wq)
{	
	if(peek(wq) == NULL)
		return FALSE;
	else
		return (peek(wq)->t_io == 0);
}

int sched_nex_io(struct run_task *rt)
{
	if(rt->status == SWITCH_OUT && rt->rproc->c_io && rt->rproc->t_cpu > 0)
		return (rt->rproc->t_nex_io == 0);
	return FALSE;
} 

int sched_new_prog(TASK *nex_proc, int time)
{
	if(nex_proc == NULL)
		return FALSE;
	else
		return (nex_proc->t_arrive <= time);
}
