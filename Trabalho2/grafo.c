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
}


no_grafo * cria_no(char *user)
{
    if(user == NULL){
        return NULL;
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

    strcpy(no_user, user);
    no->nome_user=no_user;
    no->tamanho = 0;
    no->ligacoes = NULL;

    return no;
}


no_grafo * no_insere(grafo *g, char *user)
{

    if(g == NULL){
        return NULL;
    }

    if(user == NULL){
        return NULL;
    }

    for(int i=0;i<g->tamanho;i++)
    {
        if(strcmp(g->nos[i]->nome_user, user) == 0){
            return NULL;
        }
    }
    
    no_grafo **aux = g->nos;
    g->nos = (no_grafo**) realloc(g->nos, sizeof(no_grafo*)*(g->tamanho+1));

    if(g->nos == NULL){
        g->nos = aux; //Garante que a memoria do g->nos não é perdida mesmo que o realloc não tenha tido sucesso
        return NULL;
    }
    
    no_grafo* no = cria_no(user);

    if(no == NULL){
        return NULL;
    }

    g->nos[g->tamanho] = no;
    g->tamanho++;    

    return no;
}

ligacao * cria_lig(no_grafo *destino,int peso)
{
    if(destino == NULL){
        return NULL;
    }

    if(peso < 0){
        return NULL;
    }

    ligacao *lig = (ligacao*) malloc(sizeof(ligacao));
    
    if(lig == NULL){
        return NULL;
    }

    lig->destino = destino;
    lig->peso_ligacao = peso;

    return lig;
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

    for(int i=0;i<origem->tamanho;i++)
    {
        if(strcmp(origem->ligacoes[i]->destino->nome_user, destino->nome_user) == 0){
            return -1;
        }
    }

    ligacao **aux = origem->ligacoes;
    origem->ligacoes = (ligacao**) realloc(origem->ligacoes, sizeof(ligacao*)*(origem->tamanho+1));

    if(origem->ligacoes == NULL){
        origem->ligacoes = aux; ////Garante que a memoria do origem->ligacoes não é perdida mesmo que o realloc não tenha tido sucesso
        return -1;
    }
    
    ligacao *lig = cria_lig(destino, peso);

    if(lig == NULL){
        return -1;
    }

    origem->ligacoes[origem->tamanho] = lig;
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

    for(int i=0;i<g->tamanho;i++)
    {
        if(strcmp(g->nos[i]->nome_user, nomeU) == 0){
            return g->nos[i];
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
    int i = 0, j = 0, msg[2];

    for(i=0;i<td->tamanho;i++){
        elem = td->elementos[i];
        while(elem != NULL)
        {   
            no_insere(g, elem->msg->remetente);
            no_insere(g, elem->msg->destinatario);
            elem = elem->proximo;
        }
    }

    i = 0;

    for(i=0;i<g->tamanho;i++)
    {
        for(j=0;j<g->tamanho;j++)
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
        }
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

    no_grafo ** amigos = (no_grafo**) malloc(sizeof(no_grafo*));

    if(amigos == NULL){
        return NULL;
    }

    no_grafo * amigo;
    int i = 0, j = 0, amigo1 = 0;
    *n = 0;

    for(i=0;i<g->tamanho;i++)
    {
        if(strcmp(g->nos[i]->nome_user, nomeU) == 0){
            for(j=0;j<g->nos[i]->tamanho;j++)
            {
                if(g->nos[i]->ligacoes[j]->peso_ligacao >= 4){
                    amigo1 = 1;
                    amigo = g->nos[i]->ligacoes[j]->destino;
                }
            }
            
            if(amigo1 == 1){
                for(j=0;j<amigo->tamanho;j++)
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
                }
            }
            if((*n) > 0){
                return amigos;
            } else {
                free(amigos);
                return NULL;
            }
        }
    }

    free(amigos);
    return NULL;
}

no_grafo ** ajuda_identifica_ciclo(no_grafo **ciclo, int *n, int M)
{
    
    if(*n != 1){
        for(int j=0;j<ciclo[*n]->tamanho;j++){
            if(ciclo[*n]->ligacoes[j]->destino == ciclo[0]){
                (*n)++;
                printf("3: %s\n", ciclo[j]->nome_user);
                return ciclo;
            }
        }
    }

    int i = 0;
    while(*n < M)
    {
        if(ciclo[*n]->ligacoes[i] != NULL){
            ciclo[*n+1] = ciclo[*n]->ligacoes[i]->destino;
            printf("%d: %s\n",i, ciclo[i]->nome_user);
            i++;
            (*n)++;
            if(ajuda_identifica_ciclo(ciclo, n, M) != NULL){
                printf("olaa\n");
                return ciclo;
            }
            (*n)--;
        } else {
            return NULL;
        }
    }

    return NULL;
}



no_grafo ** identifica_ciclo(grafo *g, char *nomeU, int M, int *n)
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

    if(M < 3){
        return NULL;
    }
    
    no_grafo ** ciclo = (no_grafo**) malloc(sizeof(no_grafo)*M);

    if (ciclo == NULL){
        return NULL;
    }
    
    int i = 0;
    *n = 1;
    ciclo[0] = encontra_no(g, nomeU);

    while(ciclo[0]->tamanho > i)
    {
        ciclo[1] = ciclo[0]->ligacoes[i]->destino;
        
        if(ajuda_identifica_ciclo(ciclo, n, M) != NULL){
            printf("%d\n",*n);
            return ciclo;
        }

        i++;
    }

    return NULL;
}