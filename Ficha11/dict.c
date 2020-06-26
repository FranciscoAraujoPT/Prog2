#include "avl.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>



#define MAX_WORD 256


void downcase (char * str)
{
  if(str == NULL)
    return;

  while(*str != '\0')
  {
    *str = tolower(*str);
    str++;
  }
}

int le_dicionario(FILE * f, arvore_avl *dict) {

  /* alinea 1.1 */
  if(f == NULL){
    return 0;
  }

  if(dict == NULL){
    return 0;
  }
  
  int nPalavras=0;
  char palavra[MAX_WORD];

  while(fgets(palavra, MAX_WORD, f) != NULL)
  {
    palavra[strlen(palavra)-1] = '\0';
    downcase(palavra);
    if(avl_insere(dict, palavra) == -1){
      return 0;
    }
    nPalavras++;
  }

  return nPalavras;
}

char* isola_palavra(char *str, int *len) {

  /* alinea 1.2 */
  if(str == NULL){
    return NULL;
  }

  *len = 0;

  char c;
  char *palavra=NULL;

  while((c=str[*len]) != '\0')
  {
    if(c == ' ' && (*len)>0){
      break;
    }

    if(c != ' ' && palavra==NULL){
      palavra=&str[*len];
    }

    (*len)++;
  }

  return palavra;
}

char* verifica_texto(arvore_avl * dict, char *str, int *len) {

  /* alinea 1.3 */
  if(dict == NULL){
    return NULL;
  }

  if(str == NULL){
    return NULL;
  }

  if(len == NULL){
    return NULL;
  }
  
  int i;
  char *palavra=NULL;


  while((palavra=isola_palavra(str, len)) != NULL)
  {
    char aux2[*len+1];

    for(i=0;i<(*len);i++)
    {
      aux2[i]=palavra[i];
    }
    aux2[*len] = '\0';

    downcase(aux2);

    no_avl *aux = avl_pesquisa(dict, aux2);

    if(aux == NULL){
      return palavra;
    }
    str = &palavra[*len+1];
  }
  return palavra;
}

int main() {
    FILE * f = fopen("dict.txt", "r");
    if(!f) {
        puts("dict.txt nao encontrado!");
        return 1;
    }

    arvore_avl *dict = avl_nova();
    int words = le_dicionario(f, dict);

    printf("Lidas %d palavras\n", words);

    int len=0;
    char *ret = "The quick brown fox ola adeus jumps over the lazy dog foox barz bla";
    while((ret = verifica_texto(dict, ret , &len)) != NULL) {
        char word[MAX_WORD + 1] = {};
        strncpy(word, ret, len);
        printf("Palavra desconhecida: %s\n", word);
        ret += len;
    }
    
    avl_apaga(dict);
    fclose(f);
    return 0;
}
