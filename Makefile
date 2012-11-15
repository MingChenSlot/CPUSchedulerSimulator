all: sim

CC = gcc -std=c99
CFLAGS = -pedantic -Wall -O3
objects = main.o tasks.o

sim: $(objects)
	$(CC) $(CFLAGS) -o sim $(objects) 

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

tasks.o: tasks.c tasks.h
	$(CC) $(CFLAGS) -c tasks.c

clean:
	rm -f sim *.o *~
