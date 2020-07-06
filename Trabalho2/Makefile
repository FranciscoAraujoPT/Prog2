#####Makefile######
all: social-teste

social-teste: grafo.o stnova.o tabdispersao.o
	gcc social-teste.c grafo.o stnova.o tabdispersao.o -g -Wall

grafo.o: grafo.c grafo.h
	gcc -c grafo.c -g -Wall

stnova.o: stnova.c stnova.h
	gcc -c stnova.c -g -Wall

tabdispersao.o: tabdispersao.c tabdispersao.h
	gcc -c tabdispersao.c -g -Wall

clear:
	rm grafo.o stnova.o tabdispersao.o