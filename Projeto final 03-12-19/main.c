#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "mapeamento_localidades.h"
#include "vet_listas.h"
#include "clista.h"

char *scanf_ilimitado(char *string)
{
    char letter;
    int i;
    string=(char *)malloc(sizeof(char));
    scanf("%c", &letter);
    for(i=0; letter != ' ' && letter != '\n' ;i++)
    {
        string=(char *)realloc(string,(i+2)*sizeof(char));
        string[i]=letter;
        scanf("%c", &letter);
    }
    string[i]='\0';
    return string;
}

int main()
{
    char **vet_id, **vet_localidades, **vet_localidades_ordenado;
    int tam_vet_id,i, pontes, *vet_localidades_com_id, quantidade_pontes_cada_localidade;
    clista *vetor_lista_localidades;

    scanf("%d", &pontes);
    getchar();

    /**vet_localidades contem as strings da entrada.**/
    vet_localidades = (char **)malloc((2 * pontes) * sizeof(char*));

    /**vet_localidades_ordenado ir� apontar para o vet_localidades e ser� ordenado, para podermos
    fazer o vet_id e assim o mapeamento das localidades.**/
    vet_localidades_ordenado = (char **)malloc((2*pontes)*sizeof(char*));

    /**vet_localidades_com_id cont�m o vet_localidades, com as entradas,
    por�m ao inv�s de strings, contem os ids respectivos das localidades no vet_id.**/
    vet_localidades_com_id = (int *) malloc((2 * pontes) * sizeof(int));

    for(i = 0; i < (2*pontes); i++)
    {
        vet_localidades[i] = scanf_ilimitado(vet_localidades[i]);
        vet_localidades_ordenado[i] = vet_localidades[i];
    }

    /**Ordenar� o vetor de strings, contendo as pontes da entrada, isso � necess�rio para montarmos outro vetor
    contendo todas as localidades em ordem alfab�tica, para em seguida fazermos o mapeamento de cada localidade**/
    qsort( vet_localidades_ordenado, 2*pontes, sizeof(char*), &comp );

    /**� gerado o vetor de id a partir de vet_localidades_ordenado, sendo o vet_id o vetor que � feito o mapeamento
    das localidades, cada uma aparece uma vez e ser�o ordenadas em ordem alfab�tica.**/
    vet_id = preenche_vet_id(vet_localidades_ordenado, pontes, &tam_vet_id);

    /**Aloca��o do vetor de listas de cada localidade, que ir� conter todas as localidades, em ordem alfab�tica
    com todas as pontes que incidem sobre ela em forma de nodes.**/
    vetor_lista_localidades = (clista*) malloc(tam_vet_id * sizeof(clista));

    add_id_nas_localidades(vet_localidades,vet_localidades_com_id,pontes,vet_id,tam_vet_id);

    /**Manipula��es para montar o vetor de listas para cada localidade**/
    init_vetor_de_listas(vetor_lista_localidades,tam_vet_id);
    monta_vetor_de_listas(vetor_lista_localidades,tam_vet_id,vet_localidades_com_id,2*pontes);

    /**Verifica se tem solu��o, contando os nodes de cada localidade, se houver
    n�mero �mpar, ele para de contar e retorna o valor �mpar de nodes**/
    quantidade_pontes_cada_localidade=verifica_solucao(vetor_lista_localidades, tam_vet_id);
    if(quantidade_pontes_cada_localidade%2==1)
    {
        printf("Why so serious?");
        for(i=0;i<tam_vet_id;i++)
            liberar(&vetor_lista_localidades[i]);
    }
    else
    {
        /**Montamos a lista contendo os passeios e o caminho final.**/
        monta_caminho(vetor_lista_localidades, tam_vet_id, vet_id);
    }
    /**Mapeamento do free do programa.**/
    for(i=0;i<2*pontes;i++)
        free(vet_localidades[i]);
    free(vet_localidades);
    free(vet_localidades_ordenado);
    free(vet_localidades_com_id);
    free(vetor_lista_localidades);
    free(vet_id);
    return 0;
}
