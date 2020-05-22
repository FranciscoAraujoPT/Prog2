#include <stdio.h>
#include <string.h>

void inverte(char *strOriginal, char *strInvertida){

    int i=0, j=0;

    while (strOriginal[i] != '\0'){
        i++;
    }
    for(i=i-1;i>=0;i--){
        strInvertida[j] = strOriginal[i];
        j++;
    }
    strInvertida[j] = '\0';

}

void main() {

    char palavra[30], invertida[30];

    while(1){

        printf("Palavra? ");
        scanf("%s", palavra);

        if(palavra[0] == '.' && palavra[1] == '\0'){
            break;
        }
        
        inverte(palavra, invertida);

        if(strcmp(palavra, invertida) == 0){
            printf("Resultado: %s é capicua.\n", palavra);
        } else {
            printf("Resultado: %s não é capicua.\n", palavra);
        }
    }
}