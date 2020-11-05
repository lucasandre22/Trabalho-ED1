#include "clista.h"
#include <stdio.h>
#include <stdlib.h>

void init(clista *l)
{
    l->cabesalho = NULL;
}

no* inserir(clista *l, int chave)
{
    no *u = malloc(sizeof(no));
    if(!u)
        return NULL;
    u->chave = chave;
    if( l->cabesalho == NULL)
    {
        l->cabesalho = u;
        u->anterior = u;
        u->proximo = u;
        return u;
    }
    u->proximo = l->cabesalho;
    u->anterior = l->cabesalho->anterior;
    u->anterior->proximo  = u;
    l->cabesalho->anterior = u;
    l->cabesalho = u;

    return u;
}

int conta_no( clista *l )
{
    no *u = l->cabesalho, *aux = u;
    int quantidade_nos=1;
    for(u=u->proximo; u != aux ; u=u->proximo)
    {
        quantidade_nos++;
    }
    return quantidade_nos;
}

void remover_no(clista *l, no *u)
{
    if (u == l->cabesalho)
    {
        if (u->proximo == u)
            l->cabesalho = NULL;
        else
            l->cabesalho = u->proximo;
    }
    u->anterior->proximo = u->proximo;
    u->proximo->anterior = u->anterior;
    free(u);
}

void liberar(clista *l)
{
    no *u, *aux;
    if(l!=NULL && l->cabesalho!=NULL)
    {
        u=l->cabesalho->proximo;
        while(l->cabesalho!=u)
        {
            aux=u;
            u=u->proximo;
            free(aux);
        }
        free(l->cabesalho);
        l->cabesalho=NULL;
    }
}
