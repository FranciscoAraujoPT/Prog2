#include <stdio.h>

void main() 
{
    float a, min, max, i;

    printf("Qual o valor de a? ");
    scanf("%f", &a);
    printf("Qual o intervalo? ");
    scanf("%f", &min);
    scanf("%f", &max);
    printf("Qual o incremento? ");
    scanf("%f", &i);

    while (min <= max) {
        printf("f(%.2f) = %.2f\n", min, a*(min*min));
        min = min + i;
    }
}
