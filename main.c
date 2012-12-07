#include "sched.h"
#include "input.h"
#include "disk.h"

inline int min(int t1, int t2, int t3)
{	
	int min = t1;
	if(t2 < min)
		min = t2;
	if(t3 < min)
		min = t3;
	return min;
}

int main(int argc, char *argv[])
{
	int time = 10; /* cpu time */
	int t = 0; /* time interval */
	
	READY_QUEUE rq;
	QUEUE wq, oq;
	
	init_q(&wq);
	init_q(&oq);
	init_rq(&rq);

	struct run_task rt;
	rt.status = IDLE;
	rt.set = FALSE;
	rt.rproc = NULL;

	TASK *arr_prog;
	arr_prog = read_prog();

	int t1, t2, t3;
	while(TRUE){
	
		t1 = nex_arr_prog(arr_prog, time);
		t2 = nex_tslice(&rt);
		t3 = next_io(&wq);
		
		assert(t1 >= 0);
		assert(t2 >= 0);
		assert(t3 >= 0);
		t = min(t1, t2, t3);
		
		time += t;
		if(rt.status == RUNNING)
			update_run_task(&rt, t);
		update_io_time(&wq, t);

		/* after 1ms switch out, put the running process into correct queue */
		if(!rt.set && rt.status == SWITCH_OUT)
			settle_proc(&rt, &rq, &oq, time);

		if(rt.status == IDLE || rt.status == SWITCH_OUT){
			// put process on CPU cost 1 ms
			if(sched_compl_io(&wq))
				handle_compl_io(&rq, &wq, &oq, time);
			while(sched_new_prog(arr_prog, time)){
				push_rq(&rq, arr_prog);
				arr_prog = read_prog();
			}
			
			time += MIN_T;
			update_io_time(&wq, MIN_T);
		
			if(!put_proc_on_cpu(&rt, &rq)){
				rt.status = IDLE;
				if(!peek(&wq) && !arr_prog)
					break;
			}
		}
	
		if(sched_take_out_proc(&rt, &wq, arr_prog, time))
			take_out_proc(&rt);
	
		if(sched_compl_io(&wq))
			handle_compl_io(&rq, &wq, &oq, time);
		
		if(sched_nex_io(&rt))
			new_io(&wq, &rt);
		
		while(sched_new_prog(arr_prog, time)){
			push_rq(&rq, arr_prog);
			arr_prog = read_prog();
		}

	}

	printf("Current Time: %d\n", time);
	TASK *last;
	int num = 0;
	long tot_compl_time = 0;
	int min_compl_time = INF;
	int max_compl_time = 0;
	int tot_cpu_time = 0;
	int tmp_time = 0;
	while(len(&oq)){
		last = dequeue(&oq);
		num++;
		tmp_time = last->t_finish - last->t_arrive;	
		assert(tmp_time > 0);
		tot_compl_time += tmp_time;
		if(tmp_time < min_compl_time)
			min_compl_time = tmp_time;
		if(tmp_time > max_compl_time)
			max_compl_time = tmp_time;
		tot_cpu_time += last->t_exec;
//		printf("Prog Name: %s\n", last->cmd);
//		printf("Finish Time: %d\n", last->t_finish);
	}
	printf("ACT = %f\n", ((double)tot_compl_time) / num);
	printf("Min = %d\n", min_compl_time);
	printf("Max = %d\n", max_compl_time);
	printf("Throughput = %f\n", num / ((double)(time / 1000)));
	printf("Utilization = %f\n",((double)tot_cpu_time) / time); 

	return 1;
}
