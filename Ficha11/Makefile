#####Ex1#####
# all: dict

# dict: avl.o
# 	gcc dict.c avl.o -g -Wall

# avl.o: avl.c avl.h
# 	gcc -c avl.c -g -Wall

# clear:
# 	rm avl.o

#####Ex2#####
# all: eventos

# eventos: heap.o
# 	gcc eventos.c heap.o -g -Wall

# heap.o: heap.c heap.h
# 	gcc -c heap.c -g -Wall

# clear:
# 	rm heap.o

#####Ex3#####
# all: arvore

# arvore: lista.o avl.o
# 	gcc arvore.c lista.o avl.o -g -Wall

# lista.o: lista.c lista.h
# 	gcc -c lista.c -g -Wall

# avl.o: avl.c avl.h
# 	gcc -c avl.c -g -Wall

# clear:
# 	rm lista.o avl.o

#####Ex4#####
all: rotas

rotas: lista.o heap.o grafo.o
	gcc rotas.c lista.o heap.o grafo.o -g -Wall

lista.o: lista.c lista.h
	gcc -c lista.c -g -Wall

heap.o: heap.c heap.h
	gcc -c heap.c -g -Wall

grafo.o: grafo.c grafo.h
	gcc -c grafo.c -g -Wall

clear:
	rm grafo.o heap.o lista.o
