#include <stdio.h>
#include "bst.h"
#include "avl.h"

int main() {

    int i;
    arvore_bst* bst;
    arvore_avl* avl;

    avl = avl_nova();
    bst = bst_nova();

    i=bst_insere(bst,"G");
    if(i==-1)
        printf("Erro 1!");
    i=bst_insere(bst,"C");
    if(i==-1)
        printf("Erro 2!");
    i=bst_insere(bst,"A");
    if(i==-1)
        printf("Erro 3!");
    i=bst_insere(bst,"F");
    if(i==-1)
        printf("Erro 4!");
    i=bst_insere(bst,"L");
    if(i==-1)
        printf("Erro 5!");
    i=bst_insere(bst,"J");
    if(i==-1)
        printf("Erro 6!");
    i=bst_insere(bst,"V");
    if(i==-1)
        printf("Erro 7!");
    i=bst_insere(bst,"M");
    if(i==-1)
        printf("Erro 8!");
    i=bst_insere(bst,"N");
    if(i==-1)
        printf("Erro 9!");
    i=bst_insere(bst,"O");
    if(i==-1)
        printf("Erro 10!");

    printf("Bst:\n\tAltura = %d\n\t", bst_altura(bst->raiz));
    bst_imprime(bst);

    i=avl_insere(avl,"G");
    if(i==-1)
        printf("Erro 1!");
    i=avl_insere(avl,"C");
    if(i==-1)
        printf("Erro 2!");
    i=avl_insere(avl,"A");
    if(i==-1)
        printf("Erro 3!");
    i=avl_insere(avl,"F");
    if(i==-1)
        printf("Erro 4!");
    i=avl_insere(avl,"L");
    if(i==-1)
        printf("Erro 5!");
    i=avl_insere(avl,"J");
    if(i==-1)
        printf("Erro 6!");
    i=avl_insere(avl,"V");
    if(i==-1)
        printf("Erro 7!");
    i=avl_insere(avl,"M");
    if(i==-1)
        printf("Erro 8!");
    i=avl_insere(avl,"N");
    if(i==-1)
        printf("Erro 9!");
    i=avl_insere(avl,"O");
    if(i==-1)
        printf("Erro 10!");

    printf("Avl:\n\tAltura = %d\n\t", avl_altura(avl->raiz));
    avl_imprime(avl);

    avl_apaga(avl);

    return 0;
}