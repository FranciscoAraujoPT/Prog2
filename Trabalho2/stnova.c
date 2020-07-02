/*****************************************************************/
/*   Estrutura nova a implementar | PROG2 | MIEEC | 2019/20   */      
/*****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stnova.h"

void print_list(estrutura *lst){

    if(lst == NULL){
            printf("Linked list is empty\n");
    }
    estrutura *aux = lst;
    for(int i=0;i<lst->tamanho;i++){
        printf("%s %d\n", aux->inicio->msg->remetente, aux->inicio->prioridade);
        aux->inicio = aux->inicio->proximo;
    }
}

void elemento_apaga(l_elemento *elem);

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

l_elemento* novo_elemento(mensagem* m, int msg[2])
{
	l_elemento *item = (l_elemento *) malloc(sizeof(l_elemento));
	
    if(item == NULL){
		return NULL;
    }

    item->msg = m;
	if(item->msg == NULL)
	{
		free(item);
		return NULL;
	}

    item->prioridade = msg[0] + msg[1];
    item->proximo = NULL;
    item->anterior = NULL;

	return item;
}


int st_insere(estrutura *st, elemento *elem, int msg[2])
{
    
	if(st == NULL){
        return -1;
    }

    if(elem == NULL){
        return -1;
    }

    mensagem *m = cria_mensagem(elem);

    if(m == NULL){
        return -1;
    }

    l_elemento * curr = novo_elemento(m, msg);
    l_elemento * pos = st->inicio;

    if(curr == NULL){
        return -1;
    }

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
    int msg[2];

    for(int i=0;i<td->tamanho;i++){
        elem = td->elementos[i];
        while(elem != NULL)
        {   
            ligacao2(td, elem->msg->remetente, elem->msg->destinatario, msg);
            if(st_insere(st, elem, msg) == -1){
                return -1;
            }
            elem = elem->proximo;
        }
    }

    //print_list(st);
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

    int prioridade = 0, i = 0;
    elemento *aux = NULL;
    l_elemento *elem = st->inicio;

    while(elem != NULL)
    {
        if(strcmp(elem->msg->remetente, remetente) == 0){
            
            if(prioridade <= elem->prioridade){
                prioridade = elem->prioridade;
                printf("%s\n", elem->msg->remetente);
                char *text = (char*) malloc(sizeof(char)*(strlen(elem->msg->texto)+1));

                if(text == NULL){
                    return NULL;
                }

                mensagem *m = (mensagem*) malloc(sizeof(mensagem));

                if(m == NULL){
                    free(text);
                    return NULL;
                }
                
                aux = (elemento*) realloc(aux, sizeof(elemento)*(i+1));
                aux[i].msg = m;
                aux[i].msg->texto = text;
                strcpy(aux[i].msg->destinatario, elem->msg->destinatario);
                strcpy(aux[i].msg->remetente, elem->msg->remetente);
                strcpy(aux[i].msg->texto, elem->msg->texto);
                
                if(i != 0) {
                    aux[i-1].proximo = &aux[i];
                }
                st->tamanho--;
                i++;
            }
        }
        elem = elem->proximo;
    }

    aux[i].proximo = NULL;

    printf("\ni=%d\n", i);
    for(int j=0;j<i;j++)
    {  
        printf("%d: %s\t%s\n",j, aux[j].msg->remetente, aux[j].msg->destinatario);
    }

    return aux; 
}

 
void elemento_apaga(l_elemento *elem)
{
    if(elem == NULL){
        return;
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

    l_elemento *aux = st->inicio;
	
    while(aux != NULL)
	{
        elemento_apaga(aux);
        aux = aux->proximo;
	}

	free(st);
    
    return 0;
}


