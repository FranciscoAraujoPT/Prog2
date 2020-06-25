#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "avl.h"

void avl_em_ordem(no_avl* no, lista *lst)
{
    if(no == NULL){
        return;
	}

    avl_em_ordem(no->esquerda, lst);
	lista_insere(lst, no->str, NULL);
	avl_em_ordem(no->direita, lst);
	
}

void guarda_conteudo(arvore_avl *arvore, lista *lst)
{
	/* alinea 3.1 */
	if(arvore == NULL){
		return;
	}

	if (lst == NULL){
		return;
	}

	avl_em_ordem(arvore->raiz, lst);
	

}

lista* descobre_segredo(arvore_avl *arvore, lista *indicacoes)
{
	/* alinea 3.2 */

	no_avl* aux = arvore->raiz;
	l_elemento* aux2 = indicacoes->inicio;

	while(aux2 != NULL)
	{
		if(strcmp("esquerda", aux2->str) == 0){
			aux = aux->esquerda;
			strcpy(aux2->str, aux->str);
		} else if(strcmp("direita", aux2->str) == 0){
			aux = aux->direita;
			strcpy(aux2->str, aux->str);
		}
		aux2 = aux2->proximo;
	}

	return indicacoes;
}


/* v-- nao alterar funcao main --v */

int main()
{
	char data[][20] = { "prog2", "mt2", "trabalho", "e'", "muito", "zzzz...",
						"dificil", "facil", "nada", "verdade"};
	
	{
		arvore_avl *T;
		lista *lst;
		int i;

		T = avl_nova();
		for(i=0; i<10; i++)
			avl_insere(T, data[i]);

		lst = lista_nova();
		guarda_conteudo(T, lst);

		printf("Conteudo: ");
		if (lista_tamanho(lst) != 0)
		{
			for (i = 0; i < lista_tamanho(lst); i++)
				printf ("%s  ", lista_elemento(lst, i)->str);
			puts("");
		}
		
		
		avl_apaga(T);
		lista_apaga(lst);
	}

	{
		int i;
		arvore_avl *T;
		lista *res, *indicacoes;
		
		printf("\n");

		T = avl_nova();
		for(i=0; i<10; i++)
			avl_insere(T, data[i]);

		indicacoes = lista_nova();
		lista_insere(indicacoes, "esquerda", NULL);
		lista_insere(indicacoes, "esquerda", NULL);
		lista_insere(indicacoes, "direita", NULL);
		
		res = descobre_segredo(T, indicacoes);
		
		printf("Segredo: ");
		if(res)
		{
			for(i=0; i<res->tamanho; i++)
				printf("%s ", lista_elemento(res, i)->str);
		}
		
		avl_apaga(T);
		printf("\n");
	}
	

	return 0;
}
