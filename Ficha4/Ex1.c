#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main() {

    int i, j;
    char name[100];
    FILE *f;
    lista *l;

    f = fopen("arquivo.txt", "r");

    l = lista_nova();

    while (fgets(name, 100, f) != NULL) {
            lista_insere(l, name, NULL);
            i++;
    }
    printf("Foram carregados %d jogos.\n", i);
    for(j=0;j<i;j++){
        printf("%s", lista_elemento(l, j)->str);
    }
    fclose(f);
}