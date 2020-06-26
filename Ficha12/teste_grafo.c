#include <stdio.h>
#include "grafo.h"

unsigned int fib(unsigned int n)
{
    if(n == 0 || n == 1){
        return n;
    }

    return (fib(n-1) + fib(n-2));
}

unsigned int fib2(unsigned int n, unsigned int * nchamadas)
{
    printf("\tfib(%d)", n);

    if(n == 0 || n == 1){
        (*nchamadas)++;
        return n;
    }

    (*nchamadas)++;
    return (fib2(n-1, nchamadas) + fib2(n-2, nchamadas));
}

unsigned int fib3(unsigned int n, unsigned int * nchamadas, unsigned int resultados[])
{
    if(n > 100){
        return -1;
    }

    if(resultados[n] != -1){
        return resultados[n];
    }

    if(n == 0 || n == 1){
        (*nchamadas)++;
        return resultados[n] = n;
    }

    (*nchamadas)++;
    return (resultados[n-1] = fib3(n-1, nchamadas, resultados)) + (resultados[n-2] = fib3(n-2, nchamadas, resultados));
}

int main()
{
    unsigned int n, f;
    unsigned int nchamadas=0;
    unsigned int resultados[100];
    
    printf("Teste 1:\n\tN? ");
    scanf("\t%d", &n);

    f = fib(n);
    printf("\tO número de Fibonacci de ordem %d é %d.\n\n", n, f);

    printf("Teste 2:\n\tN? ");
    scanf("\t%d", &n);

    f = fib2(n,&nchamadas);
    printf("\n\tfib() foi chamado %d vezes.\n\tO número de Fibonacci de ordem %d é %d.\n\n", nchamadas, n, f);

    nchamadas=0;

    for(int i=0;i<100;i++)
    {
        resultados[i]=-1;
    }

    printf("Teste 3:\n\tN? ");
    scanf("\t%d", &n);

    f = fib3(n,&nchamadas, resultados);
    printf("\tfib() foi chamado %d vezes.\n\tO número de Fibonacci de ordem %d é %d.\n", nchamadas, n, f);

    return 0;
}