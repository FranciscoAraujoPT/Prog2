#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
armazem* armazem_novo(int comprimento, int altura)
{
	armazem* arma =(armazem*)malloc(sizeof(armazem));

	if(arma == NULL)
		return NULL;

	arma->contentores = fila_nova();

	arma->comprimento = comprimento;
	arma->altura = altura;

	return arma;
}

/* alinea c) */
int armazem_vazio(armazem* armz)
{	
	if(armz->contentores->tamanho == 0){
		/* devolve vazio */
		return 1;
	} else 
		return 0;
}

/* alinea d) */
int armazem_cheio(armazem* armz)
{
	if(armz == NULL){
		return 1;
	}
	
	if(fila_tamanho(armz->contentores) < armz->comprimento){
		return 0;
	}	else if(pilha_tamanho(fila_back(armz->contentores)) < armz->altura){
		return 0;
	} else
		return 1;
}

/* alinea e) */
int armazenar_contentor(armazem* armz, contentor* contr)
{
	if(armazem_cheio(armz) == 1)
		/* devolve nao ha' espaco */
		return 0;

	pilha *last = fila_back(armz->contentores);
	
	if(last == NULL){
		last = pilha_nova();
		fila_push(armz->contentores, last);
	}

	if(pilha_tamanho(last) < armz->altura){
		pilha_push(last, contr);
	} else {
		last = pilha_nova();
		pilha_push(last, contr);
		fila_push(armz->contentores, last);
	}

	return 1;
}

/* alinea f) */
contentor* expedir_contentor(armazem* armz)
{
	if(armz == NULL || armz->contentores == NULL)
		return NULL;
	
	pilha* first=fila_front(armz->contentores);
	contentor* contr=pilha_top(first);

	if(pilha_tamanho(first) > 1){
		pilha_pop(first);
		return contr;
	} else {
		pilha_pop(first);
		fila_pop(armz->contentores);
		return contr;
	}
}
