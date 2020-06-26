#include <stdio.h>
#include "grafo.h"

unsigned int pas(unsigned int linha, unsigned int coluna)
{
    if(coluna > linha){
        return 0;
    }

    if(coluna == 0){
        return 1;
    }

    return pas(linha-1, coluna-1) + pas(linha-1, coluna);
}

unsigned int pas2(unsigned int linha, unsigned int coluna, unsigned int (*resultados)[100])
{
    if (linha>100 || coluna>100)
    {
        return -1;
    }
    
    if(resultados[linha][coluna] != -1){
        return resultados[linha][coluna];
    }

    if(coluna > linha){
        return 0;
    }

    if(coluna == 0){
        return 1;
    }

    return pas(linha-1, coluna-1) + pas(linha-1, coluna);
}

int main()
{
    unsigned int col, lin, p;
    unsigned int resultados[100][100];

    printf("Teste 1:\n\tLinha? ");
    scanf("\t%d", &lin);
    printf("\tColuna? ");
    scanf("\t%d", &col);

    p = pas(lin, col);
    printf("\tO elemento do triângulo de Pascal em (%d, %d) é %d.\n\n", lin, col, p);

    for(int i=0;i<100;i++)
    {
        for(int j=0;j<100;j++){   
           resultados[i][j]=-1;
        }
    }

    printf("Teste 2:\n\tLinha? ");
    scanf("\t%d", &lin);
    printf("\tColuna? ");
    scanf("\t%d", &col);

    p = pas2(lin, col, resultados);
    printf("\tO elemento do triângulo de Pascal em (%d, %d) é %d.\n\n", lin, col, p);

    return 0;
}