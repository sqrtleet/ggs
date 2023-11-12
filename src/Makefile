CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: main

main: graph.o io.o stack.o rpn.o
	$(CC) $(CFLAGS) graph.o io.o stack.o rpn.o -o main -lm

graph.o : graph.c
	$(CC) $(CFLAGS) -c graph.c

rpn.o : rpn.c rpn.h
	$(CC) $(CFLAGS) -c rpn.c

io.o : io.c io.h
	$(CC) $(CFLAGS) -c io.c

stack.o : stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

rebuild : clean all

clean:
	rm -rf *.o main
