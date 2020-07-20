#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "grafo.h"

//2.1
void influenciado (grafo *g, int utl, int * vt_influencias)
{
	
}

int * ZonaInfluencia (grafo *g, int utl)
{
	
}

//2.2
/* Suponha que quer usar uma árvore AVL para ordenar um conjunto de valores. 
Descreva como procederia. 
Qual a complexidade para este processo de ordenação? Justifique de forma 
simples e objetiva. 


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
	
	int * res= ZonaInfluencia (gf, 0);
	printf ("Influencia do utilizador 0\n");
	for (int i = 0; i< N; i++)
	{
		printf ("%d ", res[i]);
	}
	printf ("\n");
	free(res);
	res= ZonaInfluencia (gf, 3);
	printf ("Influencia do utilizador 3\n");
	for (int i = 0; i< N; i++)
	{
		printf ("%d ", res[i]);
	}
	printf ("\n");
	free(res);
	
	grafo_apaga(gf);
	
	return 0;
}