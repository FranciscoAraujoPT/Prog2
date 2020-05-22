#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, *p, i;
    
    printf("Número de elementos? ");
    scanf("%d", &n);

    p=(int*)malloc(sizeof(int)*n);

    for(i=0;i<n;i++){
        printf("Introduza o %dº elemento: ", i+1);
        scanf("%d", &p[i]);
    }

    printf("\nVetor original: [ ");
    for(i=0;i<n;i++){
        printf("%d ", p[i]);
    }
    printf("]\nNúmeros pares: [ ");
    for(i=0;i<n;i++){
        if( p[i]%2 == 0)
            printf("%d ", p[i]);
    }
    printf("]\nNúmeros ímpares: [ ");
    for(i=0;i<n;i++){
        if( p[i]%2 != 0)
            printf("%d ", p[i]);
    }
    printf("]\n");

    free(p);
    p = NULL;
    
    return 0;
}