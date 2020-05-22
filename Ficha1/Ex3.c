#include <stdio.h>

float avg(float x[]){
    
    int i=0;
    float total=0;

    while(i < 10){
        total = total + x[i];
        i++;
    }

    return total/10;
}
float max(float x[]){

    int i=1;
    float max = x[0];

    while(i < 10){
        if (x[i] > max)
            max = x[i];
        i++;
    }

    return max;
}
float min(float x[]){

    int i=1;
    float min = x[0];

    while(i < 10){
        if (x[i] < min)
            min = x[i];
        i++;
    }

    return min;
}

void main()
{
    int i, j; 
    float v[10], maximo, minimo, media;

    for(i=1;i<11;i++){
        printf("Introduza %dº número: ", i);
        scanf("%f", &v[i-1]);
    }

    printf("Média: %.2f\nMáximo: %.2f\nMínimo: %.2f\n", media = avg(v), maximo = max(v), minimo = min(v));

    printf("Vetor:");
    for(i=0;i<10;i++){
        printf(" %.2f", v[i]);
    }
    printf("\n");
}
