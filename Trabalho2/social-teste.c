/*****************************************************************/
/*         Trabalho pratico 2  | PROG2 | MIEEC | 2019/20       */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tabdispersao.h"
#include "grafo.h"
#include "stnova.h"


/* DEFINES E VARIAVEIS GLOBAIS UTEIS PARA OS TESTES */
#define MAX_LINHA 1024
#define TAB_MSG 17
#define TAB_MSG1 997

/* VERIFICACOES IMPLEMENTADAS */
int verifica_tabela_existe(tabela_dispersao* td)
{
    int er=0;
    
    int t=tabela_existe(td, "FERNANDO");
    if(t!=0)
    {
        printf("...verifica_tabela_existe(Remetente inexistente): tabela_existe deu diferente de 0 (ERRO)\n");
       er++;
    }
    else
        printf("...verifica_tabela_existe(Remetente inexistente): tabela_existe deu 0 (OK)\n");

    t=tabela_existe(td, "ANA");
    if(t!=7)
    {
        printf("...verifica_tabela_existe(Remetente que existe): tabela_existe deu diferente de 7 (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_tabela_existe(Remetente que existe): tabela_existe deu 7 (OK)\n"); 

    return er;
}

int verifica_tabela_listagem(tabela_dispersao* td)
{
    int er=0;
    
    mensagem** t=tabela_listagem(td, "FERNANDO");
    if(t==NULL)
    {
        printf("...verifica_tabela_listagem(Remetente inexistente): tabela_listagem deu NULL (ERRO)\n");
        er++;
    } else
    {
       if(t[0]!=NULL)
        {
            printf("...verifica_tabela_listagem(Remetente inexistente): tabela_listagem a primeira posição deu diferente de NULL (ERRO)\n");
            er++;
        }
        else
            printf("...verifica_tabela_listagem(Remetente inexistente): tabela_listagem a primeira posição deu NULL (OK)\n");
    }

    
   
   free(t);

   t=tabela_listagem(td, "ANA");
   if(t==NULL)
    {
        printf("...verifica_tabela_listagem(Remetente inexistente): tabela_listagem deu NULL (ERRO)\n");
        er++;
    }
    else { 
        int i=0;
        if (t)
        {
            while (t[i]!=NULL)
            { 
                i++;
            }

            if(i!=7)
            {
                printf("...verifica_tabela_listagem(Remetente que existe): tabela_listagem deu diferente de 7 mensagens(ERRO)\n");
                er++;
            }
            else
                printf("...verifica_tabela_listagem(Remetente que existe): tabela_listagem deu 7 mensagens(OK)\n"); 

            i=0;
        
            free(t);
        }
    }
    return er;
}


int verifica_ligacao2(tabela_dispersao* td)
{
    int er=0;
    int totMsg[2]={0};
    ligacao2(td,"LUIS","FERNANDO",totMsg);
    if(totMsg[0]!=-1 || totMsg[1]!=-1)
    {
        printf("...verifica_ligacao2(Os remetentes sao inexistente): ligacao2 deu diferente de -1 -1 (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_ligacao2(Os remetentes sao inexistente): ligacao2 deu -1 -1 (OK)\n");

    ligacao2(td,"PEDRO","MARIA",totMsg);
   

 if(totMsg[0]!=0 || totMsg[1]!=1)
    {
        printf("...verifica_ligacao2(Remetentes existentes): ligacao2 deu diferente de 0 1 (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_ligacao2(Remetentes existentes): ligacao2 deu 0 1 (OK)\n");
    return er;
}


int verifica_criaGrafo(tabela_dispersao* td,grafo **g)
{
    int er=0;
    *g=criaGrafo(td);
    
    if (*g)
    {
      
        if((*g)->tamanho!=7)
        {
            printf("...verifica_criaGrafo(numero de nos): criaGrafo deu diferente de 7 (ERRO)\n");
            er++;
        }
        else
            printf("...verifica_criaGrafo(numero de nos): criaGrafo deu 7 (OK)\n");
    } else
        
        {
            printf("...verifica_criaGrafo(numero de nos): criaGrafo deu NULL (ERRO)\n");
            er++;
        } 
 
    return er;
   
}
int verifica_lista_amigos(grafo *g)
{
    int er=0;
    int n=0;
    no_grafo **nos=lista_amigos(g, "PEDRO", &n);
   
    if(n!=0)
    {
        printf("...verifica_lista_amigos(sem amigos): lista_amigos deu diferente de 0(ERRO)\n");
        er++;
    }
    else
        printf("...verifica_lista_amigos(sem amigos): lista_amigos deu 0 (OK)\n");
    free(nos);
    
  nos=lista_amigos(g, "ANA", &n);
  
    if(n==0)
    {
        printf("...verifica_lista_amigos(sem amigos): lista_amigos deu  0 (ERRO)\n");
        er++;
    }
    else
   if (strcmp(nos[0]->nome_user,"MAFALDA"))
    {
        printf("...verifica_lista_amigos(com amigos): lista_amigos deu diferente da amiga MAFALDA (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_lista_amigos(com amigos): lista_amigos deu a amiga MAFALDA (OK)\n");
	
    free(nos);

    return er;
   
}



int verifica_identifica_ciclo(grafo *g)
{
    int er=0;
    no_grafo **nosciclo;
    int r;
    
    nosciclo=identifica_ciclo(g, "MARIA", 4, &r);
 
 
    if(nosciclo==NULL)
    {
        printf("...verifica_identifica_ciclo(com ciclo): identifica_ciclo deu NULL (ERRO)\n");
        er++;
    }
    else if(r!=4)
    {
        printf("...verifica_identifica_ciclo(com ciclo): identifica_ciclo deu um numero de nos diferente de 4 (ERRO)\n");
        er++;
    }
    else
    { 
        printf("...verifica_identifica_ciclo(com ciclo): identifica_ciclo deu um numero de nos igual a 4 (OK)\n");
        printf("Os no´s foram: ");
        for (int i=0;i<r-1;i++)
            printf("[%d %s] : ",i+1,nosciclo[i]->nome_user);
        printf("[%d %s]\n",r,nosciclo[r-1]->nome_user);
    }
    free(nosciclo);
    
    return er;
   
}


int verifica_st_remove(estrutura *st)
{
    int er=0;
     
    
    
    elemento *el=st_remove(st,"ANA");
    elemento *aux;
 
    if(el==NULL)
    {
        printf("...verifica_st_remove(): st_remove deu NULL (ERRO)\n");
        er++;
    }
    else 
    {   char amigo[TAMANHO_CHAVE];
        int i=0;
        if (strcmp(el->msg->remetente,"ANA")==0)
            strcpy(amigo,el->msg->destinatario);

        while (el)
        {
            i++;

            aux=el->proximo;
	    if (el->msg->texto)
		  free(el->msg->texto);
	    free(el->msg);
	    free(el);
	    el=aux;

        }
       if((i==4) && (strcmp(amigo,"MAFALDA")==0))
        {
            printf("...verifica_st_remove(): st_remove removeu a amiga MAFALDA com 4 mensagens (OK)\n");
        
        }
        else
           { 
            printf("...verifica_st_remove():  st_remove não removeu a amiga MAFALDA com 4 mensagens (ERRO)\n");
            er++;
           }
    }
    
    
    return er;
   
}
 /*================================================= */

int verifica_tabela_existe1(tabela_dispersao* td)
{
    int er=0;
    
    int t=tabela_existe(td, "JACK");
   
     if(t!=778)
    {
        printf("...verifica_tabela_existe(Remetente que existe): tabela_existe deu diferente de 778 (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_tabela_existe(Remetente que existe): tabela_existe deu 778 (OK)\n"); 

    return er;
}

int verifica_tabela_listagem1(tabela_dispersao* td)
{
    int er=0;
    
    mensagem** t=tabela_listagem(td, "JAKE");

   if(t==NULL)
    {
        printf("...verifica_tabela_listagem(Remetente inexistente): tabela_listagem deu NULL (ERRO)\n");
        er++;
    }
    else { 
        int i=0;
        if (t)
        {
            while (t[i]!=NULL)
            { 
                i++;
            }

            if(i!=521)
            {
                printf("...verifica_tabela_listagem(Remetente que existe): tabela_listagem deu diferente de 521 mensagens(ERRO)\n");
                er++;
            }
            else
                printf("...verifica_tabela_listagem(Remetente que existe): tabela_listagem deu 521 mensagens(OK)\n"); 

        
            free(t);
        }
    }
    return er;
}

int verifica_ligacao21(tabela_dispersao* td)
{
    int er=0;
    int totMsg[2]={0};
    ligacao2(td,"CATES","HAMMOND",totMsg);


  
   
 if(totMsg[0]!=135 || totMsg[1]!=109)
    {
        printf("...verifica_ligacao2(Remetentes existentes): ligacao2 deu diferente de 135 e 109 (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_ligacao2(Remetentes existentes): ligacao2 deu 135 109 (OK)\n");
    return er;
}


int verifica_criaGrafo1(tabela_dispersao* td,grafo **g)
{
    int er=0;
    *g=criaGrafo(td);
    
    if (*g)
    {
      
        if((*g)->tamanho!=1545)
        {
            printf("...verifica_criaGrafo(numero de nos): criaGrafo deu diferente de 1545 nós (ERRO)\n");
            er++;
        }
        else
            printf("...verifica_criaGrafo(numero de nos): criaGrafo deu 1545 nós (OK)\n");
    } else
        
        {
            printf("...verifica_criaGrafo(numero de nos): criaGrafo deu NULL (ERRO)\n");
            er++;
        } 
 
    return er;
   
}

int verifica_lista_amigos1(grafo *g)
{
    int er=0;
    int n=0,j,i,correto=0,resultado=0;
    no_grafo **nos=lista_amigos(g, "WOMAN", &n);
    char nomes[6][14]={"CHESS PLAYER","JACK","JACOB","JOE","MILES","ROB"};
    if(n==0)
    {
       
       er++;
    }
    else
   {    
       resultado=1;
       for (i=0;i<n;i++)
       {   
           correto=0;
           for(j=0;j<6;j++)
           {
               
               if (strcmp(nos[i]->nome_user,nomes[j])==0)
                {
                    correto=1;
                    break;
                }
           }
           if (correto==0) 
            {
                resultado=0;
            }
       }

       if (!resultado)
    {
        printf("...verifica_lista_amigos(com amigos): lista_amigos deu pelos menos um diferente ""CHESS PLAYER"",""JACK"",""JACOB"",""JOE"",""MILES"",""ROB"" (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_lista_amigos(com amigos): lista_amigos deu ""CHESS PLAYER"",""JACK"",""JACOB"",""JOE"",""MILES"",""ROB"" (OK)\n");
   }
    free(nos);

    return er;
   
}


int verifica_identifica_ciclo1(grafo *g)
{
     int er=0;
     no_grafo **nosciclo;
    int r;
    
    nosciclo=identifica_ciclo(g, "ERNEST",8, &r);
 
 
    if(nosciclo==NULL)
    {
        printf("...verifica_identifica_ciclo(com ciclo): identifica_ciclo deu NULL (ERRO)\n");
        er++;
    }
    else if(r>=3 && r<=8)

    {
        printf("...verifica_identifica_ciclo(com ciclo): identifica_ciclo deu um numero de nos está entre 3 e 8 (OK)\n");
        printf("Os no´s foram: ");
        for (int i=0;i<r-1;i++)
            printf("[%d %s] : ",i+1,nosciclo[i]->nome_user);
        printf("[%d %s]\n",r,nosciclo[r-1]->nome_user);
        
    }
    else
    {  
       
        printf("...verifica_identifica_ciclo(com ciclo): identifica_ciclo deu um numero de nos que não está entre 3 e 8 (ERRO)\n");
        printf("Os no´s foram: ");
        for (int i=0;i<r-1;i++)
            printf("[%d %s] : ",i+1,nosciclo[i]->nome_user);
        printf("[%d %s]\n",r,nosciclo[r-1]->nome_user);
        er++;
    }
    free(nosciclo);
    
    return er;
   
}

int verifica_st_remove1(estrutura *st)
{
    int er=0;
    clock_t start_t, end_t;
    start_t = clock(); 
    elemento *el=st_remove(st,"HELEN");
    end_t = clock();
    elemento *aux;
   
    if(el==NULL)
    {
        printf("...verifica_st_remove(): st_remove deu NULL (ERRO)\n");
        er++;
    }
    else 
    {   char amigo[TAMANHO_CHAVE];
        int i=0;
         if (strcmp(el->msg->remetente,"HELEN")==0)
               strcpy(amigo,el->msg->destinatario);
        
        while (el)
        {
            i++;

            aux=el->proximo;
	    if (el->msg->texto)
		    free(el->msg->texto);
	    free(el->msg);
	    free(el);
	    el=aux;

        }
       if((i==67) && (strcmp(amigo,"CALVIN")==0))
        {
            printf("...verifica_st_remove(): st_remove removeu a amiga CALVIN com 67 mensagens (OK)\n");
            printf("\tTempo a remover: %.8f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
        }
        else
           { 
            printf("...verifica_st_remove():  st_remove removeu a amiga %s com %d mensagens devia ser (CALVIN,67) (ERRO)\n",amigo,i);
            
            er++;
           }
    }
    
    
    return er;
   
}

 /*================================================= */


int main()
{

    int errCount=0, err;
    char *fi= "dados.txt";
  

    tabela_dispersao* td;
    grafo *g;
    
    td=tabela_carrega(fi,TAB_MSG);
    
   
    
    printf("INICIO DOS TESTES: Boa sorte\n\n");
    printf("Teste com poucos utilizadores\n\n");

    err =  verifica_tabela_existe( td);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_tabela_existe\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_tabela_existe passou\n\n");
    }

     err =  verifica_tabela_listagem( td);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_tabela_listagem\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_tabela_listagem passou\n\n");
    }

    err =  verifica_ligacao2( td);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_ligacao2\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_ligacao2 passou\n\n");
    }

    err =  verifica_criaGrafo(td,&g);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_criaGrafo\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_criaGrafo passou\n\n");
    }

      err =  verifica_lista_amigos(g);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_lista_amigos\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_lista_amigos passou\n\n");
    }


    err =  verifica_identifica_ciclo(g);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_identifica_ciclo\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_identifica_ciclo passou\n\n");
    }
   
  
  

    estrutura *st=st_nova();

    
    st_importa_tabela(st,td);

    

    err =  verifica_st_remove(st);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_st_remove\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_st_remove passou\n\n");
    }
     
    

     
    st_apaga(st); 
    tabela_apaga(td);
    grafo_apaga(g); 
   
/*================================================= */
/* Com um ficheiro maior */

    char *fic= "dataset_partA.txt";
    printf("Teste com muitos utilizadores\n\n");

    td=tabela_carrega(fic,TAB_MSG1);



    err =   verifica_tabela_existe1(td);


    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_st_remove\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_st_remove passou\n\n");
    }
     

    err =  verifica_tabela_listagem1( td);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_tabela_listagem\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_tabela_listagem passou\n\n");
    }

    err =  verifica_ligacao21( td);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_ligacao2\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_ligacao2 passou\n\n");
    }

    err =  verifica_criaGrafo1(td,&g);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_criaGrafo\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_criaGrafo passou\n\n");
    }

    err =  verifica_lista_amigos1(g);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_lista_amigos\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_lista_amigos passou\n\n");
    }

    err =  verifica_identifica_ciclo1(g);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_identifica_ciclo\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_identifica_ciclo passou\n\n");
    }
    st=st_nova();
  
    
    st_importa_tabela(st,td);
   
     
   
   
    err =  verifica_st_remove1(st);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_st_remove\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_st_remove passou\n\n");
    } 
    
    st_apaga(st); 
    tabela_apaga(td);
    grafo_apaga(g);
    
    if (errCount == 0)
        printf("FIM DOS TESTES: Todos os testes passaram\n");
    else
        printf("FIM DOS TESTES: Foram encontrados %d ERROS no total\n", errCount);
        
    return 0;

    

}
