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

no *busca(clista *l, int chave)
{
    no *u = l->cabesalho;

    for(u ; u && u->chave != chave; u=u->proximo);

    if(u->chave != chave )
        return NULL;

    return u;
}

void escrever(clista *l)
{
    no *u = l->cabesalho, *aux = u;

    printf("  %d", u->chave);

    u = u->proximo;
    for(u; u != aux; u = u->proximo )
    {
        printf(" %d", u->chave);
    }
    printf("\n");
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

void remover(clista *l, int key)
{
    no *u = l->cabesalho;
    int start = 1;
    while (u && (u != l->cabesalho || start) && u->chave != key)
    {
        start = 0;
        u = u->proximo;
    }
    if (!u)
        return;
    if (u == l->cabesalho)
    {
        if (!start)
            return;
        if (u->proximo == u)
            l->cabesalho = NULL;
        else
            l->cabesalho = u->proximo;
    }
    u->anterior->proximo = u->proximo;
    u->proximo->anterior = u->anterior;
    free(u);
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
    u=l->cabesalho;
    if(l!=NULL && l->cabesalho!=NULL)
    {
        while(l->cabesalho!=u->anterior)
        {
            aux=u;
            u=u->proximo;
            free(aux);
        }
    }
    else
        return;
}
