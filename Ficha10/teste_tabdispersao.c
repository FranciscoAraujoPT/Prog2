#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tabdispersao.h"

#define NOME_FICHEIRO "englishwords.txt"
#define TAMANHO_TAB_DISP 100000

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

int main() {
    
    clock_t inicio, fim, inicioTab, fimTab;
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
    inicioTab = clock();

    tabela_dispersao *td_djbm = ler_para_tabela(NOME_FICHEIRO, TAMANHO_TAB_DISP, hash_djbm);
    if(td_djbm == NULL){
        printf("erro a ler para tabela de dispersao\n");
        return -1;
    }
    fimTab = clock();

    tempo = (double)(fimTab - inicioTab) / CLOCKS_PER_SEC;
    
    printf("tempo em segundos: %lf\n", tempo);
    printf("#elementos: %d\n\n", tabela_numelementos(td_djbm));

    printf("\nFIM\n");
}