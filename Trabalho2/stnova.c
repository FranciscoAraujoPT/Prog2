/*****************************************************************/
/*   Estrutura nova a implementar | PROG2 | MIEEC | 2019/20   */      
/*****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stnova.h"

#define RAIZ 		(1)
#define PAI(x) 		(x/2)
#define FILHO_ESQ(x) 	(x*2)
#define FILHO_DIR(x) 	(x*2+1)

void heap_imprime(estrutura *h, int indice)
{
  int i, nivel = 0;
  
  if (indice < h->tamanho)
  {
    i = indice;
    while(i > 1)
    {
      i = i/2;
      nivel++;
    }
    
    heap_imprime(h, indice*2);
    
    for(i = 0; i < 3 * nivel; i++)
      printf("     ");
    
    printf("%s (%d)\n",h->h_elementos[indice]->msg->remetente, h->h_elementos[indice]->prioridade);
    
    heap_imprime(h, indice*2+1);
  }
}

estrutura* st_nova()
{
    estrutura * h = (estrutura *) malloc(sizeof(estrutura));

	if(h == NULL){
		return NULL;
    }

	h->tamanho = 0;
	h->capacidade = 0;
	h->h_elementos = NULL;

	return h;
}


mensagem * cria_mensagem(elemento *elem)
{
    if(elem == NULL){
        return NULL;
    }

    char *text = (char*) malloc(sizeof(char)*strlen(elem->msg->texto)+1);

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

int maior_que(h_elemento * e1, h_elemento * e2)
{
	if (e1 == NULL || e2 == NULL)
	{
		return 0;
	}

	return e1->prioridade < e2->prioridade;
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

    h_elemento * aux;
	int i;

	/* se heap está cheia, realoca o espaço */
	if (st->tamanho >= st->capacidade){
        h_elemento ** aux = st->h_elementos;
        st->capacidade = st->tamanho+1;
		st->h_elementos = (h_elemento**) realloc(st->h_elementos, sizeof(h_elemento*)*(st->capacidade));
        
        if(st->h_elementos == NULL){
            st->h_elementos = aux;
            free(m);
            return -1;
        }
    }

    st->h_elementos[st->tamanho] = (h_elemento*) malloc(sizeof(h_elemento));

    if(st->h_elementos[st->tamanho] == NULL){// lembrar de modificar
        return -1;
    }

	st->h_elementos[st->tamanho]->msg = m;
    st->h_elementos[st->tamanho]->prioridade = -(msg[0]+msg[1]);
    i = st->tamanho++;

 	/* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
	while ((st->tamanho != RAIZ) && (maior_que(st->h_elementos[i], st->h_elementos[PAI(i)])))
	{
		aux = st->h_elementos[PAI(i)];
		st->h_elementos[PAI(i)] = st->h_elementos[i];
		st->h_elementos[i] = aux;
		i = PAI(i);
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

    heap_imprime(st, 1);
    return 0;

}

elemento *st_remove(estrutura *st,char *remetente)
{
    int i, filho_maior;
	h_elemento * aux;

    elemento *ret = (elemento*) malloc(sizeof(elemento));

	/* se heap estiver vazia, nao remove elemento */
	if (st == NULL || st->tamanho <= 0){
		return NULL;
    }

	ret->msg = st->h_elementos[RAIZ]->msg;
    ret->proximo = NULL;
	free(st->h_elementos[RAIZ]);

	/* coloca ultimo elemento da heap na raiz */
	st->h_elementos[RAIZ] = st->h_elementos[st->tamanho-1];
	st->h_elementos[st->tamanho-1] = NULL;
	st->tamanho--;

 	i = RAIZ;

	/* enquanto nao chegar 'a base da heap */
	while(FILHO_ESQ(i) <= st->tamanho)
	{
		filho_maior = FILHO_ESQ(i);

		/* verifica se existe filho 'a direita e se este e' mais prioritario do que 'a esquerda */
		if (FILHO_DIR(i) <= st->tamanho && maior_que(st->h_elementos[FILHO_DIR(i)], st->h_elementos[FILHO_ESQ(i)]))
			filho_maior = FILHO_DIR(i);

		/* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
		if (maior_que(st->h_elementos[filho_maior], st->h_elementos[i]))
		{
			aux = st->h_elementos[filho_maior];
			st->h_elementos[filho_maior] = st->h_elementos[i];
			st->h_elementos[i] = aux;
			i = filho_maior;
		}
		else
			break;
	}

    printf("%s\t%s\n", ret->msg->remetente, ret->msg->destinatario);
	return ret; 
}


int st_apaga(estrutura *st)
{
    int i;

	if(st == NULL){
		return -1;
    }

	for(i=RAIZ; i<st->tamanho; i++)
	{
        free(st->h_elementos[i]->msg->texto);
		free(st->h_elementos[i]->msg);
		free(st->h_elementos[i]);
		st->h_elementos[i]=NULL;
	}

	free(st->h_elementos);
	free(st);
    
    return 0;
}


