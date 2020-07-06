/*****************************************************************/
/*         Tabela de Dispersao | PROG2 | MIEEC | 2019/20         */
/*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabdispersao.h"

tabela_dispersao* tabela_nova(int tamanho, hash_func *hfunc)
{
     /* aloca memoria para a estrutura tabela_dispersao */
    if (hfunc == NULL)
        return NULL;

    tabela_dispersao *t = (tabela_dispersao*) malloc(sizeof (tabela_dispersao));
    if (t == NULL)
        return NULL;

    /* aloca memoria para os elementos */
    t->elementos = (elemento **) calloc(tamanho, sizeof (elemento*));
    if (t->elementos == NULL) {
        free(t);
        return NULL;
    }

    t->tamanho = tamanho;
    t->hfunc = hfunc;

    return t;
}

void tabela_apaga(tabela_dispersao *td)
{
    

    if (td == NULL) return;

    /* esvazia tabela*/
    tabela_esvazia(td);

    /* liberta vector e estrutura */
    free(td->elementos);
    free(td);;
}

int tabela_adiciona(tabela_dispersao *td, const char *remet,const char *dest, const char *texto)  //valor = texto // dest //remet=chave
{
    int index;
    elemento * elem, *elemaux;

    if (!td || !texto|| !dest || !remet) return TABDISPERSAO_ERRO;

    /* aloca memoria para o elemento */
        elem = (elemento*) malloc(sizeof (elemento));
        if (elem == NULL)
            return TABDISPERSAO_ERRO;

        /* aloca memoria para o mensagem*/
        elem->msg = (mensagem*) malloc(sizeof (mensagem));
        if (elem->msg == NULL)
        {   
            free(elem);
            return TABDISPERSAO_ERRO;
        }
        /* aloca memoria para o texto da mensagem*/
         elem->msg->texto = malloc(strlen(texto)+1);
        if (elem->msg->texto == NULL)
        {   
            free(elem->msg);
            free(elem);
            return TABDISPERSAO_ERRO;
        }
        /*copia chave e valor */
        
        strcpy(elem->msg->remetente, remet);
        strcpy(elem->msg->destinatario, dest);
        strcpy(elem->msg->texto,texto );


    /* calcula hash para a string a adicionar */
    index = td->hfunc(remet, td->tamanho);

    /* verifica se chave ja' existe na lista */
    elemaux = td->elementos[index];
   

    if (elemaux == NULL)
    {
        /* novo elemento, chave nao existe na lista */

        /* insere no inicio da lista */
        elem->proximo = NULL;
        td->elementos[index] = elem;
    } else {
      
        elem->proximo = elemaux;
        td->elementos[index] = elem;
       
    }

    return TABDISPERSAO_OK;
}


int tabela_existe(tabela_dispersao *td, const char *remetente)
{
    if(td == NULL){
        return -1;
    }

    if(remetente == NULL){
        return -1;
    }

    int nMsg = 0, indice = td->hfunc(remetente, td->tamanho);
    elemento *elem;

    elem = td->elementos[indice];
    while(elem != NULL)
    {
        if(strcmp(elem->msg->remetente, remetente) == 0){
            nMsg++;
        }
        elem = elem->proximo;
    }
    
    return nMsg;
}

mensagem **tabela_listagem(tabela_dispersao *td, const char *remetente)
{
    if(td == NULL){
        return NULL;
    }

    if (remetente == NULL){
        return NULL;
    }

    mensagem **msg = (mensagem**) malloc(sizeof(mensagem) * (tabela_existe(td, remetente)) + sizeof(mensagem*));
    
    if(msg == NULL){
        return NULL;
    }
     
    int j=0, indice = td->hfunc(remetente, td->tamanho);
    elemento *elem;

    elem = td->elementos[indice];
    while(elem != NULL)
    {
        if(strcmp(elem->msg->remetente, remetente) == 0){
            msg[j] = elem->msg;
            j++;
        }
        elem = elem->proximo;
    }

    msg[j] = NULL; //garante que a primeira, em caso de inexistência de remetente, ou a ultima posição é NULL.
    
    if(j == 0){
        return msg;
    }

    return msg;
}

int tabela_esvazia(tabela_dispersao *td)
{
     int i;
    elemento * elem, * aux;

    if (!td) return TABDISPERSAO_ERRO;

    /* para cada entrada na tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        /* apaga todos os elementos da entrada */
        elem = td->elementos[i];
        while(elem != NULL)
        {
            aux = elem->proximo;
            free (elem->msg->texto);
            free(elem->msg);
            free(elem);
            elem = aux;
        }
        td->elementos[i] = NULL;
    }
    return TABDISPERSAO_OK;
}

unsigned long hash_krm(const char* chave, int tamanho)
{
	int c, t = strlen(chave);
    unsigned long hash = 7;
    
    for(c = 0; c < t; c++)
    {
        hash += (int) chave[c];
    
    }

    return hash % tamanho;

    return 0;
}

tabela_dispersao* tabela_carrega(char *ficheiro,int tamanho)
{
    FILE *f = fopen(ficheiro, "r");
    if(f == NULL) 
        return NULL;
    
    tabela_dispersao *td = tabela_nova(tamanho,hash_krm);
    if(td == NULL)
    {
        
        fclose(f);
        return NULL;
    }

    int count=0;
    char str_aux[1024] = {};
    char remetente[TAMANHO_CHAVE] = {0};
    char destinatario[TAMANHO_CHAVE] = {0};
    char *token;
   
    

    while((fgets(str_aux, 1024, f)) != NULL)
    {
        
        str_aux[strlen(str_aux)-1] = '\0';

        count++;  
        token = strtok(str_aux, "\\");
        
        strcpy(remetente,token);
        token = strtok(NULL, "\\");
    
        strcpy(destinatario,token);
    
        token = strtok(NULL, "");
    
        if (token==NULL) 
            token=" ";
        
        if (tabela_adiciona(td, remetente,destinatario,token)==-1)
        {
            tabela_apaga(td);
            fclose(f);
            return NULL;
        }
           
  
    }
    
    fclose(f);
    return td; 
}

void ligacao2(tabela_dispersao *td, char *nomeU1, char *nomeU2, int totMsg[2])
{
    if(td == NULL){
        return;
    }

    if(nomeU1 == NULL){
        return;
    }

    if(nomeU2 == NULL){
        return;
    }

    if(totMsg == NULL){
        return;
    }

    totMsg[0] = totMsg[1] = 0;
    int existeU1 = 0, existeU2 = 0;

    int indice = td->hfunc(nomeU1, td->tamanho);
    elemento *elem = td->elementos[indice];
    

    while(elem != NULL)
    {
        if(strcmp(elem->msg->remetente, nomeU1) == 0){
            existeU1 = 1;
            if(strcmp(elem->msg->destinatario, nomeU2) == 0){
                totMsg[0]++;                
            }
        }
        elem = elem->proximo;
    }
    
    indice = td->hfunc(nomeU2, td->tamanho);
    elem = td->elementos[indice];

    while(elem != NULL)
    {
        if (strcmp(elem->msg->remetente, nomeU2) == 0){
            existeU2 = 1;
            if(strcmp(elem->msg->destinatario, nomeU1) == 0){
                totMsg[1]++;
            }
        }
        elem = elem->proximo;
    } 

    if(existeU1 == 0){
        totMsg[0] = -1;
    }

    if (existeU2 == 0){
        totMsg[1] = -1;
    }
}
