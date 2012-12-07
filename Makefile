all: esim psim

CC = gcc -std=c99
CFLAGS = -pedantic -Wall -O3
objects1 = main.o sched.o input.o disk.o exp_queue.o queue.o 
objects2 = main.o sched.o input.o disk.o priorityQ.o red_black_tree.o queue.o misc.o

esim: $(objects1)
	$(CC) $(CFLAGS) -o esim $(objects1) 

psim: $(objects2)
	$(CC) $(CFLAGS) -o psim $(objects2)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

sched.o: sched.c sched.h
	$(CC) $(CFLAGS) -c sched.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

disk.o: disk.c disk.h
	$(CC) $(CFLAGS) -c disk.c

exp_queue.o: exp_queue.c exp_queue.h
	$(CC) $(CFLAGS) -c exp_queue.c

priorityQ.o: priorityQ.c priorityQ.h
	$(CC) $(CFLAGS) -c priorityQ.c

red_black_tree.o: red_black_tree.c red_black_tree.h
	$(CC) $(CFLAGS) -c red_black_tree.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

misc.o: misc.c misc.h
	$(CC) $(CFLAGS) -c misc.c

clean:
	rm -f *sim *.o *~
