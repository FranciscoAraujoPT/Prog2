#######Makefile#######
all:teste_grafo

teste_grafo: grafo.o
	gcc teste_grafo.c grafo.o -g -Wall

grafo.o: grafo.c grafo.h
	gcc -c grafo.c -g -Wall

clear:
	rm grafo.o