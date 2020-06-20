#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tabdispersao.h"

#define NOME_FICHEIRO "passwords.txt"
#define TAMANHO_TAB_DISP 10

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

    char user[TAMANHO_CHAVE], pass[TAMANHO_VALOR];
    
    while(fscanf(f,"%s %s", user, pass) != EOF)
    {
        tabela_adiciona(td, user, pass);
    }
    fclose(f);

    return td;
}

int main() 
{
    tabela_dispersao *td_djbm = ler_para_tabela(NOME_FICHEIRO, TAMANHO_TAB_DISP, hash_djbm);
    if(td_djbm == NULL){
        printf("erro a ler para tabela de dispersao\n");
        return -1;
    }

    char user[TAMANHO_CHAVE], pass[TAMANHO_VALOR];
    
    printf("Login: ");
    scanf("%s", user);

    printf("Password: ");
    scanf("%s", pass);

    if(tabela_valor(td_djbm, user) == NULL){
        printf("Authentication failed.\n");
    } else {
        printf("Authentication succeeded.\n");
    }

    tabela_apaga(td_djbm);
    
    return 0;
}