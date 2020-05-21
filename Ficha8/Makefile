######MakeFile######
all: prob1

prob1: heap.o avl.o
	gcc prob1.c heap.o avl.o -g -Wall

heap.o: heap.c heap.h
	gcc -c heap.c -Wall -g

avl.o: avl.c avl.h
	gcc -c avl.c -Wall -g

clean: 
	rm heap.o avl.o