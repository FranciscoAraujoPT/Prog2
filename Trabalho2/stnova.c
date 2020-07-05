/*****************************************************************/
/*   Estrutura nova a implementar | PROG2 | MIEEC | 2019/20   */      
/*****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stnova.h"


mensagem * cria_mensagem(elemento *elem);
mensagem * cria_mensagem2 (l_elemento *elem);
l_elemento* lista_elemento(estrutura *st, char* nomeU1);
int novo_elemento(estrutura *st, elemento *elem, tabela_dispersao *td);
void elemento_apaga(estrutura *st, l_elemento *elem);

estrutura* st_nova()
{
    estrutura * lst = (estrutura *) malloc(sizeof(estrutura));

	if(lst == NULL){
		return NULL;
    }

	lst->tamanho = 0;
    lst->inicio = NULL;
    lst->fim = NULL;

	return lst;
}

mensagem * cria_mensagem(elemento *elem)
{
    if(elem == NULL){
        return NULL;
    }

    char *text = (char*) malloc(sizeof(char)*(strlen(elem->msg->texto)+1));

    if(text == NULL){
        return NULL;
    }

    mensagem *m = (mensagem*) malloc(sizeof(mensagem));

    if(m == NULL){
        free(text);
        return NULL;
    }
    
    strcpy(m->destinatario, elem->msg->destinatario);
    strcpy(m->remetente, elem->msg->remetente);
    strcpy(text, elem->msg->texto);
    m->texto = text;

    return m;
}

int novo_elemento(estrutura *st, elemento *elem, tabela_dispersao *td)
{
    if(st == NULL){
        return -1;
    }

    if(elem == NULL){
        return -1;
    }

    if(td == NULL){
        return -1;
    }

	l_elemento *item = (l_elemento *) malloc(sizeof(l_elemento));
	
    if(item == NULL){
		return -1;
    }

    elemento *elem1 = (elemento*) malloc(sizeof(elemento));

    if(elem == NULL){
        free(item);
		return -1;
    }

    item->elem = elem1;

    item->elem->msg = cria_mensagem(elem);

	if(item->elem->msg == NULL)
	{
		free(item);
        free(elem);
		return -1;
	}

    l_elemento *aux = lista_elemento(st, item->elem->msg->remetente);
    
    if(aux != NULL){
        if((strcmp(aux->elem->msg->destinatario,item->elem->msg->destinatario) == 0)){
            aux->elem->proximo = item->elem;
            item->tamanho_elem++;
            return 0;
        }
    }

    item->elem->proximo = NULL;
    item->tamanho_elem = 0;

    int msg[2];
    ligacao2(td, item->elem->msg->remetente, item->elem->msg->destinatario, msg);

    item->prioridade = msg[0] + msg[1];
    item->proximo = NULL;
    item->anterior = NULL;
    
    st->curr = item;

    if(st_insere(st,elem) == -1){
        elemento_apaga(st, item);
        return-1;
    }

	return 0;
}

int st_insere(estrutura *st, elemento *elem)
{
    
	if(st == NULL){
        return -1;
    }

    if(elem == NULL){
        return -1;
    }

    l_elemento * pos = st->inicio, *curr = st->curr;
    

    if(st->tamanho == 0){
        st->inicio = st->fim = curr;
    } else {
        if (curr->prioridade <= st->fim->prioridade){
            curr->anterior = st->fim;
		    st->fim->proximo = curr;
		    st->fim = curr;
        } else {
            if (curr->prioridade > st->inicio->prioridade){
                curr->proximo = st->inicio;
                st->inicio->anterior = curr;
                st->inicio = curr;
            } else {
                while(curr->prioridade <= pos->prioridade)
                {
                    pos = pos->proximo;
                }
                curr->anterior = pos->anterior;
                curr->proximo = pos;
                pos->anterior->proximo = curr;
                pos->anterior = curr;
            }
        }
    }
    st->tamanho++;

    return 0;
}

int st_importa_tabela(estrutura *st, tabela_dispersao *td)
{

    if(td == NULL){
        return -1;
    }

    if(st == NULL){
        return -1;
    }

    elemento *elem;

    for(int i=0;i<td->tamanho;i++){
        elem = td->elementos[i];
        while(elem != NULL)
        {   
            if(novo_elemento(st, elem, td) == -1){
                return -1;
            }
            elem = elem->proximo;
        }
    }

    return 0;
}

mensagem * cria_mensagem2 (l_elemento *item)
{
    if(item == NULL){
        return NULL;
    }

    char *text = (char*) malloc(sizeof(char)*(strlen(item->elem->msg->texto)+1));

    if(text == NULL){
        return NULL;
    }

    mensagem *m = (mensagem*) malloc(sizeof(mensagem));

    if(m == NULL){
        free(text);
        return NULL;
    }
    
    strcpy(m->destinatario, item->elem->msg->destinatario);
    strcpy(m->remetente, item->elem->msg->remetente);
    strcpy(text, item->elem->msg->texto);
    m->texto = text;

    return m;
}

l_elemento* lista_elemento(estrutura *st, char* nomeU1)
{
	if (st == NULL){
		return NULL;
    }

    if (nomeU1 == NULL){
		return NULL;
    }

	l_elemento *curr = st->inicio;

	while(curr != NULL)
    {   
        if(strcmp(curr->elem->msg->remetente, nomeU1) == 0){
            return curr;
        }
		curr = curr->proximo;
    }

	return NULL;
}

elemento *st_remove(estrutura *st,char *remetente)
{
    clock_t start_t, end_t;
    start_t = clock(); 

    if(remetente == NULL){
        return NULL;
    }

    if(st == NULL){
        return NULL;
    }

	/* se a lista estiver vazia, nao remove elemento */
	if (st->tamanho <= 0){
		return NULL;
    }

    l_elemento *item, *aux;
    item = lista_elemento(st, remetente);

    if(item == NULL){
        return NULL;
    }

    elemento *inicio = (elemento*) malloc(sizeof(elemento)*(item->tamanho_elem));
    //elemento *aux2 =item->elem, *aux3 = inicio;
    
    if(inicio == NULL){
        return NULL;
    }

    aux = item->proximo;
    inicio = item->elem;
    //elemento_apaga(st, item);
    item = aux;

    end_t = clock();
    printf("\tTempo a remover: %.8f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    return inicio; 
}
 
void elemento_apaga(estrutura *st, l_elemento *item)
{
    if(st == NULL){
        return;
    }

    if(item == NULL){
        return;
    }

    st->tamanho--;

    if(item->anterior != NULL){
		item->anterior->proximo = item->proximo;
    } else {
		st->inicio = item->proximo;
    }

    if(item->proximo != NULL){
		item->proximo->anterior = item->anterior;
    } else {
		st->fim = item->anterior;
    }

    free(item->elem->msg->texto);
    item->elem->msg->texto = NULL;
    free(item->elem->msg);
    item->elem->msg = NULL;
    free(item->elem);
    item->elem = NULL;
    free(item);
}

int st_apaga(estrutura *st)
{

	if(st == NULL){
		return -1;
    }

    if(st->tamanho <= 0){
		return -1;
    }

    l_elemento *aux;
	
    while(st->inicio)
	{
		aux = st->inicio;
		st->inicio = st->inicio->proximo;
		elemento_apaga(st, aux);
	}

	free(st);
    
    return 0;
}
