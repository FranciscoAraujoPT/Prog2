/*****************************************************************/
/*   Estrutura nova a implementar | PROG2 | MIEEC | 2019/20   */      
/*****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stnova.h"


mensagem * cria_mensagem(elemento *elem);
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

    item->msg = cria_mensagem(elem);

	if(item->msg == NULL)
	{
		free(item);
		return -1;
	}

    int msg[2];
    ligacao2(td, item->msg->remetente, item->msg->destinatario, msg);

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

elemento *st_remove(estrutura *st,char *remetente)
{
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

    int prioridade = -1, i = 0;
    elemento *inicio = NULL, *aux = NULL, *aux2;
    l_elemento *elem = st->inicio, *aux3;

    while(elem != NULL)
    {
        if(strcmp(elem->msg->remetente, remetente) == 0){
            if(prioridade > elem->prioridade){
                break;
            }
            if(prioridade <= elem->prioridade){
                char *text = (char*) malloc(sizeof(char)*(strlen(elem->msg->texto)+1));

                if(text == NULL){
                    return NULL;
                }

                mensagem *m = (mensagem*) malloc(sizeof(mensagem));

                if(m == NULL){
                    free(text);
                    return NULL;
                }

                aux = (elemento*) malloc(sizeof(elemento)*(i+1));
                aux->msg = m;
                aux->msg->texto = text;
                
                strcpy(aux->msg->destinatario, elem->msg->destinatario);
                strcpy(aux->msg->remetente, elem->msg->remetente);
                strcpy(aux->msg->texto, elem->msg->texto);
                
                if(i == 0){
                    prioridade = elem->prioridade;
                    inicio = aux;
                } else {
                    aux2->proximo = aux;
                }
                
                aux2 = aux;
                aux = aux->proximo;
                i++;

                aux3 = elem->proximo;
                elemento_apaga(st, elem);
                elem = aux3;
            }
        } else {
            elem = elem->proximo;
        }
    }

    aux2->proximo= NULL;

    return inicio; 
}
 
void elemento_apaga(estrutura *st, l_elemento *elem)
{
    if(st == NULL){
        return;
    }

    if(elem == NULL){
        return;
    }

    st->tamanho--;

    if(elem->anterior != NULL){
		elem->anterior->proximo = elem->proximo;
    } else {
		st->inicio = elem->proximo;
    }

    if(elem->proximo != NULL){
		elem->proximo->anterior = elem->anterior;
    } else {
		st->fim = elem->anterior;
    }

    free(elem->msg->texto);
    elem->msg->texto = NULL;
    free(elem->msg);
    elem->msg = NULL;
    free(elem);
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
