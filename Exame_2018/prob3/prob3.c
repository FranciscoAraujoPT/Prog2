#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "tabdispersao.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 3.1 ***/
void imprime_capitais(char *nomeFicheiro, int k)
{
	if(nomeFicheiro == NULL){
		return;
	}

	if(k<=0){
		return;
	}

	heap* h = heap_nova(100);

	if(h == NULL){
		return;
	}

	tabela_dispersao* td = tabela_nova(100, hash_djbm);

	if(td == NULL){
		heap_apaga(h);
		return;
	}
	
	FILE * f = fopen(nomeFicheiro, "r");

	char pais[20], capital[20], *aux;
	int populacao, indice;
	td_elemento* elem;	
	int i=0;

	
	while(fscanf(f,"%s %s %d", pais, capital, &populacao) != EOF) //Total: O(n log n)
	{
		heap_insere(h, capital, -populacao);//O(log N)
		tabela_insere(td, capital, pais); //O(1)
		i++;
	}


	if(h->tamanho > 0){
		for(int i=0;i<k;i++)//Total: O(n log n)
		{
			aux = heap_remove(h); //O(log n)
			printf("%s -", aux);
			indice = td->hfunc(aux, td->tamanho);
			elem = td->elementos[indice];
			while(elem != NULL) //O(1) ???
			{
				if(strcmp(elem->obj->chave, aux) == 0){
					printf("%s\n", elem->obj->valor);
				}
				elem = elem->proximo;
			}
			free(aux);
		}
	}

	heap_apaga(h);
	tabela_apaga(td);
	fclose(f);

}

/*** problema 3.2 ***/
/*
complexidade do algoritmo: O(n log n)

justificacao:

... -> O(1)

while -> O(N)
   heap_insere -> O(log N)
   tabela_insere -> O(1)

for -> O(1)
   heap_remove -> O(log N)

... -> O(1)

Ou seja, a complexidade total é O(N) * O(log N) + O(N) * O(log N) -> O(N log N)
*/

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define MAX_STR 500

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	
	/* inicio teste prob3.1 */
	{
		imprime_capitais("capitais.txt", 7);
	}
    /* fim teste prob3.1 */

	return 0;
}
