/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2019/20         */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musica.h"



/* VERIFICACOES IMPLEMENTADAS */
int verifica_instante_novo(instante **t, int dura,  char* notas,  int bateria[],   char* extra)
{
    int er=0;
    
    *t = instante_novo(dura,notas,bateria,extra);
    if(!(*t))
    {
        printf("...verifica_instante_novo: instante novo e' NULL (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_instante_novo: instante novo nao e' NULL (ok)\n");

    int nbateria=0;
    for (int i=0; i<8; i++)
    {
        if ((*t)->bateria[i]!=bateria[i])
        nbateria++;

    }
    if(nbateria!=0)
    {
        printf("...verifica_instante_novo: bateria do novo instante (= ");
        for(int i = 0; i < 8; i++)
            printf("%d", (*t)->bateria[i]);

        printf(") e' diferente do esperado (= ");
        for (int i = 0; i < 8; i++)
            printf("%d", bateria[i]);

        printf(") (ERRO)\n");
        er++;
    }
    else{
        printf("...verifica_instante_novo: bateria coincide com o esperado (= ");
        for (int i = 0; i < 8; i++)
            printf("%d", bateria[i]);
        printf(") (ok)\n");
    }
        
    if (extra==NULL)
    {
        if((*t)->instrumentoExtra!=extra)
        {
            printf("...verifica_instante_novo: Instrumento extra do novo instante (= %s) e' diferente do esperado (= %s) (ERRO)\n", (*t)->instrumentoExtra, extra);
            er++;
        }
        else
            printf("...verifica_instante_novo: Instrumento extra coincide com o esperado (= %s) (ok)\n", extra);

    } else {
        if(strcmp((*t)->instrumentoExtra, extra))
        {
            printf("...verifica_instante_novo: Instrumento extra do novo instante (= %s) e' diferente do esperado (= %s) (ERRO)\n", (*t)->instrumentoExtra, extra);
            er++;
        }
        else
            printf("...verifica_instante_novo: Instrumento extra coincide com o esperado (= %s) (ok)\n", extra);    
    }

    if((*t)->duracao!=dura)
    {
        printf("...verifica_instante_novo: duracao do novo instante (= %d) e' diferente do esperado (= %d) (ERRO)\n", (*t)->duracao, dura);
        er++;
    }
    else
        printf("...verifica_instante_novo: duracao coincide com o esperado (= %d) (ok)\n", dura);  

    if (((*t)->notasGuitarra[0]!=notas[0]) || ((*t)->notasGuitarra[1]!=notas[2]))
    {
        printf("...verifica_instante_novo: notas da Guitarra do novo instante (= %c%C) e' diferente do esperado (= %c%c) (ERRO)\n", (*t)->notasGuitarra[0],(*t)->notasGuitarra[1], notas[0],notas[2]);
        er++;
    }
    else
        printf("...verifica_instante_novo: notas da Guitarra coincide com o esperado (= %c%c) (ok)\n", notas[0],notas[2]);  



    if (((*t)->notasPiano[0]!=notas[4]) || ((*t)->notasPiano[1]!=notas[6]))
    {
        printf("...verifica_instante_novo: notas da Piano do novo instante (= %c%c) e' diferente do esperado (= %c%c) (ERRO)\n", (*t)->notasPiano[0], (*t)->notasPiano[1], notas[4],notas[6]);
        er++;
    }
    else
        printf("...verifica_instante_novo: notas da Piano coincide com o esperado (= %c%c) (ok)\n", notas[4],notas[6]);          
    return er;
}

int verifica_instante_insere(musica *m, instante *t, instante **t2, instante **t1 )
{
    int er=0,erro;
    int dura=5,du=3;
    char *notas="A2B3D4", *notas1="E5";
    int bateria[]={1,0,1,0,1,0,1,0};
    char *extra="cv.mp3";
    *t2=instante_novo(du,notas,bateria,extra);
    *t1=instante_novo(dura,notas1,bateria,extra);
    
   
    erro = instante_insere(m,t,-1);
    if(erro==-1)
    {
        printf("...verifica_instante_insere: nao conseguiu inserir (ERRO)\n");
        return 1;
    }
    else{
        if (m->inicio!=t)
        {
            printf("...verifica_instante_insere: nao inseriu correctamente, o apontador inicio esta´ incorreto (ERRO)\n");
            er++;
        }
        else printf("...verifica_instante_insere: inseriu 1º instante com sucesso (ok)\n");
    }
      
    erro=instante_insere(m,*t2,-1);
    
    
    erro=instante_insere(m,*t1,1);
    
    if (m->inicio->proximo->duracao!=5 || m->inicio->proximo->proximo->duracao!=3)
    {
        printf("...verifica_instante_insere: não inseriu correctamente o 2º e 3º instantes, nao estao a na posicao correta (ERRO)\n");
        er++;
    } else
        printf("...verifica_instante_insere: inseriu nas poscicoes corretas o 2º e 3º instantes (ok)\n");

    return er;
}
int verifica_instante_remove(musica *m)
{
    int er=0;
    
    instante *t;
    t = instante_remove(m,4);
    if(t)
    {
        printf("...verifica_instante_remove(teste de pos invalido): removeu um instante de uma posicao invalida (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_instante_remove(teste de pos invalido): não remove nenhum instante  (ok)\n");

    t = instante_remove(m,0);    
    
    if(!t)
    {
        printf("...verifica_instante_remove(teste de pos valida ): nao removeu  (ERRO)\n");
        er++;
    }
    else if (t->duracao!=4)
    {
        printf("...verifica_instante_remove(teste de pos valida ): removeu um instante errado (ERRO)\n");
        er++;
    }
    else
    { 
        printf("...verifica_instante_remove(teste de pos valida ): removeu com sucesso (ok)\n");
    }
    return er;
}

int verifica_instante_apaga(instante **t)
{
    int erro;
    
    erro = instante_apaga(*t);
    if(erro==-1)
    {
        printf("...verifica_instante_apaga: deu erro ao apagar instante (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_instante_apaga: apagou com sucesso (ok)\n"); 
    return 0;

}


int verifica_musica_nova(musica **m)
{
    int er=0;
    
    *m = musica_nova();
    if(!(*m))
    {
        printf("...verifica_musica_nova: musica nova e' NULL (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_musica_nova: musica nova nao e' NULL (ok)\n");

    if ((*m)->inicio!=NULL)
    {
        printf("...verifica_musica_nova: apontador inicio nao e' NULL (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_musica_nova: apontador nova e' NULL (ok)\n");
        if ((*m)->cursor!=NULL)
        {
            printf("...verifica_musica_nova: apontador cursor nao e' NULL (ERRO)\n");
            er++;
        }
    else
        printf("...verifica_musica_nova: apontador cursor e' NULL (ok)\n");
    return er;
}

int verifica_musica_tamanho(musica *m)
{
    int er=0,erro=0;
 
    erro = musica_tamanho(m);
    if(erro!=3)
    {
        printf("...verifica_musica_tamanho: tamanho da musica (= %d) e' diferente do esperado (= 3) (ERRO)\n", erro);
        er++;
    }
    else
        printf("...verifica_musica_tamanho: tamanho da musica coincide com o esperado (= %d) (ok)\n", erro);
    return er;
}    

int verifica_musica_pesquisa_nota(musica * m)
{
    int er=0;
    instante *t;
    t = musica_pesquisa_nota(m,'E',1);
   
    if(!t)
    {
        printf("...verifica_musica_pesquisa_nota(Teste de uma nota que existe): nota nao foi encontrada (ERRO)\n");
        er++;
    }
    else
    if (t->duracao!=5)
    {
        printf("...verifica_musica_pesquisa_nota(Teste de uma nota que existe): nota encontrada no instante incorreto (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_musica_pesquisa_nota(Teste de uma nota que existe): nota encontrada no instante correto(ok)\n"); 

    t = musica_pesquisa_nota(m,'E',0);
   
    if(t)
    {
        printf("...verifica_musica_pesquisa_nota(Teste de uma nota que nao existe): retornou um instante (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_musica_pesquisa_nota(Teste de uma nota que nao existe): retornou null (ok)\n"); 
    return er;

}

int verifica_musica_toca(musica *m)
{
    int er = 0, erro = 0;

    erro = musica_toca(m, 2);
    if (erro == -1 || m->cursor->duracao != 1 || m->cursor->bateria[2] != 0 || m->cursor->bateria[3] != 1 || m->cursor->bateria[4] != 0)
    {
        printf("...verifica_musica_toca (Teste de fim de instante): cursor e' diferente do esperado (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_musica_toca (Teste de fim de instante): cursor coincide com o esperado (ok)\n");

    erro = musica_toca(m, 5);
    if (erro == -1 || m->cursor->duracao != 2 || m->cursor->notasPiano[0] != 'D' || m->cursor->notasPiano[1] != 'B')
    {
        printf("...verifica_musica_toca (Teste de meio de instante): cursor e' diferente do esperado (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_musica_toca (Teste de meio de instante): cursor coincide com o esperado (ok)\n");

    return er;
}

int verifica_musica_corrige(musica *m)
{
    int er = 0, erro = 0;

    erro = musica_corrige(m, "variante_B.txt");
    if (erro != 10)
    {
        printf("...verifica_musica_corrige: nu'mero de correcoes (= %d) e' diferente do esperado (= 10) (ERRO)\n", erro);
        er++;
    }
    else
        printf("...verifica_musica_corrige: nu'mero de correcoes coincide com o esperado (= %d) (ok)\n", erro);
    return er;
}

 /*================================================= */


int main()
{
    int errCount=0, err;
  
    int dura=4;
    char *notas="A2B3D4G5";
    int bateria[8]={1,0,1,0,1,0,1,0};
    char *extra="cv.mp3";

    instante *inst,*inst2,*inst3;
    musica *m;

    printf("INICIO DOS TESTES: Boa sorte\n\n");

    err =  verifica_instante_novo(&inst,dura,notas,bateria,extra);
   
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_instante_novo\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_instante_novo passou\n\n");
    }

    err = verifica_musica_nova(&m);
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_musica_nova\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_musica_nova passou\n\n");
    }

    err = verifica_instante_insere(m, inst,&inst2,&inst3);
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_instante_insere\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_instante_insere passou\n\n");
    }
    
    
  

    err = verifica_musica_tamanho(m);
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_musica_tamanho\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_musica_tamanho passou\n\n");
    }

    err = verifica_musica_pesquisa_nota(m);
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_musica_pesquisa_nota\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_musica_pesquisa_nota passou\n\n");
    }

    err = verifica_instante_remove(m);
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_instante_remove\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_instante_remove passou\n\n");
    }

    err = verifica_instante_apaga(&inst);
    if(err)
    {
        printf("ERRO: %d erros encontrados em verifica_instante_apaga\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_instante_apaga passou\n\n");
    }

    musica_apaga(m);


    musica *m1 = musica_importa("loop_A.txt");
    
    if(m1 == NULL){
        printf("Falhou importacao da musica\n");
    }
    else{
        printf("Musica importada com sucesso: %d instantes\n", musica_tamanho(m1));
    }
    
    err = verifica_musica_toca(m1);
    if (err)
    {
        printf("ERRO: %d erros encontrados em verifica_musica_toca\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_musica_toca passou\n\n");
    }
    err = verifica_musica_corrige(m1);
    if (err)
    {
        printf("ERRO: %d erros encontrados em verifica_musica_corrige\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: verifica_musica_corrige passou\n\n");
    }
    musica_apaga(m1);
    if (errCount == 0)
        printf("FIM DOS TESTES: Todos os testes passaram\n");
    else
        printf("FIM DOS TESTES: Foram encontrados %d ERROS no total\n", errCount);
    return 0;

}
