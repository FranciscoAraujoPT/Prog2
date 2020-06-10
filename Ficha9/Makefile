######MakeFile######
all: teste_grafo

teste_grafo: grafo.o vetor.o
	gcc teste_grafo.c grafo.o vetor.o -g -Wall

vetor.o: vetor.c vetor.h
	gcc -c vetor.c -Wall -g

grafo.o: grafo.c grafo.h
	gcc -c grafo.c -Wall -g

clean: 
	rm vetor.o grafo.o