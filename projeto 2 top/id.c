#include <stdlib.h>
#include <malloc.h>
#include <string.h>



int comp(const void *a, const void *b)
{
    a = *(char **)a;
    b = *(char **)b;
    return strcmp(a, b);
}

/**Função que faz a lista de localidades ordenado, cada localidade aparece uma vez**/
char** preenche_vet_id(char** vet_localidades_ordenado,int pontes, int *tam_vet_id)
{
    int k = 0, i=0;
    *tam_vet_id = 0;
    char ** vet_id = (char**)malloc(sizeof(char*));

    vet_id[k] = vet_localidades_ordenado[i]; /*adiciono o primeiro elemento no vetor*/

    for(i ; i < (2*pontes)-1; i++)
    {
        if(strcmp(vet_localidades_ordenado[i],vet_localidades_ordenado[i+1]) != 0)
        {
            k++;
            vet_id = (char**) realloc(vet_id, (k+1)*sizeof(char*));
            vet_id[k] = vet_localidades_ordenado[i+1];
        }
    }
    *tam_vet_id = k + 1;
    return vet_id;
}

int busca_binaria( char**  vet_id,char* localidade,int n)
{
    int a = 0, b = n-1, indice;

    do
    {
        indice = (a+b)/2;

        if( strcmp(vet_id[indice], localidade) == 0)
            return indice;
        if( strcmp(vet_id[indice], localidade) < 0 )
            a = indice+1;
        else
            b = indice -1 ;

    }
    while( a <= b );
}

void add_id_nas_localidades(char** vet_localidades,int* vet_localidades_com_id,int pontes,char** vet_id,int tam_vet_id)
{
    int i, indice;

    for(i = 0; i < 2*pontes; i++)
    {
        indice = busca_binaria( vet_id, vet_localidades[i], tam_vet_id);
        vet_localidades_com_id[i] = indice;
    }
}
