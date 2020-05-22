teste_armazem.c: contentor.o armazem.o fila_contentores.o pilha_contentores.o
	gcc teste_armazem.c contentor.o armazem.o fila_contentores.o pilha_contentores.o -g -Wall

contentor.o: contentor.c contentor.h
	gcc -c contentor.c -Wall -g

armazem.o: armazem.c armazem.h
	gcc -c armazem.c -Wall -g

fila_contentores.o: fila_contentores.c fila_contentores.h
	gcc -c fila_contentores.c -Wall -g

pilha_contentores.o: pilha_contentores.c pilha_contentores.h
	gcc -c pilha_contentores.c -Wall -g

clean: 
	rm teste_armazem contentor.o armazem.o fila_contentores.o pilha_contentores.o