all: prob2

prob2: grafo.o avl.o
	gcc prob2.c grafo.o avl.o -g -Wall

grafo.o:
	gcc -c grafo.c -g -Wall

avl.o:
	gcc -c avl.c -g -Wall