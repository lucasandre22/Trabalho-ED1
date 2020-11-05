#include "clista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init(clista *l){
  l->cabesalho = NULL;
}

int inserir(clista *l , char *chave){
    no *u = malloc(sizeof(no));
    if(!u) return 0;

    u->chave = chave;
    if( l->cabesalho == NULL){
      l->cabesalho = u;
      u->anterior = u;
      u->proximo = u;
      return 1;
    }

    u->proximo = l->cabesalho;
    u->anterior = l->cabesalho->anterior;
    u->anterior->proximo  = u;
    l->cabesalho->anterior = u;
    l->cabesalho = u;

    return 1;
}

no *busca(clista *l, char *chave){
  no *u = l->cabesalho,*aux = l->cabesalho;

  //talvez precise checar a primeira possição#obs: não o fiz
  if(strcmp(u->chave, chave) == 0) return u;
  for(u = u->proximo ; u != aux && strcmp(u->chave, chave) != 0; u = u->proximo); //aux para saber quando percorri todos os elementos da da lista

  if(strcmp(u->chave, chave) != 0 ) return NULL;

  return u;
}

void escrever( clista *l){
    no *u = l->cabesalho, *aux = u;

    printf("%s", u->chave);

    u = u->proximo;
    for(u; u != aux; u = u->proximo ){
      printf("\n%s", u->chave);
    }
    printf("\n");
}

void liberar(clista *l){
  no *u = l->cabesalho,*proximo;
    free(u);
    for(u = u->proximo; u != l->cabesalho; u = proximo)
    {
        proximo = u->proximo;
        free(u);
    }
    l->cabesalho = NULL;
}

