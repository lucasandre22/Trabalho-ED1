#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "clista.h"
#include "monta_caminho.h"

/**Função que monta um vetor de caminhos, cada posição deste vetor é um passeio
completo, então é verificado se é possível fazer uma conexão entre eles, caso não
seja o problema não tem solução. Caso tenha solução, o caminho final é armazenado
na primeira posição do vetor_lista_caminhos.**/
void monta_caminho(clista *vetor_lista_localidades, int tam_vet_id, char** vet_id)
{
    int posicao_lista,i,k,tamanho_vetor_caminhos=0,aux=1,primeira_vez,tem_solucao=1;
    no **ponteiros,*proximo_ponteiros=NULL,*proximo_temp=NULL,*temp=NULL;

    clista *vetor_lista_caminhos=(clista*)malloc(sizeof(clista));
    ponteiros=(no**)malloc(tam_vet_id*sizeof(no*));
    /*Vetor de ponteiros para os diferentes nós do caminho, para poder fazer o merge das listas*/
    for(i=0; i<tam_vet_id; i++)
        ponteiros[i]=NULL;
    init(&vetor_lista_caminhos[tamanho_vetor_caminhos]);
    /*monta vetor de listas contendo os passeios, precisamos então após, fazer o merge entre as listas.*/
    for(k=0; k<tam_vet_id; k++)
    {
        i=k;
        primeira_vez=1;
        /*Monta o passeio correspondente, caso a lista não apontar para NULL.*/
        while(vetor_lista_localidades[k].cabesalho!=NULL)
        {
            /*Da realloc no vetor de caminhos.*/
            if(k>0 && primeira_vez==1)
            {
                /*Aux representa o tamanho do vetor_lista_caminhos + 1, para realizar o realloc.*/
                aux++;
                tamanho_vetor_caminhos++;
                vetor_lista_caminhos=(clista*)realloc(vetor_lista_caminhos,aux*sizeof(clista));
                init(&vetor_lista_caminhos[tamanho_vetor_caminhos]);
                primeira_vez=0;
            }
            posicao_lista=vetor_lista_localidades[i].cabesalho->chave;
            inserir(&vetor_lista_caminhos[tamanho_vetor_caminhos], posicao_lista);
            /*Aponta os ponteiros para os nos do primeiro caminho, armazenando esses ponteiros no vetor ponteiros.*/
            if(k==0)
                ponteiros[vetor_lista_caminhos[tamanho_vetor_caminhos].cabesalho->chave]=vetor_lista_caminhos[tamanho_vetor_caminhos].cabesalho;
            else
            {
                /*Se eles compartilham uma mesma localidade, temp vai apontar para esta localidade compartilhada no passeio que estou montando.*/
                if(ponteiros[vetor_lista_caminhos[tamanho_vetor_caminhos].cabesalho->chave]!=NULL && temp==NULL)
                    temp=vetor_lista_caminhos[tamanho_vetor_caminhos].cabesalho;
            }
            /*Remove o no respectivo na outra localidade.*/
            remover_no(&vetor_lista_localidades[posicao_lista],vetor_lista_localidades[i].cabesalho->respectivo);
            /*Remove o primeiro no da localidade.*/
            remover_no(&vetor_lista_localidades[i],vetor_lista_localidades[i].cabesalho);
            i=posicao_lista;
        }
        if(k>0 && primeira_vez==0)
        {
            if(temp==NULL)/*Se não houver localidades em comum nos 2 passeios, o programa para porque nao tem solução!*/
            {
                tem_solucao=0;
                break;
            }
            else/*Faz o merge das listas, utilizando ponteiros para os nodes, caso houver localidades em comum.*/
            {
                proximo_temp=temp->proximo;
		proximo_temp->anterior=ponteiros[temp->chave];
		proximo_ponteiros=ponteiros[temp->chave]->proximo;
		ponteiros[temp->chave]->proximo=proximo_temp;
		temp->proximo=proximo_ponteiros;
		proximo_ponteiros->anterior=temp;
            }
            temp=NULL;
        }
    }
    /*Se não tiver solução, temos que liberar o vetor caminhos individualmente porque os caminhos não se conectam.*/
    if(tem_solucao==0)
    {
	/*Libero a primeira posição do vetor de caminhos, que contem o passeio principal e também libero o passeio que não possui conexão, no caso está na última posição deste vetor de caminhos*/
        printf("Why so serious?");
        for(i=0;i<tam_vet_id;i++)
            liberar(&vetor_lista_localidades[i]);
	liberar(&vetor_lista_caminhos[0]);
	liberar(&vetor_lista_caminhos[tamanho_vetor_caminhos]);
    }
    else/*Posso mandar imprimir o caminho final na primeira posicao do vetor de lista caminhos, por ser mais prático.*/
    {
        escreve_caminho(&vetor_lista_caminhos[0],vet_id,tam_vet_id);
        liberar(&vetor_lista_caminhos[0]);
    }
    free(vetor_lista_caminhos);
    free(ponteiros);
}

/**Função que procura bat_cave no vetor contendo o caminho final e começa a printar a partir dele.**/
void escreve_caminho(clista *l, char** vet_id, int tam_vet_id)
{
    char bat_cave[9]="bat_cave";
    no *u,*aux;
    bat_cave[8]='\0';
    /*Acha posição no vetor_id correspondente a bat_cave, o nó "u" estará apontando para ele.*/
    for(u=l->cabesalho; u; u=u->proximo)
        if(strcmp(vet_id[u->chave],bat_cave)==0)
            break;
    aux=u;
    printf("%s", vet_id[u->chave]);
    for(u=u->proximo; u != aux ; u=u->proximo)
        printf("\n%s", vet_id[u->chave]);
    printf("\n%s", vet_id[aux->chave]);
}

/**Função que conta o número de nodes no vetor de cada localidade, se conter número ímpar de pontes
em alguma delas, ele para e retorna esse número, caso contrário retorna um número par**/
int verifica_solucao(clista *vetor_lista_localidades, int tam)
{
    int i,quantidade_pontes_cada_localidade=0;
    for(i=0; i<tam; i++)
    {
        quantidade_pontes_cada_localidade=conta_no(&vetor_lista_localidades[i]);
        if(quantidade_pontes_cada_localidade%2==1)
            break;
    }
    return quantidade_pontes_cada_localidade;
}
