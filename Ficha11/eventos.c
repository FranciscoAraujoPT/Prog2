#include "heap.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 256
#define MAX_HEAP 256

int pop_number(char *str) {
    int i = strlen(str) - 1;
    while(i >= 0 && isspace(str[i])) i--;

    if(i < 0)
        return -1;

    while(i >= 0 && !isspace(str[i])) i--;
    i++;

    int ret = atoi(str + i);
    str[i] = 0;

    return ret;
}

int say_number(char *str) {
    int i = strlen(str) - 1;
    while(i >= 0 && isspace(str[i])) i--;

    if(i < 0)
        return -1;

    while(i >= 0 && !isspace(str[i])) i--;
    i++;

    int ret = atoi(str + i);

    return ret;
}


int le_eventos(FILE *f, heap *eventos_agendados) {
    
    /* alinea 2.1 */
    if(f == NULL){
        return 0;
    }

    if(eventos_agendados == NULL){
        return 0;
    }
    
    char palavra[MAX_LINE];
    int nEventos=0, prioridade;

    while(fgets(palavra, MAX_LINE, f) != NULL)
    {
        pop_number(palavra);
        palavra[strlen(palavra)-1] = '\0';
        
        prioridade = say_number(palavra);

        heap_insere(eventos_agendados, palavra, prioridade);
        nEventos++;
    }

    return nEventos;
}

int processa_tempo(int tempo, heap *eventos_agendados, heap *eventos_espera) {

    /* alinea 2.2 */
    
    int duracao, prioridade,nEventos=0;
    char *palavra;
    heap *aux = heap_nova(MAX_HEAP);

    while((palavra = heap_remove(eventos_agendados)) != NULL)
    {
        prioridade = say_number(palavra);

        duracao=say_number(palavra);
        
        if(duracao <= tempo){
            prioridade = prioridade*-1;
            pop_number(palavra);
            palavra[strlen(palavra)-1] = '\0';
            heap_insere(eventos_espera, palavra, prioridade);
        } else {
            heap_insere(aux, palavra, prioridade);
        }
        nEventos++;
    }

    while((palavra = heap_remove(aux)) != NULL)
    {
        heap_insere(eventos_agendados, palavra, prioridade);
    }
    
    heap_apaga(aux);

    return nEventos;
}

char* proximo_evento(heap *eventos_espera, int *duracao) {

    /* alinea 2.3 */
    char *palavra;

    if((palavra = heap_remove(eventos_espera)) == NULL){
        return NULL;
    }
    
    *duracao = pop_number(palavra);

    return palavra;
}


void processa_eventos(heap *eventos_agendados){
    heap * eventos_espera = heap_nova(MAX_HEAP);
    int time = 0;

    while(eventos_espera->tamanho || eventos_agendados->tamanho)
    {   
        processa_tempo(time, eventos_agendados, eventos_espera);

        if(eventos_espera->tamanho) {
            char * evento;
            int duracao;
            evento = proximo_evento(eventos_espera, &duracao);
            printf("@%d: %s (duracao: %d)\n", time, evento, duracao);
            time += duracao;
            free(evento);
        }
        else
            time = eventos_agendados->elementos[1]->prioridade;
    }

    

    heap_apaga(eventos_espera);
}


int main() {
    FILE *f;
    int eventos;
    heap *eventos_agendados;

    f = fopen("eventos.txt", "r");
    if(!f) {
        puts("eventos.txt nao encontrado!");
        return 1;
    }

    eventos_agendados = heap_nova(MAX_HEAP);

    eventos = le_eventos(f, eventos_agendados);
    printf("Lidos %d eventos\n", eventos);
    heap_imprime(eventos_agendados, 1);
    printf("\n");
    processa_eventos(eventos_agendados);

    heap_apaga(eventos_agendados);
    fclose(f);
    return 0;
}
