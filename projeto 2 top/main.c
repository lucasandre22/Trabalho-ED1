#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "id.h"
#include "vet_listas.h"
#include "clista.h"

/**Fun��o que l� a entrada sem limite**/
char* lerstring()
{
    int i;
    char c, *text;

    text = (char*) malloc(sizeof(char) + 1);
    for( i = 0; (c = getchar()) != '\n' && c!= EOF && c != '\0' && c != ' '; i++)
    {
        text[i] = c;
        text = (char*) realloc(text, strlen(text)+ sizeof(char));
    }
    text[i] = '\0';

    return text;
}

/**Fun��o que conta o n�mero de nodes no vetor de cada localidade, se conter n�mero �mpar de pontes
em alguma delas, ele para e retorna esse n�mero, caso contr�rio retorna um n�mero par**/
int verifica_solucao(clista *vetor_lista_localidades, int tam)
{
    int i,quantidade_pontes_cada_localidade;
    for(i=0; i<tam; i++)
    {
        quantidade_pontes_cada_localidade=conta_no(&vetor_lista_localidades[i]);
        if(quantidade_pontes_cada_localidade%2==1)
            break;
    }
    return quantidade_pontes_cada_localidade;
}

/**Fun��o que procura bat_cave no vetor contendo o caminho final e come�a a printar a partir dele.**/
void escreve_caminho(clista *l, char** vet_id, int tam_vet_id)
{
    char bat_cave[9]="bat_cave";
    no *u,*aux;
    bat_cave[8]='\0';
    //Acha posi��o no vetor_id correspondente a bat_cave, o n� "u" estar� apontando para ele.
    for(u=l->cabesalho; u; u=u->proximo)
        if(strcmp(vet_id[u->chave],bat_cave)==0)
            break;
    aux=u;
    printf("\n%s", vet_id[u->chave]);
    for(u=u->proximo; u != aux ; u=u->proximo)
        printf("\n%s", vet_id[u->chave]);
    printf("\n%s", vet_id[aux->chave]);
}

void monta_caminho(clista *vetor_lista_localidades, int tam_vet_id, char** vet_id)
{
    int posicao_lista,i,k,tamanho_vetor_caminhos=0,aux=1,primeira_vez=0,tem_solucao=1;
    no **ponteiros,*proximo_ponteiros,*anterior_temp,*temp=NULL;

    clista *vetor_lista_caminhos=(clista*)malloc(sizeof(clista));
    ponteiros=(no**)malloc(tam_vet_id*sizeof(no*));
    for(i=0; i<tam_vet_id; i++)
        ponteiros[i]=NULL;
    init(&vetor_lista_caminhos[tamanho_vetor_caminhos]);
    //monta vetor de listas contendo os passeios, precisamos ent�o ap�s, fazer o merge entre as listas.
    for(k=0; k<tam_vet_id; k++)
    {
        i=k;
        primeira_vez=1;
        //Monta o passeio correspondente, caso a lista n�o apontar para NULL.
        while(vetor_lista_localidades[k].cabesalho!=NULL)
        {
            //Da realloc no vetor de caminhos.
            if(k>0 && primeira_vez==1)
            {
                //Aux representa o tamanho do vetor_lista_caminhos + 1, para realizar o realloc.
                aux++;
                tamanho_vetor_caminhos++;
                vetor_lista_caminhos=(clista*)realloc(vetor_lista_caminhos,aux*sizeof(clista));
                init(&vetor_lista_caminhos[tamanho_vetor_caminhos]);
                primeira_vez=0;
            }
            posicao_lista=vetor_lista_localidades[i].cabesalho->chave;
            inserir(&vetor_lista_caminhos[tamanho_vetor_caminhos], posicao_lista);
            //Aponta os ponteiros para os nos do primeiro caminho, armazenando esses ponteiros no vetor ponteiros.
            if(k==0)
                ponteiros[vetor_lista_caminhos[tamanho_vetor_caminhos].cabesalho->chave]=vetor_lista_caminhos[tamanho_vetor_caminhos].cabesalho;
            else
            {
                //Se eles compartilham uma mesma localidade, temp vai apontar para esta localidade compartilhada no passeio que estou montando.
                if(ponteiros[vetor_lista_caminhos[tamanho_vetor_caminhos].cabesalho->chave]!=NULL)
                    temp=vetor_lista_caminhos[tamanho_vetor_caminhos].cabesalho;
            }
            //Remove o no respectivo na outra localidade.
            remover_no(&vetor_lista_localidades[posicao_lista],vetor_lista_localidades[i].cabesalho->respectivo);
            //Remove o primeiro no da localidade.
            remover_no(&vetor_lista_localidades[i],vetor_lista_localidades[i].cabesalho);
            i=posicao_lista;
        }
        if(k>0 && primeira_vez==0)
        {
            if(temp==NULL)//Se n�o houver localidades em comum nos 2 passeios, o programa para porque nao tem solu��o!
            {
                tem_solucao=0;
                break;
            }
            else//Faz o merge das listas caso houver localidades em comum.
            {
                anterior_temp=temp->anterior;
                proximo_ponteiros=ponteiros[temp->chave]->proximo;
                ponteiros[temp->chave]->proximo=temp->anterior;
                anterior_temp->anterior=ponteiros[temp->chave];
                proximo_ponteiros->anterior=temp;
                temp->proximo=proximo_ponteiros;
            }
            temp=NULL;
        }
    }
    //O caminho final ficou na primeira posicao do vetor de caminhos, por ser mais pr�tico.
    if(tem_solucao==0)
        printf("Why so serious?");
    else
    {
        //escrever(&vetor_lista_caminhos[0]);
        escreve_caminho(&vetor_lista_caminhos[0],vet_id,tam_vet_id);
    }
    //mapeamento free da fun��o monta_caminho
}
//void free_listas()

//void free_vetores_int()

void free_strings(char* string)
{
    if(string==NULL)
        return;
    else
        free(string);
}

int main()
{

    char **vet_id, **vet_localidades, **vet_localidades_ordenado;
    int tam_vet_id,i, pontes, *vet_localidades_com_id, quantidade_pontes_cada_localidade;
    clista *vetor_lista_localidades;

    printf("How many bridges does Gotham City have?\n");
    scanf("%d", &pontes);
    getchar();

    /**vet id conter� todas as localidades diferentes, em ordem alfab�tica, com seus respectivos ids para o mapeamento.**/
    vet_id = (char **) malloc( sizeof(char*));

    /**vet_localidades contem as strings da entrada.**/
    vet_localidades = (char **)malloc((2 * pontes) * sizeof(char*));

    /**vet_localidades_ordenado ir� apontar para o vet_localidades e ser� ordenado, para podermos fazer o vet_id e assim
    o mapeamento das localidades.**/
    vet_localidades_ordenado = (char **)malloc((2*pontes)*sizeof(char*));

    /**vet_localidades_com_id cont�m o vet_localidades, com as entradas,
    por�m ao inv�s de structs, contem os ids respectivos no vet_id.**/
    vet_localidades_com_id = (int *) malloc((2 * pontes) * sizeof(int));

    for(i = 0; i < 2 * pontes; i++)
    {
        vet_localidades[i] = lerstring();
        vet_localidades_ordenado[i] = vet_localidades[i];
    }

    /**Ordenar� o vetor de listas, contendo as pontes da entrada, isso � necess�rio para montarmos outro vetor
    contendo todas as localidades em ordem alfab�tica, para em seguida fazermos o mapeamento de cada localidade**/
    qsort( vet_localidades_ordenado, 2*pontes, sizeof(char*), &comp );

    /**� gerado o vetor de id a partir de vet_localidades_ordenado, sendo o vet_id o vetor com as localidades de cada problema**/
    vet_id = preenche_vet_id(vet_localidades_ordenado, pontes, &tam_vet_id);

    /**Aloca��o do vetor de listas de cada localidade, que ir� contem os �ndices correspondentes a cada localidade, **/
    vetor_lista_localidades = (clista*) malloc(tam_vet_id * sizeof(clista));

    add_id_nas_localidades(vet_localidades,vet_localidades_com_id,pontes,vet_id,tam_vet_id);

    /**Manipula��es para montar o vetor de listas para cada localidade**/
    init_vetor_de_listas(vetor_lista_localidades,tam_vet_id);
    monta_vetor_de_listas(vetor_lista_localidades,tam_vet_id,vet_localidades_com_id,2*pontes);

    /**Verifica se tem solu��o, contando os nodes de cada localidade, se houver
    n�mero �mpar, ele para de contar e retorna o valor �mpar de nodes**/
    quantidade_pontes_cada_localidade=verifica_solucao(vetor_lista_localidades, tam_vet_id);

    if(quantidade_pontes_cada_localidade%2==1)
        printf("\nWhy so serious?");
    else
    {
        /**Montamos a lista contendo os passeios e o caminho final na posi��o 0**/
        monta_caminho(vetor_lista_localidades, tam_vet_id, vet_id);
    }

    /** Mapeamento do free do programa **/







    return 0;
}
