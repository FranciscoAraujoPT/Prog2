######MakeFile######
all: teste_tabdispersao

teste_tabdispersao: tabdispersao.o
	gcc teste_tabdispersao.c tabdispersao.o -g -Wall

tabdispersao.o: tabdispersao.c tabdispersao.h
	gcc -c tabdispersao.c -Wall -g

clean: 
	rm tabdispersao.o