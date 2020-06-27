/*****************************************************************/
/*   Grafo direcionado | PROG2 | MIEEC | 2019/20        */      
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"


grafo* grafo_novo()
{
    grafo* g = (grafo*)malloc(sizeof(grafo));
    
    if(g == NULL){
        return NULL;
    }

    g->nos = (no_grafo**) malloc(sizeof(no_grafo));
    
    if(g->nos == NULL){
        free(g);
        return NULL;
    }

    g->tamanho = 0;

    return g;
}


void grafo_apaga(grafo* g)
{
    if(g == NULL){
        return;
    }

    int j = 0;

    if(g->nos != NULL){
        for (int i=0;i<g->tamanho;i++)
        {
            while(g->nos[i]->ligacoes[j])
            {
                ligacao* aux = g->nos[i]->ligacoes[j];
                j++;
                free(aux);
            }
            ligacao ** aux2 = g->nos[i]->ligacoes;
            char *aux3 = g->nos[i]->nome_user;
            no_grafo *aux4 = g->nos[i];
                free(aux2);
                free(aux3);
                free(aux4);
        }
        free(g->nos);
    }
    free(g);
}


no_grafo * no_insere(grafo *g, char *user)
{

    if(g == NULL){
        return NULL;
    }

    if(user == NULL){
        return NULL;
    }

    int i = 0;

    while (g->tamanho > i)
    {
        printf("2:%s\t%s\n",g->nos[i]->nome_user, user);
        if(strcmp(g->nos[i]->nome_user, user) == 0){
            return NULL;
        }
        i++;
    }

    no_grafo *no = (no_grafo*) malloc(sizeof(no_grafo));
    
    if(no == NULL){
        return NULL;
    }

    char *no_user = (char*) malloc(sizeof(char)*(strlen(user)+1));
    ligacao **lig = (ligacao**) malloc(sizeof(ligacao));

    strcpy(no_user, user);
    no->nome_user=no_user;
    //printf("\nposição= %d\n", i);
    //printf("3:%s\t%s\n",no->nome_user, user);
    no->tamanho = 0;
    no->ligacoes = lig;
    g->nos[i] = no;
    g->tamanho++;

    return g->nos[i];
}


int  cria_ligacao(no_grafo *origem, no_grafo *destino, int peso)
{
    if(origem == NULL){
        return -1;
    }

    if(destino == NULL){
        return -1;
    }

    if(peso < 0){
        return -1;
    }

    
    int i = 0;

    while(origem->tamanho > i)
    {
        if(strcmp(origem->ligacoes[i]->destino->nome_user, destino->nome_user) == 0){
            return -1;
        }
        i++;
    }
    
    ligacao *lig = (ligacao*) malloc(sizeof(ligacao));

    if(lig == NULL){
        return -1;
    }

    lig->destino = destino;
    lig->peso_ligacao = peso; 
    origem->ligacoes[i] = lig;
    origem->tamanho++;

    return 0;
}


no_grafo * encontra_no(grafo *g, char *nomeU)
{
    
    if(g == NULL){
        return NULL;
    }

    if(nomeU == NULL){
        return NULL;
    }

    int i = 0;

    if(g->tamanho == 0){
        return NULL;
    } else {
        while (g->tamanho > i)
        {
            if(strcmp(g->nos[i]->nome_user, nomeU) == 0){
                return g->nos[i];
            }
            i++;
        }
    }

    return NULL;
}




grafo * criaGrafo(tabela_dispersao *td)
{
    if(td == NULL){
        return NULL;
    }

    grafo* g = grafo_novo();

    if(g == NULL){
        return NULL;
    }

    elemento *elem;
    no_grafo *origem, *dest;
    int i = 0, msg[2];
    while(td->tamanho > i){
        elem = td->elementos[i];
        //printf("i=%d\n", i);
        while(elem)
        {   
            origem = no_insere(g, elem->msg->remetente);
            dest = no_insere(g, elem->msg->destinatario);
            
            if(origem != NULL && dest != NULL){
                ligacao2(td, origem->nome_user, dest->nome_user, msg); // verificar
                //printf("msg1 = %d\n", msg[0]);
                if(msg[0]>0){
                    cria_ligacao(origem, dest, msg[0]);
                }
                //printf("msg2 = %d\n", msg[1]);
                if(msg[1]>0){
                    cria_ligacao(dest, origem, msg[1]);
                }
            }

            elem = elem->proximo;
            //printf("================================\n");
        }
        //printf("%s\n", g->nos[0]->nome_user);
        i++;
    }
    printf("\nFIM\n");
    return g;
}



no_grafo **lista_amigos(grafo *g, char *nomeU, int *n)
{
   return NULL;
}



no_grafo ** identifica_ciclo(grafo *g, char *nomeU, int M, int *n)
{
    
    return NULL;

  
}