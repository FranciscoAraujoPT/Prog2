#include <stdio.h>

int ordenado(int src[],int n){

    int i, res=1;

    for(i=0;i<(n-1);i++){
        if(src[i] > src[i+1]){
            res = 0;
        }
        if(res == 0){
            break;
        }
    }
    
    return res;
}

void main() 
{
    int n, i;

    printf("Introduza o número de números: ");
    scanf("%d", &n);
    
    int v[n];

    for(i=0;i<n;i++){
        printf("Introduza %dº número: ", i+1);
        scanf("%d", &v[i]);
    }

    if(ordenado(v,n) == 1) {
        
        printf("Vetor:");
        
        for(i=n-1;i>=0;i--){
            printf(" %d", v[i]);
        }
    }
    printf("\n");
}