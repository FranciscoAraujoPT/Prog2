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
	
	if(no == NULL){
        return 0;
	}

	if(min < 0){
		return 0;
	}
	
	int n=0;

	n += filtra_strings(no->esquerda, min);
	if(strlen(no->str) > min){
		printf("%s\n", no->str);
		n++;
	}
    n += filtra_strings(no->direita, min);

	return n;
}

/*** problema 2.2 ***/
int* caminho_pontos(grafo *g, int *pontos, int n, int *tam_caminho)
{
	if(g == NULL){
		return NULL;
	}

	if(pontos == NULL){
		return NULL;
	}

	if(tam_caminho == NULL){
		return NULL;
	}

	if(n <= 1){
		return NULL;
	}

	int *aux, k = 0;
	int *caminho_total = (int*)malloc(sizeof(int)*g->tamanho);

	for(int i=1;i<n;i++)
	{
		aux = grafo_bfs(g,pontos[i-1], pontos[i], tam_caminho);
		for(int j=0;j<(*tam_caminho);j++)
		{
			caminho_total[k]=aux[j];
			k++;
		}
		k--;
		free(aux);
	}

	*tam_caminho = k+1;

	return caminho_total;
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
