/*****************************************************************/
/*   Grafo direcionado | PROG2 | MIEEC | 2019/20        */      
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

#define PESO_AMIGO 4

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

    if(encontra_no(g, user) != NULL){
        return NULL;
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

int grafo_aresta(no_grafo* origem, no_grafo* dest)
{
    if(origem == NULL){
        return 0;
    }

    if(dest == NULL){
        return 0;
    }

    for(int i=0;i<origem->tamanho;i++)
    {
        if(origem->ligacoes[i]->destino == dest){
            return 1;
        }
    }

    return 0;
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
    int msg[2];
    msg[0] = msg[1] = 0;

    for(int i=0;i<td->tamanho;i++){
        elem = td->elementos[i];
        while(elem != NULL)
        {   
            if(elem->msg != NULL){
                
                origem = encontra_no(g, elem->msg->remetente);
                dest = encontra_no(g, elem->msg->destinatario);

                if(origem != NULL && dest != NULL){
                    if(grafo_aresta(origem, dest)){
                        elem = elem->proximo;
                        continue;
                    }
                }

                if(origem == NULL){
                    origem = no_insere(g, elem->msg->remetente);
                }

                if(dest == NULL){
                    dest = no_insere(g, elem->msg->destinatario);
                }

                ligacao2(td, elem->msg->remetente, elem->msg->destinatario, msg);

                if(msg[0]>0){
                    cria_ligacao(origem, dest, msg[0]);
                }

                if(msg[1]>0){
                    cria_ligacao(dest, origem, msg[1]);
                }
            }
            elem = elem->proximo;
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

    no_grafo ** amigos = NULL, **candidatos_amigo =  NULL;
    no_grafo *no;
    int count = 0, tamanho = 0;
    
    no = encontra_no(g, nomeU);
    
    if(no == NULL){
        return NULL;
    }

    for(int i=0;i<no->tamanho;i++)
    {
        if(no->ligacoes[i]->peso_ligacao >= PESO_AMIGO){
            candidatos_amigo = (no_grafo **) realloc(candidatos_amigo, sizeof(no_grafo)*(count+1));
            if(candidatos_amigo == NULL){
                return NULL;
            }
            candidatos_amigo[count] = no->ligacoes[i]->destino;
            count++;
        }
    }
    
    if(count != 0){
        for(int i=0;i<count;i++)
        {
            for(int j=0;j<candidatos_amigo[i]->tamanho;j++)
            {
                if(strcmp(candidatos_amigo[i]->ligacoes[j]->destino->nome_user, nomeU) == 0){
                    if(candidatos_amigo[i]->ligacoes[j]->peso_ligacao >= PESO_AMIGO){
                        amigos = (no_grafo **) realloc(amigos, sizeof(no_grafo)*((tamanho)+1));
                        if(amigos == NULL){
                            free(candidatos_amigo);
                            return NULL;
                        }
                        amigos[tamanho] = candidatos_amigo[i];
                        (tamanho)++;
                        break;
                    }
                }
            }
        }   
    }
    free(candidatos_amigo);
    
    if(tamanho > 0){
        *n = tamanho;
        return amigos;
    }

    return NULL;
}

int dfs(no_grafo *no, int indice, int M, no_grafo* resultados[])
{   
    if(indice >= M){
        return 0;
    }

    if(indice > 0){
        if(no ==  resultados[0]){
            return indice;
        }
    }

    resultados[indice] = no;

    int d;
    for(int i=0;i<no->tamanho;i++)
    {
        no = no->ligacoes[i]->destino;
        printf("%d: %s\n",i, no->nome_user);
        d = dfs(no, indice+1, M,resultados);
        if(d > 0){
            return indice;
        }
        indice--;
    }
    
    return 0;
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
    
    no_grafo ** ciclo = (no_grafo**) calloc(M,sizeof(no_grafo*));

    if (ciclo == NULL){
        return NULL;
    }

    ciclo[0] = encontra_no(g, nomeU);
    printf("0: %s\n", ciclo[0]->nome_user);

    if(ciclo[0] == NULL){
        return NULL;
    }

    int i = 0, indice = 0;

    indice = dfs(ciclo[0], indice, M, ciclo);

    printf("indice = %d\n", indice);
    for(int j=0;i<indice;j++)
    {
        printf("%s\n", ciclo[j]->nome_user);

    }

    return NULL;
}