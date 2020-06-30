#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vetor.h"
#include "lista.h"
#include "fila.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
vetor* encontra_nomes(vetor *vec1, vetor *vec2)
{
	/* complexidade do algoritmo: ______________ */

	return NULL;
}

/*** problema 2.2 ***/
fila* filtra_nomes(lista *lst, char *existe)
{
	return NULL;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

vetor* lerParaVetor(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	vetor* v;

	if (ficheiro == NULL)
		return NULL;

	v = vetor_novo();

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
		*nlptr = '\0';
		vetor_insere(v,buffer,v->tamanho);
	}

	return v;
}

lista* lerParaLista(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	lista* l;

	if (ficheiro == NULL)
		return NULL;

	l = lista_nova();

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
		*nlptr = '\0';
		lista_insere(l,buffer,NULL);
	}

	return l;
}

int main()
{
	FILE *f;
	vetor *v1, *v2, *v;
	lista *l;
	fila *resultado;

	/* testes */
	f = fopen("nomes1.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	v1 = lerParaVetor(f);
	rewind(f);
	l = lerParaLista(f);
	fclose(f);

	f = fopen("nomes2.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	v2 = lerParaVetor(f);
	fclose(f);

	/* inicio teste prob1.1 */
	v = encontra_nomes(v1, v2);
	if(v)
		printf("\nVetor resultante contem %d nomes.\n", vetor_tamanho(v));
	else
		printf("\nencontra_nomes retornou NULL\n");
	/* fim teste prob1.1 */

	/* inicio teste prob1.2 */
	resultado = filtra_nomes(l, "MARIA");
	if(resultado)
	{
		int n=0;
		printf("\nNomes filtrados (total de %d):\n", fila_tamanho(resultado));
		while (!fila_vazia(resultado) && n<3) {
			printf("%s\n", fila_front(resultado));
			fila_pop(resultado);
			n++;
		}
		if(fila_tamanho(resultado) > 2)
		{
			puts("...");
			while (fila_tamanho(resultado) > 1)
				fila_pop(resultado);
			printf("%s\n", fila_front(resultado));
			fila_pop(resultado);
		}
		else {
			while (!fila_vazia(resultado)) {
					printf("%s\n", fila_front(resultado));
					fila_pop(resultado);
				}
		}

		if(lista_tamanho(l) != 289)
			printf("Nem todos os nomes foram removidos da lista (tamanho: %d; esperado: 289)\n", lista_tamanho(l));
	}
	else
		printf("\nfiltra_nomes retornou NULL\n\n");
	/* fim teste prob1.2 */

	vetor_apaga(v1);
	vetor_apaga(v2);
	vetor_apaga(v);
	lista_apaga(l);
	fila_apaga(resultado);

	return 0;
}
