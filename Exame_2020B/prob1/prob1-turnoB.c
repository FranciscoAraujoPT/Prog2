#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

#define max(a,b)  ((a)<(b) ? (b) : (a))
#define min(a,b)  ((a)>(b) ? (b) : (a))





/**********//////////////////////////////**********/
//1.1
//temperatura: vetor com valores de temperatura
//n: numero de valores no vetor temperatura
//retorna NULL em caso de erro
float * realce_temperaturas (float * temperatura, int n)
{
	
}

//1.2
/* Qual a complexidade da função anterior? 


*/

//1.3
//temperatura: vetor com valores de temperatura
//n: numero de valores no vetor temperatura
//imprime temperatura realcada de forma ordenada
void impressao_ordenada_realcada (float * temperatura, int n)
{
	
}


/******************************************************************/
int main()
{
	int N = 7;
	float aux[]={24.1 , 24.1 ,25.0, 26.0, 26.0, 26.0, 23.7};

	float  * res = realce_temperaturas (aux, N);
	if (!res) return -1;
	printf ("temperaturas realcadas: ");
	for (int i = 0; i <N; i++)
		printf ("%.2f ", res[i]);
	printf ("\n");
	impressao_ordenada_realcada (aux, N);
	
	return 0;
}