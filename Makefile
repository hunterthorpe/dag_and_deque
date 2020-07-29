# Makefile for parkranger DAG

# The compiler flags used when compiling
CFLAGS=-Wall -Wno-comment

a1: main.o deque.o parkranger.o util.o
	gcc $(CFLAGS) -o a1 main.o deque.o parkranger.o util.o

main.o: main.c deque.h util.h
	gcc $(CFLAGS) -c main.c

deque.o: deque.c deque.h util.h
	gcc $(CFLAGS) -c deque.c

parkranger.o: parkranger.c parkranger.h util.h
	gcc $(CFLAGS) -c parkranger.c

util.o: util.c util.h
	gcc $(CFLAGS) -c util.c


# This .PHONY command declares the "clean" rule as a phony one, i.e., it means
# that the clean rule will run instructions but it wont create a file called
# "clean" like a normal rule would (e.g., the util.o rule results in a file
# called util.o being created).
.PHONY: clean

clean:
	rm *.o
	rm a1
