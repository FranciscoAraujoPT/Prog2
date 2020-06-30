#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "grafo.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2.1 ***/
int filtra_strings(no_avl *no, int min)
{
	
	return 0;
}

/*** problema 2.2 ***/
int* caminho_pontos(grafo *g, int *pontos, int n, int *tam_caminho)
{
	
	return NULL;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define MAX_STR 500
#define MAX_LINE	100
#define MAX_SIZE 1000

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fp=fopen("paises.txt", "r");
	char str_aux[MAX_STR], *res;
	
	/* inicio teste prob2.1 */
	{
		arvore_avl *arv;
		int i, res;
		puts("\n* Problema 2.1 *");
		arv = avl_nova();
		while(fgets(str_aux,MAX_STR,fp) != NULL)
		{
			if(str_aux[strlen(str_aux)-1] == '\n')
				str_aux[strlen(str_aux)-1] = '\0';
			avl_insere(arv, str_aux);
		}
		
		res = filtra_strings(arv->raiz, 20);
		if(res != 8)
			printf("ERRO: valor de retorno nao corresponde ao tamanho esperado (%d-%d)\n", res, 8);

		avl_apaga(arv);
	}
	/* fim teste prob2.1 */

	rewind(fp);

	/* inicio teste prob2.2 */
	{
		grafo *g;
		int *caminho, n=0, i;
		int pontos[] = {0, 4, 5};

		puts("\n* Problema 2.2 *");
		g = grafo_novo(8, DIGRAFO);
		grafo_adiciona(g,0,4);
		grafo_adiciona(g,1,0);
		grafo_adiciona(g,1,5);
		grafo_adiciona(g,2,1);
		grafo_adiciona(g,3,2);
		grafo_adiciona(g,4,3);
		grafo_adiciona(g,5,4);
		grafo_adiciona(g,6,3);
		grafo_adiciona(g,7,2);
		grafo_adiciona(g,7,6);
		grafo_adiciona(g,1,7);

        caminho = caminho_pontos(g, pontos, 3, &n);

		printf("Caminho completo: ");
        for (i = 0; i < n; i++)
			printf("%d ", caminho[i]);
		puts("");

		free(caminho);
		grafo_apaga(g);
		puts("");
	}
	/* fim teste prob2.2 */

	fclose(fp);

	return 0;
}
