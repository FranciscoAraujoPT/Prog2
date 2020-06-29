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

    g->nos = NULL;
    g->tamanho = 0;

    return g;
}

void no_apaga(no_grafo *no)
{
    if(no == NULL){
        return;
    }

    if(no->tamanho > 0){
        
        for(int i=0;i<no->tamanho;i++)
        {
            free(no->ligacoes[i]);
            no->ligacoes[i] = NULL;
        }
    
        free(no->ligacoes);
        no->ligacoes = NULL;
    }

    free(no->nome_user);
    no->nome_user = NULL;
    free(no);
    no = NULL;

}

void grafo_apaga(grafo* g)
{
    if(g == NULL){
        return;
    }

    if(g->tamanho > 0){
        for (int i=0;i<g->tamanho;i++)
        {
            no_apaga(g->nos[i]);
        }
        free(g->nos);
        g->nos = NULL;
    }
    free(g);
    g = NULL;
}


no_grafo * no_insere(grafo *g, char *user)
{

    if(g == NULL){
        return NULL;
    }

    if(user == NULL){
        return NULL;
    }

    int i;

    for(i=0;i<g->tamanho;i++)
    {
        if(strcmp(g->nos[i]->nome_user, user) == 0){
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

    g->nos = (no_grafo**) realloc(g->nos, sizeof(no_grafo*)*(g->tamanho+1));

    if(g->nos == NULL){
        free(no);
        free(no_user);
        return NULL;
    }

    strcpy(no_user, user);
    no->nome_user=no_user;
    no->tamanho = 0;
    no->ligacoes = NULL;
    g->nos[g->tamanho] = no;
    g->tamanho++;    

    return g->nos[g->tamanho-1];
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

    origem->ligacoes = (ligacao**) realloc(origem->ligacoes, sizeof(ligacao*)*(origem->tamanho+1));

    if(origem->ligacoes == NULL){
        free(lig);
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

no_grafo * ajuda_identifica_ciclo(no_grafo **ciclo, int *n)
{
    int i = 0;

    while(ciclo[*n]->tamanho >= i)
    {
        ciclo[*n+1] = ciclo[*n]->ligacoes[i]->destino;
        printf("x: %s\t", ciclo[0]->nome_user);
        if(ciclo[*n]->ligacoes[i]->destino == ciclo[0]){
            printf("3:%s\t", ciclo[*n]->nome_user);
            return ciclo[*n];
        }
        
        i++;
        
        if(ciclo[*n]->tamanho == i){
            (*n)++;
            for(int j=0;j<ciclo[*n]->tamanho;j++)
            {
                ciclo[*n+1] = ciclo[*n]->ligacoes[j]->destino;
                if(ajuda_identifica_ciclo(ciclo, n) != NULL){
                    printf("2:%s\t", ciclo[*n]->nome_user);
                    break;
                }

            }
            (*n)--;
            i = 0;
        }
    }

    return NULL;
}


no_grafo ** identifica_ciclo(grafo *g, char *nomeU, int M, int *n)
{
    // if(g == NULL){
    //     return NULL;
    // }

    // if(nomeU == NULL){
    //     return NULL;
    // }

    // if(n == NULL){
    //     return NULL;
    // }

    // if(M < 3){
    //     return NULL;
    // }

    // no_grafo ** ciclo = (no_grafo**) malloc(sizeof(no_grafo)*M);

    // if (ciclo == NULL){
    //     return NULL;
    // }
    

    // int i = 0;
    // *n = 1;
    // ciclo[0] = encontra_no(g, nomeU);
    // printf("0:%s\t", ciclo[0]->nome_user);

    // while(ciclo[0]->tamanho > i)
    // {
    //     ciclo[1] = ciclo[0]->ligacoes[i]->destino;
    //     printf("1:%s\t", ciclo[1]->nome_user);

    //     if(ajuda_identifica_ciclo(ciclo, n) != NULL){
    //         break;
    //     }

    //     i++;
    // }

    return NULL;
}