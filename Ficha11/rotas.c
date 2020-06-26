#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "grafo.h"
#include "heap.h"

#define MAX_HEAP 25

int proximas_n_chegadas(lista *tempos, lista *origens, lista *aeroportos, int n)
{
	/* alinea 4.1 */
	if(tempos == NULL){
		return 0;
	}

    if(origens == NULL){
		return 0;
	}

	if(aeroportos == NULL){
		return 0;
	}

	if(n<0 || n>25){
		return 0;
	}

	int i=0;
	heap* h = heap_nova(MAX_HEAP);
	l_elemento* ori = origens->inicio;
	l_elemento* t = tempos->inicio;
	l_elemento* aer = aeroportos->inicio;
	char* palavra;

	while(ori && t && aer)
	{
		/*Pesquisa na lista aeroporto pelo aeroporto correto atraves do indice dado pela lista origens*/
		for(i=0;i<atoi(ori->str);i++)
		{
			aer=aer->proximo;
		}

		heap_insere(h, aer->str, atoi(t->str));
		ori = ori->proximo;
		t = t->proximo;
		aer = aeroportos->inicio;
	}

	for(i=0;i<n;i++)
	{
		palavra = h->elementos[1]->valor;
		printf("%d: %s\n", i+1, palavra);
		free(h->elementos[1]->valor);
		h->elementos[1]->valor = NULL;
		heap_remove(h);
		
	}

	heap_apaga(h);

    return 1;
}

lista* pesquisa_destinos (grafo *rotas, lista *aeroportos, const char *origem)
{
	/* alinea 4.2 */
	if(rotas == NULL){
		return NULL;
	}

	if(aeroportos == NULL){
		return NULL;
	}

	if(origem == NULL){
		return NULL;
	}	

	lista* lst = lista_nova();

	if(lst == NULL){
		return NULL;
	}

	l_elemento* aer = aeroportos->inicio;
	int indice=0;

	while(aer)
	{
		if(strcmp(origem,aer->str) == 0){
			break;
		}
		indice++;
		aer = aer->proximo;
	}
	

	lista_no* aux = rotas->adjacencias[indice].inicio;

    while (aux)
    {
		if(aux->vertice >= 0){
			aer = aeroportos->inicio;
			for(int j=0;j<aux->vertice;j++)
			{
				aer=aer->proximo;
			}
			lista_insere(lst, aer->str, NULL);
		}
		aux = aux->proximo;
    }

	return lst;
}

/* Aqui começa o código de teste. Não modificar! */

grafo* carrega_rotas (lista *aeroportos, const char *filename)
{
	if(!filename) return NULL;
	grafo* g=NULL;
	FILE *f;
	int origem, destino;
	f = fopen(filename, "r");
	if (!f) {
		printf("Erro na leitura do ficheiro: %s\n",filename);
		return NULL;
	}
	g = grafo_novo(lista_tamanho(aeroportos), NAODIRECIONADO);
	if (!g) {
			printf("Erro na criacao do grafo\n");
			return NULL;
	}
	while(fscanf(f, "%d\t%d", &origem, &destino) == 2) {
		grafo_adiciona(g, origem, destino);
	}
	fclose(f);
	return g;
}

int main()
{
	FILE *f;
	grafo *g=NULL;
	lista *aeroportos;
	char* buff;
	size_t n;
	int i;

	setvbuf(stdout, NULL, _IONBF, 0);
	f = fopen("aeroportos.txt", "r");
	aeroportos = lista_nova();
	buff=NULL;
	n=0;
	while(getline(&buff,&n,f)!=-1) {
		buff[strlen(buff)-1]='\0';
		lista_insere(aeroportos, buff, NULL);
	}
	free(buff);
	fclose(f);

	g = carrega_rotas(aeroportos, "rotas.txt");

	{
		FILE *f;
		char tempo[5], origem[10];
		lista *tempos, *origens;

		f = fopen("chegadas.txt", "r");
		tempos = lista_nova();
		origens = lista_nova();

		while(fscanf(f, "%s\t%s", tempo, origem) == 2) {
			lista_insere(tempos, tempo, NULL);
			lista_insere(origens, origem, NULL);
		}

		if(proximas_n_chegadas(tempos, origens, aeroportos, 5) != 1)
    		printf("Erro ao executar a funcao\n");

    	lista_apaga(tempos);
    	lista_apaga(origens);
    	fclose(f);
	}

	{
		printf("\n");
		const char *origem = "Lille (FR)";
		lista *l = pesquisa_destinos(g,aeroportos, origem);
		if(l == NULL)
			printf("Destinos diretos a partir de %s = 0\n", origem); 
		else
		{
			printf("Destinos diretos a partir de %s = %d\n", 
									origem, lista_tamanho(l));
			for(i=0;i<l->tamanho;i++)
				printf("%s\n",lista_elemento(l,i)->str);
			lista_apaga(l);
		}
	}

	grafo_apaga(g);
	lista_apaga(aeroportos);
	return 0;
}
