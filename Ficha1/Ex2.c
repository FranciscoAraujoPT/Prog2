#include <stdio.h>

void main()
{
    int i, j, v1[5], v2[5];

    printf("Vetor 1:\n");
    for(i=1;i<6;i++){
        printf("Introduza %dº número: ", i);
        scanf("%d", &v1[i-1]);
    }

    printf("Vetor 2:\n");
    for(i=1;i<6;i++){
        printf("Introduza %dº número: ", i);
        scanf("%d", &v2[i-1]);
    }

    printf("\nComuns: ");
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(v1[i] == v2[j])
                printf("%d ", v1[i]);
        }
    }
    printf("\n");
}