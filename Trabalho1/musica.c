/*****************************************************************/
/*Biblioteca musica | PROG2 | MIEEC | 2019/20     */
/*****************************************************************/

#include "musica.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

instante* instante_novo(int duracao, char *notas, int bateria[],  char* instrumentoExtra)
{
    int i;
    /* aloca memoria para a estrutura instante */
    instante *inst = (instante*)malloc(sizeof(instante));

	if(inst == NULL || duracao < 1 || duracao > 16)
		return NULL;
    
    /* copia valor da duração */
    inst->duracao = duracao;
    
    for(i=0;i<2;i++){
        inst->notasGuitarra[i] = '-';
        inst->notasPiano[i] = '-';
    }

    if(notas != NULL){
    /* copia valores para as notas de guitarra e piano */
        for (i=0;i<strlen(notas);i++){
            if(notas[i]<'A' || notas[i]>'G')
                return NULL;
            i++;
            if(notas[i]<'2' || notas[i]>'5')
                return NULL;
        }
        for(i=0;i<strlen(notas);i=i+2){
            if(notas[i+1] == '2'){ 
                inst->notasGuitarra[0] = notas[i];
            } else if(notas[i+1] == '3'){ 
                inst->notasGuitarra[1] = notas[i];
            } else if(notas[i+1] == '4'){ 
                inst->notasPiano[0] = notas[i];
            } else if(notas[i+1] == '5'){ 
                inst->notasPiano[1] = notas[i];
            }
        }     
    }

    /* copia valores para a bateria */
    for (i=0;i<8;i++){
        if(bateria[i] != 0 && bateria[i] != 1)
            return NULL;
        inst->bateria[i] = bateria[i];
    }
    
    /* aloca memoria para string instrumentoExtra e copia os valores para a mesma */
    if(instrumentoExtra != NULL){
        inst->instrumentoExtra = (char *)malloc((strlen(instrumentoExtra)+1)*sizeof(char));
        if(inst->instrumentoExtra == NULL){
            free(inst);
            return NULL;
        }
        for(i=0;i<strlen(instrumentoExtra)+1;i++){
            inst->instrumentoExtra[i]=instrumentoExtra[i];
        }
    } else
        inst->instrumentoExtra = NULL;
    
    /* O proximo instante ainda não existe */
    inst->proximo = NULL;

	return inst;
}

musica* musica_nova()
{
    /* aloca memoria para a estrutura musica*/
	musica *music = (musica*)malloc(sizeof(musica));
	if(music == NULL)
		return NULL;

    /* Os instantes ainda não existem */
    music->inicio = music->cursor = NULL;

	return music;
}


int  instante_insere(musica *m , instante *t, int pos )
{
	if(m == NULL || t == NULL || pos<-1 || pos > musica_tamanho(m)){
    	return -1;
    }

    int i;

    instante *atual;
    atual = m->inicio;

	/* inserir no fim da lista */
	if(pos == -1) {
		/* se for o primeiro instante */
		if (m->inicio == NULL) {
			m->inicio = m->cursor = t;
            t->proximo = m->inicio;
		} else {
            while(atual->proximo != m->inicio){
                atual = atual->proximo;
            }
            atual->proximo = t;
            t->proximo = m->inicio;
		}
		return 0;
	}

	/* inserir no inicio da lista */
	if (pos == 0){
        /* se for o primeiro instante */
        if (m->inicio == NULL) {
			m->inicio = m->cursor = t;
            t->proximo = m->inicio;
		} else {
        t->proximo=m->inicio;
            while(atual->proximo != m->inicio){
                atual = atual->proximo;
            }
            atual->proximo = t; 
            m->inicio = t;
        }
        return 0;
	}
    
    /* troca apontadores para inserir instante */
    for(i=0;i<pos-1;i++){
        atual = atual->proximo;
    }
    t->proximo = atual->proximo;
    atual->proximo = t;

    return 0;
}

int musica_tamanho(musica *m)
{
    if(m == NULL)
		return -1;

    int i=0;
    instante *atual;
    /*verifica se existe um instante */
    if((atual = m->inicio) != NULL){
        i++;
        while(atual->proximo != m->inicio){
            atual = atual->proximo;
            i++;
        }
    }

	return i;
}

instante* musica_pesquisa_nota(musica *m, char nota, int instrumento)
{

    if(m == NULL || nota<'A' || nota>'G' || instrumento > 1 || instrumento < 0){
        return NULL;
    }
    
    int i;
    instante *atual;
    atual = m->inicio;
    
    /* pesquisa a partir do inicio */
    while(atual->proximo != m->inicio){
        for(i=0;i<2;i++){
            if(instrumento == 0){
                if(atual->notasGuitarra[i] == nota){
                    return atual;
                }
            } else {
                if(atual->notasPiano[i] == nota){
                    return atual;
                }
            }
        }
        atual = atual->proximo;
    }

	return NULL;
}


instante* instante_remove(musica *m, int pos)
{
	if (m == NULL || pos > (musica_tamanho(m)-1) || pos<0)
        return NULL;
    
    instante *atual;
    instante *aux;

    atual = m->inicio;
    aux = atual;

    //remove instante inicio
    if (pos == 0)
    {
        while (atual->proximo != m->inicio){
            atual = atual->proximo;
        }
        //certificar que cursor não é retirado
        if(m->cursor == m->inicio)
            m->cursor=m->inicio->proximo;
        atual->proximo = m->inicio->proximo;
        atual = m->inicio;
        m->inicio = m->inicio->proximo;
        atual->proximo = NULL;
        return atual;
    }
    //outros casos
    for (int i = 0; i < pos - 1; i++)
        atual = atual->proximo;
    //certificar que cursor não é retirado
    if(m->cursor == atual->proximo)
        m->cursor=atual->proximo->proximo;
    aux=atual->proximo;
    atual->proximo = atual->proximo->proximo;
    aux->proximo=NULL;
    return aux;

}


int instante_apaga( instante *t )
{
    if(t == NULL){
        return -1;
    }
    /* libertar memoria dinâmica alocada do instante */
	free(t->instrumentoExtra);
    t->instrumentoExtra = NULL;
    free(t);
    t = NULL;
    
    return 0;
}


int musica_apaga(musica *m)
{
    if(m == NULL)
        return -1;

    int i, tamanho = musica_tamanho(m);
    instante *atual;
    instante *aux;

    atual = m->inicio;
    /* libertar memoria dinâmica aloca de cada instante da lista*/
    for (i=0; i < tamanho; i++){
        aux = atual;
        atual = atual->proximo;
        instante_apaga(aux);
    }
    /* libertar memoria dinâmica alocada para a musica */
    free(m);
    m = NULL;

	return 0;
}

musica *musica_importa(const char *nomef){
    FILE *f = fopen(nomef, "r");
    if(f == NULL) return NULL;
    
    musica *m = musica_nova();
    if(m == NULL){
        fclose(f);
        return NULL;

    }

    int duracao = 0, i, j;
    char str_aux[100] = {};
    int bateria[8] = {0};
    char notas[9] = {0};
    char instrumentoExtra[100] = {0};
   
    instante *aux;

    while(fscanf(f, "%d", &duracao) != EOF){
        fgets(str_aux, 100*sizeof(char), f);
        str_aux[strlen(str_aux)-1] = '\0';

        /* lê os 8 carateres correspondentes à bateria */
        i = 0;
        j = 1;
        while(i < 8){
            
            bateria[i] = atoi(str_aux+j);
            i++;
            j+=2;
        }

        /* lê o resto da linha do ficheiro */
        if(strlen(str_aux+17) > 1){
            j = 0;
            for(i = 17; i < strlen(str_aux+17)+18; i++){
                if(str_aux[i] == ' ') continue;
                else if(str_aux[i] == '"'){
                    strcpy(instrumentoExtra, str_aux+i+1);
                    instrumentoExtra[strlen(instrumentoExtra) - 1] = '\0';
                    break;
                }
                else if(j < 8){
                    notas[j++] = str_aux[i];
                }
            }
           
        }
       
        /* cria novo instante (caso não exista instrumentoExtra coloca NULL */
        if(strlen(instrumentoExtra) <= 1){
            aux = instante_novo(duracao, notas, bateria, NULL);
        }
        else{
            aux = instante_novo(duracao, notas, bateria, instrumentoExtra);
        }
        
        if(aux == NULL){
            musica_apaga(m);
            fclose(f);
            return NULL;
        }
        /* insere instante na lista */
        if(instante_insere(m, aux, -1) == -1){
            musica_apaga(m);
            fclose(f);
            return NULL;
        }
        /* reinicia instrumentoExtra e notas */
        memset(instrumentoExtra, '\0', 100);
        memset(notas, '\0', 9);

    }
    fclose(f);
    return m;

}
int musica_toca(musica *m, int duracao)
{
    if(m == NULL || duracao<0)
        return -1;

    while(duracao > 0){
        /* retira do tempo total o tempo do instante */
        duracao = duracao - m->cursor->duracao;
        m->cursor = m->cursor->proximo;
    }

    return 0;
}
int musica_corrige(musica *m, char *ficheiro){

    FILE* f;
    if( m == NULL || ficheiro == NULL || (f = fopen(ficheiro, "r")) == NULL)
        return -1;

    int i, aux1, aux2, aux3, aux4, aux5, inicio, fim, instrumento, estado, tamanho=(musica_tamanho(m)-1), duracao, sucesso = 0;
    char c,antiga, nova, lixo[100]={};
    instante* atual;

    while((c=fgetc(f)) != EOF){
        switch(c){
            case '1': //remove instantes
                fgets(lixo, 100, f);
                i=(sscanf(lixo,"%n%d%n%d%n",&aux1, &inicio, &aux2, &fim, &aux3));
                
                /* Verificação de entradas impossiveis */
                if(i!=2 || lixo[aux1]!= ' ' || lixo[aux2]!= ' ' || (lixo[aux3]!= '\0' && lixo[aux3]!='\n') || strlen(lixo)>(aux3+1)){
                    break;
                }
                
                /* Verificação de valores impossiveis */
                if(inicio>fim || inicio<0 || inicio>tamanho || fim<0 || fim>tamanho){
                    break;
                } else {
                    for(i=inicio;i<=fim;i++){
                        instante_apaga(instante_remove(m, inicio));
                        tamanho--;
                    }
                    sucesso++;
                    break;
                }

            case '2': //altera notas da guitarra ou piano
                fgets(lixo, 100, f);
                i=(sscanf(lixo,"%n%d%n%*c%c%n%*c%c%n",&aux1, &instrumento, &aux2, &antiga, &aux3, &nova, &aux4));
                /* Verificação de entradas impossiveis */
                if(i!=3 || lixo[aux1]!= ' ' || lixo[aux2]!= ' ' || lixo[aux3]!= ' ' || (lixo[aux4]!= '\0' && lixo[aux4]!='\n') || strlen(lixo)>(aux4+1)){
                    break;
                }   
                
                /* Verificação de valores impossiveis */
                if(antiga<'A' || antiga>'G' || nova<'A' || nova>'G' || instrumento<0 || instrumento>1){
                    break;
                } else {
                    atual = m->inicio;
                    while(atual->proximo != m->inicio){
                        if(instrumento == 0){
                            for(i=0;i<2;i++){
                                if(atual->notasGuitarra[i] == antiga)
                                    atual->notasGuitarra[i] = nova;
                            }
                        } else {
                            for(i=0;i<2;i++){
                                if(atual->notasPiano[i] == antiga)
                                    atual->notasPiano[i] = nova;
                            }
                        }
                        atual = atual->proximo;
                    }
                    sucesso++;
                    break;
                }

            case '3': // altera os estados dos instrumentos da batera
                fgets(lixo, 100, f);
                i=(sscanf(lixo,"%n%d%n%d%n%d%n%d%n",&aux1, &instrumento, &aux2, &estado, &aux3, &inicio, &aux4, &fim, &aux5));
                
                /* Verificação de entradas impossiveis */
                if(i!=4 || lixo[aux1]!= ' ' || lixo[aux2]!= ' ' || lixo[aux3]!= ' ' || lixo[aux4]!= ' ' || (lixo[aux5]!= '\0' && lixo[aux5]!='\n') || strlen(lixo)>(aux5+1)){
                    break;
                }

                /* Verificação de valores impossiveis */
                if(inicio>fim || estado<0 || estado>1 || instrumento<0 || instrumento>7 || inicio<0 || inicio >tamanho || fim<0 || fim>tamanho){
                    break;
                } else {
                    atual = m->inicio;
                    for (i=0; i < inicio; i++){
                        atual = atual->proximo;
                    }
                    
                    for (i=inicio; i <= fim; i++){
                        atual->bateria[instrumento] = estado;
                        atual = atual->proximo;
                    }
                    
                    sucesso++;
                    break;
                }
                
            case '4': //altera a duração dos instantes
                fgets(lixo, 100, f);
                i=(sscanf(lixo,"%n%d%n%d%n%d%n",&aux1, &duracao, &aux2, &inicio, &aux3, &fim, &aux4));

                /* Verificação de entradas impossiveis */
                if(i!=3 || lixo[aux1]!= ' ' || lixo[aux2]!= ' ' || lixo[aux3]!= ' ' || (lixo[aux4]!= '\0' && lixo[aux4]!='\n') || strlen(lixo)>(aux4+1)){
                    break;
                }

                /* Verificação de valores impossiveis */
                if(duracao<1 || duracao>16 || inicio>fim || inicio<0 || inicio >tamanho || fim<0 || fim>tamanho){
                    break;
                } else {
                    atual = m->inicio;
                    for (i=0; i < inicio; i++){
                        atual = atual->proximo;
                    }
                    
                    for (i=inicio; i <= fim; i++){
                        atual->duracao = duracao;
                        atual = atual->proximo;
                    }
                    
                    sucesso++;
                    break;
                }
                default:
                    fgets(lixo, 100, f);
        }
    }

    fclose(f);
    return sucesso;
}