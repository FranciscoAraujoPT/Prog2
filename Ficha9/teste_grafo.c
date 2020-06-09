#include "grafo.h"
#include <stdio.h>

int main()
{
	/* exemplo da alinea 1.2 */
	int adj[] = {1,2,1,3,1,4,2,5,3,5,4,5};
	grafo *g12 = grafo_deLista(adj, 6);
	grafo_imprime(g12);
	grafo_apaga(g12);

	/* outros testes */




	printf("\nFIM\n");

	return 0;
}
