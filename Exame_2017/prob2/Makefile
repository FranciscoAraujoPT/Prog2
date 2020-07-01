#####Makefile#####
all:prob2

prob2: grafo.o heap.o tabdispersao.o
	gcc prob2.c grafo.o heap.o tabdispersao.o -g -Wall

grafo.o:
	gcc -c grafo.c -g -Wall

heap.o:
	gcc -c heap.c -g -Wall

tabdispersao.o:
	gcc -c tabdispersao.c -g -Wall