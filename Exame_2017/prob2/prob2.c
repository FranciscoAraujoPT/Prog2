#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabdispersao.h"
#include "heap.h"
#include "grafo.h"

/*** problema 2.1 ***/
grafo * grafo_intersecao(grafo *g1, grafo *g2)
{

	return NULL;
}

/*** problema 2.2 ***/
void imprime_ordenado(tabela_dispersao *td)
{
	/* complexidade do algoritmo: ________________ */


}

/*** problema 2.3 ***/
/*
complexidade do algoritmo:

justificacao:

*/

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_STR 500

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fp=fopen("paises.txt", "r");
	char str_aux[MAX_STR], *str;

	/* teste problema 2.1 */
	{
		puts("\n* Problema 2.1 *");
		grafo * g1 = grafo_novo(6, DIGRAFO);
		grafo * g2 = grafo_novo(6, DIGRAFO);
		grafo_adiciona(g1,0,4);
		grafo_adiciona(g1,1,0);
		grafo_adiciona(g1,1,4);
		grafo_adiciona(g1,1,5);
		grafo_adiciona(g1,2,1);
		grafo_adiciona(g1,3,2);
		grafo_adiciona(g1,4,3);
		grafo_adiciona(g1,5,4);
		grafo_adiciona(g2,0,4);
		grafo_adiciona(g2,1,0);
		grafo_adiciona(g2,1,4);
		grafo_adiciona(g2,1,5);
		grafo_adiciona(g2,2,3);
		grafo_adiciona(g2,5,4);
		grafo * g3=grafo_intersecao(g1,g2);
		if (g3) grafo_imprime(g3);
		grafo_apaga(g1);
		grafo_apaga(g2);
		grafo_apaga(g3);
		puts("");
	}

	/* teste problema 2.2 */
	{
		char *pais, res[100] = "";
		tabela_dispersao *td;
		objeto *obj;
		FILE *fp;

		puts("\n* Problema 2.2 *");
		td = tabela_nova(101, hash_djbm);
		fp=fopen("cidades.txt", "r");
		while(fgets(res, 100, fp) != NULL)
		{
			if(res[strlen(res)-1] == '\n')
			 	res[strlen(res)-1] = '\0';
			pais = strchr(res, ',') + 1;
			obj = tabela_valor(td, pais);
			if(obj == NULL)
				tabela_insere(td, pais, 1);
			else
				obj->valor++;
		}
		imprime_ordenado(td);
		tabela_apaga(td);
	}
	puts("");

	fclose(fp);
	return 0;
}
