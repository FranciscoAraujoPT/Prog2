#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "fila.h"


/*** problema 1.1 ***/
void vetor_inverte(vetor *v)
{
	/* complexidade do algoritmo: O(n) */

	if(v == NULL){
		return;
	}

	if(v->tamanho <= 1){
		return;
	}

	for(int i=0; i<v->tamanho; i++)
	{
		vetor_insere(v, v->elementos[v->tamanho-1].str, i);
		vetor_remove(v, v->tamanho-1);
	}

}

/*** problema 1.2 ***/
fila* subfila_maior(fila *f, int limiar)
{
	if(f == NULL){
		return NULL;
	}

	if(limiar < 0){
		return NULL;
	}

	fila *maior = fila_nova();

	if(maior == NULL){
		return NULL;
	}

	filaItem * aux = f->cabeca;

	while(aux != f->cauda)
	{
		if(strlen(aux->string) > limiar){
			fila_push(maior, aux->string);
		}

		aux = aux->proximo;
	}

	return maior;
	
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
	/* inicio teste prob1.1 */
	{
		vetor *v;
		int i;
	
		v = vetor_novo();
		vetor_insere(v, "Um", -1);
		vetor_insere(v, "Dois", -1);
		vetor_insere(v, "Tres", -1);
		vetor_insere(v, "Quatro", -1);
		vetor_insere(v, "Cinco", -1);

		puts("\n* Problema 1.1 *");
		printf("Vetor Original: ");
		if(v->tamanho > 0)
			printf("%s", v->elementos[0].str);
		for(i=1; i<v->tamanho; i++)
			printf(" -> %s", v->elementos[i].str);

		vetor_inverte(v);

		printf("\nVetor Invertido: ");
		if(v->tamanho > 0)
			printf("%s", v->elementos[0].str);
		for(i=1; i<v->tamanho; i++)
			printf(" -> %s", v->elementos[i].str);
		
		printf("\n\n");
		vetor_apaga(v);

	}
	/* fim teste prob1.1 */

	/* teste problema 1.2 */
	{
		fila *f, *fila_maior;
		filaItem *fitem;

		f = fila_nova();
		fila_push(f, "Amarelo");
		fila_push(f, "Verde");
		fila_push(f, "Preto");
		fila_push(f, "Azul");
		fila_push(f, "Laranja");
		fila_push(f, "Vermelho");
		fila_push(f, "Branco");

		puts("\n* Problema 1.2 *");
		printf("Fila: ");

		fitem=f->cabeca;
		if(fitem!=NULL)
			printf("%s", fitem->string);
		fitem=fitem->proximo;
		while (fitem!=NULL)
		{
			printf(" | %s", fitem->string);
			fitem=fitem->proximo;
		}

		printf("\n");

		fila_maior = subfila_maior(f, 6);
		printf("Sub-Fila maior que 6: ");
		if(fila_maior != NULL)
		{
			fitem=fila_maior->cabeca;
			if(fitem!=NULL)
				printf("%s", fitem->string);
			fitem=fitem->proximo;
			while (fitem!=NULL)
			{
				printf(" | %s", fitem->string);
				fitem=fitem->proximo;
			}
		}
		printf("\n");
		if(fila_tamanho(f) != 7)
			printf("ERRO: Fila inicial foi alterada\n");

		fila_apaga(f);
		fila_apaga(fila_maior);
		puts("");
	}
	/* fim teste prob1.2 */

	return 0;
}
