/*****************************************************************/
/*   Grafo direcionado | PROG2 | MIEEC | 2019/20        */      
/*****************************************************************/

#ifndef _GRAFO_H_
#define _GRAFO_H_

#include "tabdispersao.h"


/* Estrutura ligação ponderada.*/
struct no_grafos;

typedef struct
{
    int peso_ligacao;     /* ponderação da ligacao - número de mensagens enviadas do nome_user respectivo para este destino */
    struct no_grafos *destino; /* no´ destino */
} ligacao;

/* no_grafo e' uma estrutura que tem o user e 
   um vetor de ligações para os destinatários */
typedef struct no_grafos
{
    char *nome_user;    /* nome do user */
    int tamanho;        /* numero de ligacoes */
    ligacao **ligacoes;  /* vetor de ligacoes */
} no_grafo;

/* grafo e' implementado atraves de vetor de nos e as respetivas ligacoes  */

typedef struct
{
    int tamanho;        /* numero de nos */
    no_grafo **nos;  /* vetor de nos */
} grafo;

/* Cria grafo de tamanho 0
*  Retorna um apontador para o grafo criado
*/
grafo* grafo_novo();

/* Apaga grafo e liberta memoria 
*  parametro g - apontador para o grafo que se pretende apagar
*/
void grafo_apaga(grafo* g);

/* Insere um no´ no grafo
*  parametro g - apontador para o grafo em que se pretende inserir o no´
*  parametro user - nome do user do novo no´
*  retorna  apontador para o novo no´ ou NULL em caso de erro ou caso de no´ repetido
*  obs: nao esquecer de atualizar a estrutura grafo com o novo no´ 
*/
no_grafo * no_insere(grafo *g, char *user);

/* cria uma ligacao entre a origem e o destino com um determinado peso.
* parametro origem - apontador para o nó de origem da ligacao
* parametro destino - apontador para o nó de destino da ligacao
* retorno 0 se for bem sucedido e -1 em caso de erro
*/
int cria_ligacao(no_grafo *origem, no_grafo *destino, int peso);

/* Cria e retorna um grafo direccionado, com arestas pesados pelo número de mensagens enviadas para os respetivos nós.
*  parametro td - apontador para tabela de dispersao de onde se pretender criar o grafo
*  retorno de um apontador para o novo grafo, em caso de erro retorna NULL
*/ 
grafo * criaGrafo(tabela_dispersao *td);

/* encontra no´no grafo que tem um determinado user
*  parametro g - apontador para o grafo em que se pretende procurar
*  parametro nomeU - apontador para uma string que se pretende procurar no grafo
*  retorna um apontador para um nó do grafo, em caso de erro retorna NULL
*/
no_grafo * encontra_no(grafo *g, char *nomeU);



/* Devolve os amigos de um determinado nó 
*  parametro g - apontador para o grafo que se pretende pesquisar
*  parametro nomeU - apontador para string do nome do no´
*  parametro n - apontador para um inteiro que vai conter o numero de amigos. 
*  Retorna um vetor de apontadores para todos os nós do grafo ‘g’ que são "amigos" do nó com o nome ‘nomeU’. 
*  Retorna NULL se *não forem encontrados amigos ou em caso de erro.
*  Obs: Considera-se que dois nós são amigos se tiverem trocado 4 ou mais mensagens em cada direção, ou seja é amigo se enviou 4 ou mais e recebeu 4 ou mais mensagens. 
*  O tamanho do vetor deve ser retornado por referência através do argumento ‘n’. */
no_grafo **lista_amigos(grafo *g, char *nomeU, int *n);

/* Indentifica um ciclo apartir de um no´ com o máximo de M utilizadores 
*  parametro g - apontador para o grafo que se pretende pesquisar
*  parametro nomeU - apontador para string do nome do no´
*  parametro M - numero maximo de utilizadores.
*  parametro n - apontador para um inteiro que vai conter o numero de no´ no ciclo. 
*  Retorna vetor de apontadores para no´ do grafo ‘g’.  
*  obs: Os nós retornados deverão constituir o primeiro ciclo encontrado que inclua o utilizador ‘nomeU’ e 
*  inclua no mínimo 2 outros utilizadores. De forma a limitar a pesquisa, a função deve retornar ciclos com no máximo ‘M’ utilizadores. 
*  Retorna NULL se não for encontrado nenhum ciclo ou em caso de erro. Retorna via o argumento n o tamanho do vetor retornado.
*  Obs: o no´ inicial ser logicamente o que tem nomeU, deve aparecer na  primeira posicao do vetor e deve ser contabilizado para o argumento n. 
*/
no_grafo **identifica_ciclo(grafo *g, char *nomeU, int M, int *n);





#endif
