#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

//1.1
//temperatura: vetor com valores de temperatura
//n: numero de valores no vetor temperatura
//saida: tamanho do maior planalto no vetor
//retorna -1 em caso de erro
int maior_planalto (float * temperatura, int n)
{
	
}

//1.2
/* Qual a complexidade da função anterior? 


*/

//1.3
//temperatura: vetor com valores de temperatura
//n: numero de valores no vetor temperatura
//imprime planaltos de forma ordenada
void impressao_ordenada_planaltos(float * temperatura, int n)
{
	
}

/******************************************************************/
int main()
{
	int N = 7;
	float aux[]={24.1 , 24.1 ,25.0, 26.0, 26.0, 26.0, 23.7};

	int res = maior_planalto (aux, N);
	
	printf ("O maior planalto mede %d\n", res);
	
	impressao_ordenada_planaltos(aux, N);
	
	return 0;
}