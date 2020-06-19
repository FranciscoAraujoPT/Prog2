#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tabdispersao.h"

#define NOME_FICHEIRO "englishwords.txt"
#define TAMANHO_TAB_DISP 100000
#define NUMERO_TESTES 5

elemento *ler_para_lista(const char *nomef, int *tamanho)
{
    if(nomef == NULL){
        return NULL;
    }

    FILE *f = fopen(nomef, "r");

    if(f == NULL){
        return NULL;
    }

    elemento *inicio = NULL, *anterior = NULL;
    *tamanho = 0;
    char palavra[TAMANHO_CHAVE+1];

    while(1)
    {
        if(fgets(palavra, TAMANHO_CHAVE, f) == NULL){
            break;
        }
        palavra[strlen(palavra)-1] = '\0';

        objeto *obj = (objeto *)malloc(sizeof(objeto));
        strcpy(obj->chave, palavra);
        strcpy(obj->valor, palavra);

        elemento *elem = (elemento *)malloc(sizeof(elemento));
        elem->obj = obj;
        elem->proximo = NULL;

        if(*tamanho == 0){
            inicio = elem;
        } else {
            anterior->proximo = elem;
        }

        (*tamanho)++;
        anterior = elem;
    }
    fclose(f);

    return inicio;
}

tabela_dispersao *ler_para_tabela(const char *nomef, int tamanho, hash_func *hfunc){
    
    if(nomef == NULL){
        return NULL;
    }

    FILE *f = fopen(nomef, "r");

    if(f == NULL){
        return NULL;
    }
    tabela_dispersao *td = tabela_nova(tamanho, hfunc);
    
    if(td == NULL){
        return NULL;
    }
    char palavra[TAMANHO_CHAVE+1];
    
    while(1)
    {
        if(fgets(palavra, TAMANHO_CHAVE, f) == NULL){
            break;
        }
        palavra[strlen(palavra)-1] = '\0';

        tabela_adiciona(td, palavra, palavra);
    }
    fclose(f);

    return td;
}

const char *lista_pesquisa(elemento *inicio, const char *chave)
{
    if(inicio == NULL || chave == NULL)
        return NULL;

    elemento *elem = inicio;
    while(elem != NULL)
    {
        if(strcmp(elem->obj->chave, chave) == 0)
            return elem->obj->valor;

        elem = elem->proximo;
    }

    return NULL;
}

const char* Chave_random(elemento* lst, int *tamanho){

    if(lst == NULL){
        return NULL;
    }

    int i;
    static long int nRandon = 0;
    srand(time(NULL));
    
    for(i=0;i<nRandon;i++){
        rand();
    }

    nRandon = rand() % *tamanho;
    
    for(i=0;i<nRandon;i++)
    {
        lst=lst->proximo;
    }
    
    return lst->obj->chave;
}

int main() {
    
    clock_t inicio, fim;
    double tempo;

    printf("Ler para lista ligada - ");
    int tamanho_lista;
    inicio = clock();

    elemento *lst = ler_para_lista(NOME_FICHEIRO, &tamanho_lista);
    if(lst == NULL) {
        printf("erro a ler para lista ligada\n");
        return -1;
    }
    fim = clock();
    
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("tempo em segundos: %lf\n", tempo);
    printf("#elementos: %d\n\n", tamanho_lista);
    
    /*Verificação da lista*/
    // FILE *f1 = fopen("teste.txt", "w"), *f2 = fopen("teste2.txt", "w");

    // while((fputs(lst->obj->chave, f1) != EOF) && (fputs(lst->obj->valor, f2) != EOF)) 
    // {
    //     lst = lst->proximo;
    // }

    printf("Ler para tabela de dispersao (hash_djbm) - ");
    inicio = clock();

    tabela_dispersao *td_djbm = ler_para_tabela(NOME_FICHEIRO, TAMANHO_TAB_DISP, hash_djbm);
    if(td_djbm == NULL){
        printf("erro a ler para tabela de dispersao\n");
        return -1;
    }
    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("tempo em segundos: %lf\n", tempo);
    printf("#elementos: %d\n\n", tabela_numelementos(td_djbm));

    printf("Ler para tabela de dispersao (hash_krm) - ");
    inicio = clock();

    tabela_dispersao *td_krm = ler_para_tabela(NOME_FICHEIRO, TAMANHO_TAB_DISP, hash_krm);
    if(td_krm == NULL){
        printf("erro a ler para tabela de dispersao\n");
        return -1;
    }
    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("tempo em segundos: %lf\n", tempo);
    printf("#elementos: %d\n\n", tabela_numelementos(td_krm));

    for(int i=1;i<=NUMERO_TESTES;i++)
    {
        const char* s=Chave_random(lst,&tamanho_lista);
        
        printf("Teste %d- pesquisa na lista:\n\n", i);
        inicio = clock();

        if(lista_pesquisa(lst, s) == NULL){
            printf("\tNa lista a chave \"%s\" tem o valor NULL.\n", s);
        } else {
            printf("\tNa lista a chave \"%s\" tem o valor \"%s\".\n", s, lista_pesquisa(lst, s));
        }
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        
        printf("\tTempo em segundos: %lf\n", tempo);

        printf("\nTeste %d- pesquisa na tabela de dispersão (hash_djbm):\n\n", i);
        
        inicio = clock();
        printf("\tNa tabela de dispersão (hash_djbm) a chave \"%s\" tem o valor \"%s\".\n", s, tabela_valor(td_djbm, s));
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        
        printf("\tTempo em segundos: %lf\n\n", tempo);
        
        printf("\nTeste %d- pesquisa na tabela de dispersão (hash_krm):\n\n", i);

        inicio = clock();
        printf("\tNa tabela de dispersão (hash_krm) a chave \"%s\" tem o valor \"%s\".\n", s, tabela_valor(td_krm, s));
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        
        printf("\tTempo em segundos: %lf\n\n", tempo);
    }
    printf("FIM\n");
}