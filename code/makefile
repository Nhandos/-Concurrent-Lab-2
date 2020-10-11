CC=gcc
CFLAGS=-g -Wall -pedantic
EXECS= lab2part1 lab2part2 lab2part3 lab2part4

all: $(EXECS)
debug: CFLAGS+=-DDEBUG=1
debug: all

lab2part1: lab2part1.c
	$(CC) $(CFLAGS) -o lab2part1 lab2part1.c -lpthread

lab2part2: lab2part2.c
	$(CC) $(CFLAGS) -o lab2part2 lab2part2.c -lpthread 

lab2part3: lab2part3.c
	$(CC) $(CFLAGS) -o lab2part3 lab2part3.c -lpthread 
	
lab2part4: lab2part4.c
	$(CC) $(CFLAGS) -o lab2part4 lab2part4.c -lpthread 

clean:
	rm -rf $(EXECS)