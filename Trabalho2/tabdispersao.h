/*****************************************************************/
/*         Tabela de Dispersao | PROG2 | MIEEC | 2019/20         */
/*****************************************************************/

#ifndef TABDISPERSAO_H
#define TABDISPERSAO_H


#define TABDISPERSAO_OK   		(0)
#define TABDISPERSAO_ERRO       (-1)


#define TAMANHO_CHAVE	26


/* tabela de dispersao de mensagems baseada em encadeamento */

typedef unsigned long hash_func(const char *, int);

/** conteudo individual da tabela de dispersao:
 * cada mensagem tem um remetente que é a chave, destinatario e um texto associado que é a memsagem
 */
typedef struct
{
	/*nome da remetente da mensagem*/
	char remetente[TAMANHO_CHAVE];

	/*nome do destinatario da mensagem*/
	char destinatario[TAMANHO_CHAVE];

	/* mensagem de texto*/
	char *texto;
} mensagem;


/** elemento da tabela de dispersao */
typedef struct elem
{
	/* apontador para a mensagem*/
	mensagem *msg;

	/* apontador para o proximo elemento */
	struct elem * proximo;
} elemento;

/**
 * A estrutura tabela_dispersao para armazenar dados relativos a uma tabela de dispersao
 */
typedef struct
{
	hash_func *hfunc;		/* apontador para a funcao a ser usada (hash_djbm, hash_krm, ...) */
	elemento **elementos;	/* vetor de elementos */
	int tamanho;			/* tamanho do vetor de elementos */
} tabela_dispersao;

/**
 * cria uma tabela de dispersao
 * parametro tamanho - tamanho da tabela de dispersao
 * parametro hash_func - apontador para funcao de dispersao a ser usada nesta tabela
 * return uma tabela de dispersao vazia que usa a funcao de dispersao escolhida
 */
tabela_dispersao* tabela_nova(int tamanho, hash_func *hfunc);

/**
 * elimina uma tabela, libertando toda a memoria ocupada
 * parametro td - tabela de dispersao a ser apagada da memoria
 * Obs: apagar todos os elementos anteriormente alocados na memoria
 */
void tabela_apaga(tabela_dispersao *td);

/**
 * adiciona uma nova mensagem 'a tabela; 
 * parametro td - tabela onde adicionar o objeto
 * parametro remet - remetente da mensagem a ser adicionada
 * parametro dest - destinatario da mensagem a ser adicionada
 * parametro texto - texto da mensagem a ser adicionada
 * obs: podem existir mensagens exatamente iguais.
 */
int tabela_adiciona(tabela_dispersao *td, const char *remet,const char *dest, const char *texto) ;



/**
 * Número de  mensagens de um determinado rementente na tabela
 * parametro td - tabela onde procurar o valor
 * parametro remet - remetente da mensagem a procurar
 * retorna o numero de mensagens do remetente, -1 em caso de erro e 0 se o remetente não existir
 */
int tabela_existe(tabela_dispersao *td, const char *remetente);

/**
 * Mensagems de um determinado remetente
 * parametro td - tabela onde procurar o valor
 * parametro remet - remetente da mensagem a procurar
 * Retorna um vetor de mensagens de um remetente ou NULL se não existem.
 * Obs: A ultima posição do vetor deverá ser NULL, de forma a indicar o final do vetor.
 */
mensagem **tabela_listagem(tabela_dispersao *td, const char *remetente);

/**
 * Apaga todos os valores correntemente na tabela, ficando a tabela vazia
 * parametro td tabela a ser esvaziada
 * Retorna 0 se tiver sucesso e -1 se encontrar algo erro
 */
int tabela_esvazia(tabela_dispersao *td);


/**
 * Calcula hash com base na seguinte formula:
 *            hash(i) = hash(i-1) + chave[i]
 *    em que hash(0) = 7
 *
 * \param chave string para a qual se pretende calcular o chave de hash
 * \param tamanho da tabela de dispersão
 * \remark chave[i] e' o caracter no indice de i da chave
 */
unsigned long hash_krm(const char* chave, int tamanho);




/*
* Esta funcao preenche uma nova tabela de dispersão a partir de um ficheiro
* parametro ficheiro - ficheiro de onde se carrega a tabela
* parametro tamanho - tamanho da tabela de dispersao
* retorna a tabela de  dispersão criada , ou NULL se ocorrer algum erro
*/
tabela_dispersao* tabela_carrega(char *ficheiro,int tamanho);

/*
* Esta funcao devolve o numero de mensagens trocadas entre dois utilizadores através do parametro totMsg
* parametro td - tabela de dispersao onde procurar as mensagens
* parametro nomeU1 - nome do utilizador 1
* parametro nomeU2 - nome do utilizador 2
* parametro totMsg - na posição 0 de ‘totMsgs’ retorna o número total de mensagens enviadas do utilizador ‘nomeU1’ para
* ‘nomeU2’ e na posição 1 de ‘totMsgs’ retorna as enviadas de ‘nomeU2’ para ‘nomeU1’
* Obs: totMsg[0/1] = -1 caso o utilizador 0/1 não exista enquanto remetente
*/
void ligacao2(tabela_dispersao *td, char *nomeU1, char *nomeU2, int totMsg[2]);

#endif
