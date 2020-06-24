#####Ex1#####
# all: dict

# dict: avl.o
# 	gcc dict.c avl.o -g -Wall

# avl.o: avl.c avl.h
# 	gcc -c avl.c -g -Wall

# clear:
# 	rm avl.o

#####Ex2#####
all: eventos

eventos: heap.o
	gcc eventos.c heap.o -g -Wall

heap.o:
	gcc -c heap.c -g -Wall

clear:
	rm heap.o