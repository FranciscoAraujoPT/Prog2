#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "grafo.h"

//2.1
grafo * grafo_quadrado (grafo *g)
{
	
}

//2.2
/* Se tivesse um grafo g representado pela sua matriz de adjacência m, 
como poderia obter a matriz de adjacência do quadrado do grafo g? 
Qual a complexidade desse cálculo, em função de N, onde N é o número de nós do grafo? 
Justifique de forma simples e objetiva.  


*/


/******************************************************************/
int main()
{
	int N = 7;
	grafo* gf = grafo_novo(N, DIGRAFO);
	
	grafo_adiciona(gf, 0, N-1);
	grafo_adiciona(gf, N-1, 3);
	grafo_adiciona(gf, 3, 0);
	grafo_adiciona(gf, 5, 1);
	grafo_adiciona(gf, 3, 1);
	grafo_adiciona(gf, N-1, 5);
	
	grafo * gq = grafo_quadrado (gf);
	
	printf ("grafo quadrado\n");
	grafo_imprime(gq);
	
	grafo_apaga(gf);
	grafo_apaga(gq);
	
	return 0;
}