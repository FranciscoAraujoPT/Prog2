#include <stdio.h>

int main(){

    char url[]="lusiadas-utf8.txt";
    FILE *arq;
    int c, a=0, o=0, ces=0;
    
    arq = fopen(url, "r");

    if(arq == NULL){
        printf("Erro! Dead x(\n");

    } else{
        c = (int)getc(arq);

        while(c != EOF){

            if (c == 195){
                c = (int)getc(arq);
                if(c == 131 || c == 163) a++;
                if(c == 149 || c == 181) o++;
                if(c == 135 || c == 167) ces++;
            }
            c = (int)getc(arq);
        }
    }
    printf("Letra A com til = %d\nLetra O com til = %d\nLetra C com cedilha = %d\n", a, o, ces);

    return 0;
}