#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"


void vetor_imprimir(vetor* vec){

    int i;
    
    for(i=0;i<vec->tamanho;i++)
        printf("Frase %d: %s\n", i+1, vetor_elemento(vec, i));

}
int main()
{
    int i, pos;
    char valor[100];
    vetor *vec;

    vec = vetor_novo();

    for(i=0;i<5;i++){
        printf("Introduza uma frase: ");
        scanf("%s", valor);
        vetor_insere(vec, valor, i);
    }
    
    vetor_imprimir(vec);

    printf("\nIntroduza novamente uma frase: ");
    scanf("%s", valor);
    
    for(i=0;i<vec->tamanho;i++){
        if((pos = vetor_pesquisa(vec, valor)) == -1){
            break;
        } else{
            vetor_remove(vec, pos);
        }
    }

    vetor_imprimir(vec);

    vetor_ordena(vec);
    printf("\nVetor Ordenado:\n");
    vetor_imprimir(vec);

    vetor_apaga(vec);
}