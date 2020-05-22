#include <stdio.h>

int main () {

    int j, erro=0, i=0, c[128], tag[4]={'T','A','G',0}, titulo[30], artista[30], album[30], ano[4], comentario[30], genero, numero;
    char url[]="musica.mp3"; 
     
    FILE *f;

    f = fopen(url, "r");
    
    if(f == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
        erro = 1;
    } else {
        fseek( f, -128, SEEK_END );
        while( (c[i]=fgetc(f))!= EOF )
            ++i;
    }
    if((c[0] == tag[0]) && (c[1] == tag[1]) && (c[2] == tag[2])){
        i = 3;
        for(j=0;j<30;j++){
            titulo[j] = c[i];
            artista[j] = c[i+30];
            album[j] = c[i+60];
            comentario[j] = c[i+94];
            ++i;
        }
        i = 93;
        for(j=0;j<4;j++) {
            ano[j] = c[i];
            ++i;
        }
    }else {
        printf("Erro! Ficheiro não é uma música.");
        erro = 1;
    }

    if(erro == 0){
        printf("Título- "); 
        for(j=0;j<30;j++) printf("%c", titulo[j]);

        printf("\nArtísta- ");
        for(j=0;j<30;j++) printf("%c", artista[j]);

        printf("\nAlbum- ");
        for(j=0;j<30;j++) printf("%c", album[j]);

        printf("\nAno- ");
        for(j=0;j<4;j++) printf("%c", ano[j]);

        if(comentario[27] != 0){
            printf("\nComentario- ");
            for(j=0;j<30;j++) printf("%c", comentario[j]);

        } else {
            printf("\nComentario- ");
            for(j=0;j<28;j++) printf("%c", comentario[j]);

            numero = comentario[29];
            printf("\nNúmero- %d", numero);

            genero = c[127];
            printf("\nGénero- %d", genero);
        }
        printf("\n");
    }
    
    fclose(f);
    
    return(0);
}