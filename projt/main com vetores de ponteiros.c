#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "clista.h"
#include "quicksort.h"
/**se quiser pode tirar o include "quicksort.h" não usei no codigo**/

/**função que lê as strings e aloca espaço de acordo com o tamanho dinâmicamente**/

char* unlimited_scanf(){
    int i;
    char c, *text;

    text = (char*) malloc(sizeof(char) + 1);
    printf(" Digite uma string: ");
    for( i = 0; (c = getchar()) != '\n' && c!= EOF && c != '\0'; i++){

    text[i] = c;
    text = (char*) realloc(text, strlen(text)+ sizeof(char));
    }
    text[i] = '\0';
    return text;
}

/**função que utiliza o método de ordenação quick_sort que já tem na stdlib.h para ordenar o vetor de ponteiros para string**/
int comp(const void *a, const void *b) {
  a = *(char **)a;
  b = *(char **)b;
  return strcmp(a, b);
  //return strcmp(*(const char**)a, *(const char**)b);
}

/**função que divide as strings das pontes em duas, procurando o espaço entre as palavras**/
void divide_array(char** string_array, char** pontes_separadas, int tam)
{
    int i,j,k,size_array,z=0,y=0;
    for(i=0;i<tam;i++)
    {
        size_array=strlen(string_array[i]);

        //acha onde esta o espaço na string
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

int main()
{
    char **string_array=NULL,**pontes_separadas=NULL;
    int bridges,i;
    //clista *lista;
    //lista *lista_de_lista;
    printf(" Please, tell us the number of bridges: ");
    scanf("%d", &bridges);
    getchar();

    /**inicializa vetor de ponteiros para string com as pontes da entrada**/
    string_array=(char **)malloc(bridges*sizeof(char*));

    /**inicializa vetor de ponteiros para strings das pontes que vão ser separadas**/
    pontes_separadas=(char **)malloc((2*bridges)*sizeof(char*));

    /**preenche vetor de ponteiros para strings com as pontes da entrada**/
    for(i=0;i<bridges;i++)
    {
        string_array[i]=unlimited_scanf();
    }

    /**Ordena o vetor de strings de acordo com a lexicografia**/
    qsort(string_array,bridges,sizeof(char*),&comp);

    /**Função que divide a struct procurando os espaços, vai formar uma struct com o dobro do tamanho
    por exemplo: na entrada eu escrevo "bat_cave minor_island" essa função vai dividir em:
    bat_cave na primeira posição e minor_island na segunda posição, isso no vetor pontes_separadas**/
    divide_array(string_array, pontes_separadas, bridges);

    printf("\nEssa eh a string sem ser separada:---------");
    for(i=0;i<bridges;i++)
    {
        printf("\n%s", string_array[i]);
    }
    printf("\n\nEssa eh a string separada:--------");
    for(i=0;i<(bridges*2);i++)
    {
        printf("\n%s", pontes_separadas[i]);
    }

    /**comentei seu codigo, não modifiquei nada**/
    /*for( i = 0; i < (2*bridges); i++ ){
      init1(lista_de_lista);
      init(lista);

      inserir1(lista_de_lista, lista);
      inserir( lista, lerstring());

    }
    for( i=0;i< (2*bridges);i++){

       printf("%s \n",lista_de_lista->endereco->chave );

    }*/


    /**libera as strings e o vetor de ponteiros para essas strings**/
    for(i=0;i<bridges;i++)
        free(string_array[i]);
    for(i=0;i<(bridges*2);i++)
        free(pontes_separadas[i]);

    free(pontes_separadas);
    free(string_array);

    return 0;
}
