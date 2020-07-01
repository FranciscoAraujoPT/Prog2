/*****************************************************************/
/*   Fila de prioridade / max-heap | PROG2 | MIEEC | 2018/19    */
/*****************************************************************/

#ifndef HEAP_H
#define HEAP_H

typedef struct {
	int prioridade;
	char *valor;
} elemento;

typedef struct {
	/* numero de elementos no vetor */
	int tamanho;
	/* tamanho maximo do vetor */
	int capacidade;

	/* vetor de apontadores para elementos */
	elemento ** elementos;
} heap;

/* cria nova heap */
heap* heap_nova(int tamanho_maximo);

/* apaga heap */
void heap_apaga(heap *h);

/* insere elemento na heap com uma determinada prioridade */
int heap_insere(heap *h, const char * texto, int prioridade);

/* remove elemento na raiz da heap */
char* heap_remove(heap *h);

/* imprime o estado actual da heap, a partir do indice indicado */
void heap_imprime(heap *h, int indice);


/* retorna numero de elementos da heap ou -1 se heap nao existe */
int heap_num_elementos(heap *h);

/* retorna elemento prioritario na heap ou NULL se heap nao existe
 * parametro prioridade instancia com a prioridade do elemento */
char* heap_elemento_topo(heap* h, int* prioridade);


#endif /* HEAP_H */
