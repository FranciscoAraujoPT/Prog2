######MakeFile######
all: teste_grafo

teste_grafo: grafo.o vetor.o
	gcc teste_grafo.c vetor.o grafo_Ndirigidos.o -g -Wall

vetor.o: vetor.c vetor.h
	gcc -c vetor.c -Wall -g

grafo.o: grafo.c grafo.h
	gcc -c grafo.c -Wall -g

##grafo_Ndirigidos.o: grafo_Ndirigidos.c grafo_Ndirigidos.h
	##gcc -c grafo_Ndirigidos.c -Wall -g

clean: 
	rm vetor.o grafo.o
