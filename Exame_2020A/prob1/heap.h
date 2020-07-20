/*****************************************************************/
/*   Fila de prioridade / min-heap | PROG2 | MIEEC | 2018/19    */
/*****************************************************************/

#ifndef HEAP_H
#define HEAP_H

typedef struct {
	float prioridade;
	float valor;
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
int heap_insere(heap *h, float valor, float prioridade);

/* remove elemento na raiz da heap */
float heap_remove(heap *h);

/* imprime o estado actual da heap, a partir do indice indicado */
void heap_imprime(heap *h, int indice);

#endif /* HEAP_H */
