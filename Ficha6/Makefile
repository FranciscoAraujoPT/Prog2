arvores.c: bst.o avl.o
	gcc arvores.c bst.o avl.o -g -Wall

bst.o: bst.c bst.h
	gcc -c bst.c -Wall -g

avl.o: avl.c bst.h
	gcc -c avl.c -Wall -g

clean: 
	rm arvores.c bst.o avl.o