#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "tabdispersao.h"

char* get_freguesia(char* rua);


//  ------------ a implementar ----------------
//1.1
// Adiciona a casa comercial de nome designacao e atividade comercial atividade na tabela comercio_zona.
// Se a casa comercial a inserir possui atividade ainda nao presente na zona (nao existe em atividades_zona),
// esta atividade ee inserida na tabela atividades_zona e a classe da casa comercial ee �top�.
// Caso contrario, a classe ee �normal�.
// A funcao retorna 0 se a casa comercial ja existe ou 1 se nao.
int adiciona_comercio(char* designacao, char* atividade, tabela_dispersao* comercio_zona,
		                                              tabela_dispersao* atividades_zona)
{
	if(comercio_zona == NULL){
		return 0;
	}

	if(atividades_zona == NULL){
		return 0;
	}

	if(designacao == NULL){
		return 0;
	}

	if(atividade == NULL){
		return 0;
	}

	if(tabela_existe(comercio_zona, designacao) == TABDISPERSAO_NAOEXISTE){
		tabela_insere(comercio_zona, designacao,"top");
		tabela_insere(atividades_zona, atividade, atividade);
		return 1;
	}

	int indice = comercio_zona->hfunc(designacao, comercio_zona->tamanho);

	strcpy(comercio_zona->elementos[indice]->obj->valor,"normal");
	
	return 0;
}


//  ------------ a implementar ----------------
// 1.2
// rmove a rua com menor numero de casas comerciais na freguesia freg da heap ruas
// retorna essa string
// retorna NULL em caso de erro
char *remove_rua_menos_comercio(heap *ruas, char *freg)
{
	if(ruas == NULL){
		return NULL;
	}

	if(freg == NULL){
		return NULL;
	}

	heap * aux = heap_nova(ruas->tamanho);
	char * aux2;

	while(ruas->tamanho>0){ //Total: O(n log n) + 2*O(log n) -> O(n log n)
		if(strcmp(get_freguesia(ruas->elementos[1]->valor), freg) == 0){
			aux2 = ruas->elementos[1]->valor;
			while(aux->tamanho>0){// 2*O(log n) * O(n) -> O(n log n)
				heap_insere(ruas, aux->elementos[1]->valor, aux->elementos[1]->prioridade); // O(log n);
				free(heap_remove(aux)); // O(log n);
			}
			heap_apaga(aux);
			return aux2;
		}
		heap_insere(aux, ruas->elementos[1]->valor, ruas->elementos[1]->prioridade); // O(log n);
		free(heap_remove(ruas));// O(log n);
	}

	while(aux->tamanho>0){// 2*O(log n) * O(n) -> O(n log n))
		heap_insere(ruas, aux->elementos[1]->valor, aux->elementos[1]->prioridade); // O(log n);
		free(heap_remove(aux));// O(log n);
	}

	heap_apaga(aux);
	return NULL;
}



//  ------------ a completar ----------------
//1.3
/*Comentar a complexidade da funcao 1.2

	O(n log n) (justificado em cima)
*/


/********************************************************************/
/********************************************************************/
// retorna referencia para a substring nome_freguesia na string "nome_rua_nome_freguesia"
char* get_freguesia(char* rua)
{
	char *b;
	b=strchr(rua,'_')+1;
	return b;
}

void verifica_valor(tabela_dispersao* td, char* ch, char *v)
{	
	int n=0;
	objeto *vtab;
	vtab = tabela_elementos(td,&n);
	for (int i=0;i<n;i++) {
		if(strcmp(vtab[i].chave,ch)==0) {
			if(strcmp(vtab[i].valor,v)!=0)
				printf("\nERRO - %s deveria ser classe '%s'\n",ch,v);
			break;
		}
	}
	free(vtab);
}

void teste_adiciona_comercio() {
	tabela_dispersao *comercio = tabela_nova(101,hash_djbm);
	tabela_dispersao *atividades = tabela_nova(47,hash_djbm);

	char nome[30], ativ[30];
	int res=0;
	strcpy(nome, "Casa comercial Desp1");
	strcpy(ativ, "Desporto");
	res = adiciona_comercio(nome, ativ, comercio, atividades);
	if (res==1)
		printf("\nCasa comercial adicionada com sucesso: %s\n", nome);
	else
		printf("\nERRO - Casa comercial nao adicionada: %s\n", nome);
	verifica_valor(comercio,nome,"top");

	strcpy(nome, "Casa comercial Desp2");
	strcpy(ativ, "Desporto");
	res = adiciona_comercio(nome, ativ, comercio, atividades);
	if (res==1)
		printf("\nCasa comercial adicionada com sucesso: %s\n", nome);
	else
		printf("\nERRO - Casa comercial no adicionada: %s\n", nome);

	strcpy(nome, "Casa comercial Ocul1");
	strcpy(ativ, "Oculista");
	res = adiciona_comercio(nome, ativ, comercio, atividades);
	if (res==1)
		printf("\nCasa comercial adicionada com sucesso: %s\n", nome);
	else
		printf("\nERRO - Casa comercial nao adicionada: %s\n", nome);
	verifica_valor(comercio,nome,"top");

	strcpy(nome, "Casa comercial Desp2");
	strcpy(ativ, "Desporto");
	res = adiciona_comercio(nome, ativ, comercio, atividades);
	if (res==1)
		printf("\nERRO - Casa comercial ja existente, adicionada erradamente: %s\n", nome);
	verifica_valor(comercio,nome,"normal");

	if (tabela_numelementos(atividades)==2)
		printf("\nTabela 'atividades_zona' tem 2 elementos - ok\n");
	else
		printf("\nERRO - Tabela 'atividades_zona' deveria ter 2 elementos\n");
	if (tabela_numelementos(comercio)==3)
		printf("\nTabela 'comercio_zona' tem 3 elementos - ok\n");
	else
		printf("\nERRO - Tabela 'comercio_zona' deveria ter 3 elementos\n");

	tabela_apaga(comercio);
	tabela_apaga(atividades);
}


heap* init_ruas_comercio()
{
	heap *h = heap_nova(20);
	if (!h)
		return NULL;
	heap_insere(h,"Rua do Amial_Paranhos",14);
	heap_insere(h,"Rua Dom Joao IV_Bonfim",20);
	heap_insere(h,"Rua Pinto Bessa_Bonfim",5);
	heap_insere(h,"Rua da Telheira_Paranhos",7);
	heap_insere(h,"Rua do Campo Lindo_Paranhos",13);
	heap_insere(h,"Rua Latino Coelho_Bonfim",12);
	heap_insere(h,"Rua do Vale Formoso_Paranhos",18);
	heap_insere(h,"Rua de Augusto Lessa_Paranhos",10);
	heap_insere(h,"Rua Sao Roque da Lameira_Campanha",17);
	return h;
}


void teste_rua_menos_comercio() {
	heap *ruas_porto = init_ruas_comercio();
	char *rua1;
	rua1 = remove_rua_menos_comercio(ruas_porto, "Paranhos");

	if (rua1 != NULL)
		printf("\nRua com menos comercio em Paranhos: %s\n", rua1);
	else
		printf("\nERRO: existem ruas com casas comerciais na freguesia de Paranhos\n");

	rua1 = remove_rua_menos_comercio(ruas_porto, "Bonfim");
	if (rua1 != NULL)
		printf("\nRua com menos comercio em Bonfim: %s\n", rua1);
	else
		printf("\nERRO: existem ruas com casas comerciais na freguesia de Bonfim\n");

	rua1 = remove_rua_menos_comercio(ruas_porto, "Se");
	if (rua1 == NULL)
		printf("\nNao existem ruas comerciais na freguesia da Se\n");
	else
		printf("\nERRO: nao existem ruas com casas comerciais na freguesia da Se\n");

	printf("\nRUAS:\n");
	heap_imprime(ruas_porto,1);
	heap_apaga(ruas_porto);
}



int main ()
{
	teste_adiciona_comercio();
	teste_rua_menos_comercio();
	return 1;
}
