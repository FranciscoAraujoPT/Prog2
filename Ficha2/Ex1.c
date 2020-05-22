#include <stdio.h>


int main()  {
    
    char url[]="lusiadas.txt";
    int i=0, abc[26][2]={{0},{0}}, j, c;
    
    FILE *arq;
    
    arq = fopen(url, "r");
    
    if(arq == NULL){
        printf("Erro! Dead x(\n");
    } else{
        c = (int)getc(arq);
        while(c != EOF){
         
            if (c >= (int)'a' && c <= (int)'z'){
                ++abc[c-(int)'a'][1];
                ++i;
            } else if (c >= (int)'A' && c <= (int)'Z'){
                ++abc[c-(int)'A'][1];
                ++i;
            } else if ((c >= 224 && c <= 227) || (c >= 192 && c <= 195)) {
                ++abc[0][1];
                ++i;
            } else if ((c >= 243 && c <= 245) || (c >= 211 && c <= 213)) {
                ++abc[14][1];
                ++i;
            } else if (c == 237 || c == 205) {
                ++abc[8][1];
                ++i;
            } else if (c == 250 || c == 218) {
                ++abc[20][1];
                ++i;
            } else if (c == 231 || c == 199) {
                ++abc[2][1];
                ++i;
            }else if (c == 233 || c == 234 || c == 201 || c == 202) {
                ++abc[4][1];
                ++i;
            }
            c=(int)getc(arq); 
        }       
    }
    fclose(arq);

    printf("Número de letras no ficheiro: %d\n", i);
    
    for(j=0;j<26;j++){
        abc[j][0] = j + 97;
        printf("Letra %c = %.2f%%\n",(char)abc[j][0],(float)abc[j][1])*100/i);
    }
    return 0;
}