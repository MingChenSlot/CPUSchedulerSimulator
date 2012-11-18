#include "tasks.h"

int main()
{
	int time = 0;
	int ct = 0; //used for context switch;
	rq = readyQueue();
	oq = outputQueue();
	wq = waitQueue(); //used by I/O;

	f = open("file"); // f is file descriptor;
	line = readline(f);

	while(true){
		t1 = t2 = t3 = 0;

		/* Read Trace Data */
		while line.startTime <= time
			enqueue(rq, line);
		line = readline(f);
		if line == EOF
			break;
		t1 = line.startTime - time;

		/* Check Executing Queue */
		status = check_exe_sta(exe_task);
		switch(status){
		/* I/O Interrupt */
		case 1: waitQueue(wq, exe_task);
				eqExe(dequeue(rq));
				ct = 2;
		/* Proc Preemption */
		case 2: updatePri(exe_task, status);
				enqueue(rq, exe_task);
				eqExe(dequeue(rq));
				ct = 2;
		/* Use up time slice */
		case 3: updatePri(exe_task, status);
				enqueue(rq, exe_task) || enqueue(oq, exe_task)
				eqExe(dequeue(rq));
				ct = 2;
		default:if(ct > 0) // context switch
					ct -= t;
				else
					exe_task.t_slice -= t;
					exe_task.t_nextIO -= t;
		}
		t2 += ct ? ct : min(exe_task.t_slice, exe_task.t_nextIO);
		
		/* Check waitQueue */
		if(peek(wq).t_io == 0)
			enqueue(rq, dequeue(wq));
		else
			peek(wq).t_io -= t;
		t3 = peek(wq).t_io;

		/* Update Time */
		t = min(t1, t2, t3);
		time += t;
	}	
}

