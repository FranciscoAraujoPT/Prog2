#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main() {
    
    int *n1, n2, i;
    grafo *g = grafo_novo(8, 0);

    grafo_adiciona(g,1,2);
    grafo_adiciona(g,1,4);
    grafo_adiciona(g,1,7);
    grafo_adiciona(g,2,3);
    grafo_adiciona(g,2,5);
    grafo_adiciona(g,3,6);
    grafo_adiciona(g,4,7);
    grafo_adiciona(g,5,6);
    grafo_adiciona(g,5,7);
    grafo_adiciona(g,6,7);

    n1 = grafo_bfs(g,1,6, &n2);

    for(i=0;i<n2-1;i++)
    {
        printf("%d->", *(n1+i));
    }

    printf("%d\nFIM\n", *(n1+n2-1));

    free(n1);
    grafo_apaga(g);

    return 0;
}
