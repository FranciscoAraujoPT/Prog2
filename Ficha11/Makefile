all: dict

dict: avl.o
	gcc dict.c avl.o -g -Wall

avl.o: avl.c avl.h
	gcc -c avl.c -g -Wall

clear:
	rm avl.o