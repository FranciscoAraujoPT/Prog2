/*****************************************************************/
/*   Grafo direcionado | PROG2 | MIEEC | 2019/20        */      
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

void imprime_grafo(no_grafo **g)
{
    if(g == NULL){
        return;
    }

    int i = 0;

    while(g)
    {
        printf("%d: %s\n", i, g[i]->nome_user);
        i++;
    }
}

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

    if(g->tamanho > 0){
        for (int i=0;i<g->tamanho;i++)
        {
            while(g->nos[i]->tamanho > j)
            {
                ligacao* aux = g->nos[i]->ligacoes[j];
                free(aux);
                aux = NULL;
                j++;
            }
            j=0;
            ligacao ** aux2 = g->nos[i]->ligacoes;
            char *aux3 = g->nos[i]->nome_user;
            no_grafo *aux4 = g->nos[i];
                free(aux2);
                aux2 = NULL;
                free(aux3);
                aux3 = NULL;
                free(aux4);
                aux4 = NULL;
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
        if(strcmp(g->nos[i]->nome_user, user) == 0){
            return NULL;
        }
        i++;
    }
    
    if(g->tamanho > 0){
        g->nos = (no_grafo**) realloc(g->nos, sizeof(no_grafo)*i);

        if(g->nos == NULL){
            return NULL;
        }
    }

    no_grafo *no = (no_grafo*) malloc(sizeof(no_grafo));

    if(no == NULL){
        return NULL;
    }

    char *no_user = (char*) malloc(sizeof(char)*(strlen(user)+1));

    if(no_user == NULL){
        free(no);
        return NULL;
    }

    ligacao **lig = (ligacao**) malloc(sizeof(ligacao));

    if(lig == NULL){
        free(no);
        free(no_user);
        return NULL;
    }

    strcpy(no_user, user);
    no->nome_user=no_user;
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
    
    if(origem->tamanho > 0){
        origem->ligacoes = (ligacao**) realloc(origem->ligacoes, sizeof(ligacao)*i);//Porque que preciso disto??

        if(origem->ligacoes == NULL){
            return -1;
        }
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

    while (g->tamanho > i)
    {
        if(strcmp(g->nos[i]->nome_user, nomeU) == 0){
            return g->nos[i];
        }
        i++;
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
    int i = 0, j = 0, msg[2];

    while(td->tamanho > i){
        elem = td->elementos[i];
        while(elem)
        {   
            no_insere(g, elem->msg->remetente);
            no_insere(g, elem->msg->destinatario);
            elem = elem->proximo;
        }
        i++;
    }

    i=0;
    while(g->tamanho > i)
    {
        while(g->tamanho > j)
        {   
            if(j == i){
                j++;
                continue;
            }

            ligacao2(td, g->nos[i]->nome_user, g->nos[j]->nome_user, msg);

            if(msg[0]>0){
                cria_ligacao(g->nos[i], g->nos[j], msg[0]);
            }

            if(msg[1]>0){
                cria_ligacao(g->nos[j], g->nos[i], msg[1]);
            }
            j++;
        }
        j=0;
        i++;
    }

    return g;
}



no_grafo **lista_amigos(grafo *g, char *nomeU, int *n)
{
    if(g == NULL){
        return NULL;
    }

    if(nomeU == NULL){
        return NULL;
    }

    if(n == NULL){
        return NULL;
    }

    no_grafo ** amigos = (no_grafo**) malloc(sizeof(no_grafo));
    no_grafo * amigo;
    int i = 0, j = 0, amigo1 = 0;
    *n = 0;

    while (g->tamanho > i)
    {
        if(strcmp(g->nos[i]->nome_user, nomeU) == 0){
            while(g->nos[i]->tamanho > j)
            {
                if(g->nos[i]->ligacoes[j]->peso_ligacao >= 4){
                    amigo1 = 1;
                    amigo = g->nos[i]->ligacoes[j]->destino;
                }
                j++;
            }
            
            if(amigo1 == 1){
                j = 0;
                while(amigo->tamanho > j)
                {
                    if(strcmp(amigo->ligacoes[j]->destino->nome_user, nomeU) == 0){
                        if(amigo->ligacoes[j]->peso_ligacao >= 4){
                            if(*n > 0){
                                amigos = (no_grafo **) realloc(amigos, sizeof(no_grafo)*(*n));
                            }
                            amigos[*n] = amigo;
                            (*n)++;
                        }
                    }
                    j++;
                }
            }

            if((*n) > 0){
                return amigos;
            } else {
                free(amigos);
                return NULL;
            }
        }
       i++;
    }

    free(amigos);
    return NULL;
}



no_grafo ** identifica_ciclo(grafo *g, char *nomeU, int M, int *n)
{
    
    return NULL;
}