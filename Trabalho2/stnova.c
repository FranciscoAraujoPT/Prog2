/*****************************************************************/
/*   Estrutura nova a implementar | PROG2 | MIEEC | 2019/20   */      
/*****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stnova.h"


mensagem * cria_mensagem(elemento *elem);
l_elemento* lista_elemento(estrutura *st, char* nomeU1);
int novo_elemento(estrutura *st, elemento *elem, tabela_dispersao *td);
void elemento_apaga(hash_elemento* elem, l_elemento *item);

estrutura* st_nova()
{
    estrutura * td = (estrutura *) malloc(sizeof(estrutura));

	if(td == NULL){
		return NULL;
    }

	td->tamanho = 0;
    td->elementos = NULL;
    td->hfunc = hash_krm;

	return td;
}

mensagem * clona_mensagem(elemento *elem)
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

elemento* clona_elemento(elemento *elem)
{
    if(elem == NULL){
        return NULL;
    }

    elemento *elem_clone = (elemento*) malloc(sizeof(elemento));

    if(elem_clone == NULL){
		return NULL;
    }


    elem_clone->msg = clona_mensagem(elem);

	if(elem_clone->msg == NULL)
	{
        free(elem_clone);
		return NULL;
	}

    return elem_clone;
}

l_elemento *clona_l_elemento(estrutura *st, elemento *elem, tabela_dispersao* td)
{
    if(st == NULL){
        return NULL;
    }

    if(elem == NULL){
        return NULL;
    }

    if(td == NULL){
        return NULL;
    }
    
    elemento *elem_clone = clona_elemento(elem);

    if(elem_clone == NULL){
		return NULL;
    }
    
    l_elemento *aux = lista_elemento(st, elem_clone->msg->remetente);
    
    if(aux != NULL){
        if((strcmp(aux->elem->msg->destinatario,elem_clone->msg->destinatario) == 0)){
            aux->elem->proximo = elem_clone;
            elem_clone->proximo = NULL;
            return NULL;
        }
    }
    
    l_elemento *item = (l_elemento *) malloc(sizeof(l_elemento));
	
    if(item == NULL){
        free(elem_clone);
		return NULL;
    }

    item->elem = elem_clone;
    item->elem->proximo = NULL;

    int msg[2];
    ligacao2(td, item->elem->msg->remetente, item->elem->msg->destinatario, msg);

    item->prioridade = msg[0] + msg[1];
    item->proximo = NULL;
    item->anterior = NULL;

    return item;
}

int st_insere_tabela(estrutura *st, elemento *elem, tabela_dispersao* td){

    if(st == NULL){
        return 0;
    }

    if(elem == NULL){
        return 0;
    }

    if(td == NULL){
        return 0;
    }

    /* calcula hash para a string a adicionar */
    int index = st->hfunc(elem->msg->remetente, td->tamanho);

    /* novo elemento, chave nao existe na lista */
    if(index >= st->tamanho){
        st->elementos = (hash_elemento **) realloc(st->elementos, sizeof(hash_elemento*)*(index+1));
        
        for(int i=st->tamanho;i<index+1;i++){
            hash_elemento* hash = (hash_elemento*) malloc(sizeof(hash_elemento));
            
            if(hash == NULL){
                return 0;
            }
            
            st->elementos[i] = hash;
            st->elementos[i]->inicio = NULL;
            st->elementos[i]->fim = NULL;
            st->elementos[i]->curr = NULL; 
            st->tamanho++;
        }

           
    }

    l_elemento *l_elem = clona_l_elemento(st,elem,td);

    if(l_elem == NULL){
        return 0;
    }

    if(st->elementos[index]->inicio == NULL){
        st->elementos[index]->inicio = l_elem;
        st->elementos[index]->fim = l_elem;
        st->elementos[index]->curr = l_elem;
    } else {
        st->elementos[index]->curr = l_elem;

        if(st_insere(st, l_elem->elem) == -1){
            return 0;
        }
    }

    return 1;
}

int st_insere(estrutura *st, elemento *elem)
{
    
	if(st == NULL){
        return -1;
    }

    if(elem == NULL){
        return -1;
    }

    int index = st->hfunc(elem->msg->remetente, st->tamanho);

    l_elemento * pos = st->elementos[index]->inicio, *curr = st->elementos[index]->curr;
    

    if(st->tamanho == 0){
        st->elementos[index]->inicio = st->elementos[index]->fim = curr;
    } else {
        if (curr->prioridade <= st->elementos[index]->fim->prioridade){
            curr->anterior = st->elementos[index]->fim;
		    st->elementos[index]->fim->proximo = curr;
		    st->elementos[index]->fim = curr;
        } else {
            if (curr->prioridade > st->elementos[index]->inicio->prioridade){
                curr->proximo = st->elementos[index]->inicio;
                st->elementos[index]->inicio->anterior = curr;
                st->elementos[index]->inicio = curr;
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
            if(st_insere_tabela(st, elem, td) == 0){
                return -1;
            }
            elem = elem->proximo;
        }
    }

    return 0;
}

l_elemento* lista_elemento(estrutura *st, char* nomeU1)
{
	if(st == NULL){
		return NULL;
    }

    if(nomeU1 == NULL){
		return NULL;
    }

    int index = st->hfunc(nomeU1, st->tamanho);
	l_elemento *curr = st->elementos[index]->inicio;

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

    end_t = clock();
    printf("\tTempo a remover: %.8f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    return NULL; 
}
 
void elemento_apaga(hash_elemento* elem, l_elemento *item)
{
    if(elem == NULL){
        return;
    }

    if(item == NULL){
        return;
    }

    if(item->anterior != NULL){
        item->anterior->proximo = item->proximo;
    } else {
        elem->inicio = item->proximo;
    }

    if(item->proximo != NULL){
        item->proximo->anterior = item->anterior;
    } else {
        elem->fim = item->anterior;
    }

    elemento* aux;

    while(item->elem != NULL)
    {
        aux = item->elem;
        item->elem = item->elem->proximo;

        free(aux->msg->texto);
        aux->msg->texto = NULL;
        free(aux->msg);
        aux->msg = NULL;
        free(aux);
        aux = NULL;
    }

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
    hash_elemento *elem;
    int tamanho = st->tamanho;

	for(int i=0;i<tamanho;i++)
    {
        elem = st->elementos[i];
        while(elem->inicio)
        {
            aux = elem->inicio;
            elem->inicio = elem->inicio->proximo;
            elemento_apaga(elem, aux);
            st->tamanho--;
        }
        free(st->elementos[i]);
        st->elementos[i] = NULL;
    }

    free(st->elementos);
	free(st);
    
    return 0;
}
