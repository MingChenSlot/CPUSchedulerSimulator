#include "input.h"

int getceil(int io, int size)
{
	if(io > 0){
		int i = 1;
		while((io -= size) > 0) 
			i++;
		return i;
	}else
		return 0;
}

TASK *read_prog()
{
	TASK *tmp;
	if(!(tmp = (TASK *)malloc(sizeof(TASK)))){
		fprintf(stderr, "Malloc New Arrival Program Failed.\n");
		exit(1);
	}
	float cpu_in_seconds;
	int ret = scanf("%s%d%f%d", tmp->cmd, &(tmp->t_arrive), &cpu_in_seconds, &(tmp->c_io));
	if(ret == 4){
		tmp->t_cpu = (int)(cpu_in_seconds * 1000);
		tmp->t_exec = tmp->t_io = tmp->t_slice = tmp->t_finish = 0;
		tmp->c_io = getceil(tmp->c_io, BLOCK_SIZE);
		
		if(tmp->c_io){
			tmp->t_io_slice = tmp->t_cpu / tmp->c_io;
			if(tmp->t_io_slice < MIN_T)
				tmp->t_io_slice = MIN_T;
			tmp->t_nex_io = tmp->t_io_slice;
		}else{
			tmp->t_io_slice = 0;
			tmp->t_nex_io = INF;
		}

		tmp->priority = init_p(tmp);
		return tmp;
	}else if(ret == EOF){
		return NULL;
	}else{
		printf("Number of Parameters Not Matched.\n");
		return NULL;
	}
}

int nex_arr_prog(TASK *arr_prog, int time)
{
	if(arr_prog == NULL)
		return INF;
	else
		return (arr_prog->t_arrive - time);
}

