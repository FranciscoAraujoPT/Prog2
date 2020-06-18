#include "grafo_Ndirigidos.h"
#include <stdio.h>

int main()
{
	int i, adj[] = {1,2,1,3,1,4,2,5,3,5,4,5}, comp[] = {0,1,0,2,0,3,1,0,1,2,1,3,2,0,2,1,2,3,3,0,3,1,3,2};
	int comp2[] = {0,1,0,2,0,3,0,4,1,4,2,4,3,4};

	/* exemplo da alinea 1.2 
	grafo *g12 = grafo_deLista(adj, 6);
	grafo_imprime(g12);
	grafo_apaga(g12); */

	/* outros testes */
	printf("\nTeste 1:\n"); //Testa a função grafo_adiciona.
	grafo* g=grafo_novo(5);
	for(i=0;i<=10;i+=2){
		grafo_adiciona(g, adj[i]-1, adj[i+1]-1);
	}
	grafo_imprime(g);

	printf("\nTeste 2:\n");//Testa a função grafo_remove.
	grafo_remove(g, 2, 4);
	grafo_imprime(g);
	
	printf("\nTeste 3:\n");//Testa a função grafo_deLista.
	grafo *g12 = grafo_deLista(adj, 6);
	grafo_imprime(g12);
	grafo_apaga(g12);

	printf("\nTeste 4:\n");//Testa a função grafo_arestasSaida.
	vetor* v = grafo_arestasSaida(g, 0);
	for(i=0;i<3;i++){
		printf("%d\n", vetor_elemento(v, i));
	}

	printf("\nTeste 5:\n");//Testa a função grafo_arestasEntrada.
	v = grafo_arestasEntrada(g, 4);
	for(i=0;i<3;i++){
		printf("%d\n", vetor_elemento(v, i));
	}
	grafo_apaga(g);

	printf("\nTeste 6:\n");//Testa a função grafo_completo.	
	grafo *gcomp = grafo_deLista(comp, 12);
	grafo_imprime(gcomp);
	if(grafo_completo(gcomp)==1){
		printf("O grafo está completo.\n");
	} else {
		printf("O grafo não está completo.\n");
	}
	grafo_apaga(gcomp);

	printf("\nTeste 7:\n");//Testa a função grafo_eCelebridade.
	grafo *gcomp2 = grafo_deLista(comp2, 7);
	grafo_imprime(gcomp2);
	if(grafo_eCelebridade(gcomp2, 4)==1){
		printf("O vertice 4 é uma celebridade.\n");
	} else {
		printf("O vertice 4 não é uma celebridade.\n");
	}

	printf("\nTeste 8:\n");//Testa a função grafo_temCelebridade.
	if(grafo_temCelebridade(gcomp2)==1){
		printf("O grafo tem uma celebridade.\n");
	} else {
		printf("O grafo não tem uma celebridade.\n");
	}
	grafo_apaga(gcomp2);

	printf("\nFIM\n");

	return 0;
}
