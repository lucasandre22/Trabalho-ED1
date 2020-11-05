#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "clista.h"
#include "problema.h"


char* lerstring(){
    int i;
    char c, *text;

    text = (char*) malloc(sizeof(char) + 1);
    for( i = 0; (c = getchar()) != '\n' && c!= EOF && c != '\0'; i++){

    text[i] = c;
    text = (char*) realloc(text, strlen(text)+ sizeof(char));
    }
    text[i] = '\0';

    return text;
}

int comp(const void *a, const void *b) {
  a = *(char **)a;
  b = *(char **)b;
  return strcmp(a, b);
  /*return strcmp(*(const char**)a, *(const char**)b);*/
}

/**função que divide as strings das pontes em duas, procurando o espaço entre as palavras**/
void divide_array(char** string_array, char** pontes_separadas, int tam)
{
    int i,j,k,size_array,z=0,y=0;
    for(i=0;i<tam;i++)
    {
        size_array=strlen(string_array[i]);

        /*acha onde esta o espaço na string*/
        for(j=0;string_array[i][j]!=' ';j++){}

        /**aloca dinamicamente a primeira parte antes do espaço na string**/
        pontes_separadas[z]=(char*)malloc((j+1)*sizeof(char));
        for(k=0;k<j;k++)
            pontes_separadas[z][k]=string_array[i][k];
        pontes_separadas[z][k]='\0';
        z++;

        /**aloca dinamicamente a segunda parte depois do espaço na string**/
        pontes_separadas[z]=(char*)malloc((size_array-j)*sizeof(char));
        for(k=j+1;k<=size_array;k++)
        {
            pontes_separadas[z][y]=string_array[i][k];
            y++;
        }
        pontes_separadas[z][y]='\0';
        z++;
        y=0;
    }
}

int main(){

    clista *vet, caminho;
    char **vet_char,**pontes_separadas;
    int pontes,i,aux,num_bat_caves;

    printf(" Numero de pontes: ");
    scanf("%d", &pontes);
    getchar();
    aux = pontes;

    /*inicaliza o vetor de clista*/
    vet = (clista*) malloc( pontes * sizeof(clista));
    vet_char = (char **)malloc(pontes * sizeof(char*));
    pontes_separadas=(char **)malloc((2*pontes)*sizeof(char*));

    printf(" Digite uma string: \n");
    for(i = 0; i < pontes;i++){

      init( &vet[i] );  /*inicializa uma nova clista a cada interação do loop*/
      vet_char[i] = lerstring();  /*monta o vetor de strings*/
    }

    /* funções que faram as manipulações necessarias com as strings*/
    qsort(vet_char,pontes,sizeof(char*),&comp);
    divide_array(vet_char, pontes_separadas, pontes);
    add_na_lista( vet , pontes_separadas, pontes );

    /* funções que acharam o caminho se ele exitir*/
    acha_bat_cave( vet, &caminho, pontes, &aux);
    num_bat_caves = conta_num_bat_caves( vet, pontes);
    monta_caminho( vet, &caminho, pontes, &aux, num_bat_caves);

    printf("\n");
    verifica_se_tem_solucao(&caminho);


    return 0;
}
