/*****************************************************************/
/*   Estrutura nova a implementar | PROG2 | MIEEC | 2019/20   */      
/*****************************************************************/

#ifndef _STNOVA_H_
#define _STNOVA_H_

#include "tabdispersao.h"

/* podem criar mais struct que achem necessárias*/



typedef struct
{
 		
} estrutura;


/**
 * cria e inicializa a estrutura criada
 */
estrutura* st_nova();



/**
 * Tenta inserir o elemento elem na estrutura st, garantindo acesso mais rápido aos elementos 
 * com maior número total de mensagens trocadas.
 * parametro st - apontador para a estrutura criada 
 * parametro elem - elemento que se pretende inserir na estrutura
 * Retorna 0 se bem-sucedida ou -1 em contrário.
 * */
int st_insere(estrutura *st, elemento *elem);


/*
* Importa todo o conteúdo da tabela td para o novo formato de acesso. 
* parametro st - apontador para a estrutura criada 
* parametro td - apontador para a tabela de dispersao
* Retorna 0 se bem-sucedido ou -1 em contrário.
*/
int st_importa_tabela(estrutura *st, tabela_dispersao *td);


/*
* Extrai a instância do par remetente-destinatário com maior soma de mensagens enviadas e recebidas entre eles, 
* levando juntamente todas as mensagens enviadas pelo remetente. 
* parametro st - apontador para a estrutura criada 
* parametro remetente - apontador para o utilizador em que vai procurar o que tem mais ligacoes 
* Retorna apontador para o primeiro elemento de uma lista ligada de ‘elemento’,
* terminada com o campo ‘proximo’ do  último elemento apontando para NULL. Retorna NULL se não for encontrado ou em caso de erro.
* Obs : A instância retornada deverá ser consumida, i.e. não deverá ficar uma cópia dela em ‘st’. 
*/
elemento *st_remove(estrutura *st,char *remetente);

/*
*  Elimina todas as instâncias presentes na estrutura st e desaloca toda a memória da estrutura.
*  parametro st - apontador para a estrutura criada 
*  Retorna 0 se bem-sucedido e -1 se ocorrer algum erro.  
*/
int st_apaga(estrutura *st);


#endif