#include "clista.h"
#include <stdio.h>
#include <stdlib.h>

void init(clista *l){
  l->cabesalho = NULL;
}

no* inserir(clista *l , int chave){
    no *u = malloc(sizeof(no));
    if(!u) return NULL;

    u->chave = chave;
    if( l->cabesalho == NULL){
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

no *busca(clista *l, int chave){
  no *u = l->cabesalho;

  for(u ;u && u->chave != chave; u=u->proximo);

  if(u->chave != chave ) return NULL;

  return u;
}

void escrever( clista *l){
  no *u = l->cabesalho, *aux = u;

  printf("  %d", u->chave);

  u = u->proximo;
  for(u; u != aux; u = u->proximo ){
    printf(" %d", u->chave);
  }
  printf("\n");
}

void remover(clista *l, int chave){
   no *u , *ant = u, *prox, *aux = l->cabesalho;

  u = l->cabesalho;
  if(u->chave == chave) l->cabesalho = u->proximo;

  else{

	for(u = u ->proximo ; u != aux && u->chave != chave; u = u->proximo); //aux para saber quando percorri todos os elementos da da lista
  }
  if(!u) return;
  if(u->chave == chave){
	ant = u->anterior;
	prox = u->proximo;

	  ant->proximo = prox;
	  prox->anterior = ant;
  }
  free(u);
}

void liberar(clista *l){
  no *u = l->cabesalho, *aux;
  for(u; u; u = aux){
    aux = u->proximo;
    free(u);
  }

  l->cabesalho = NULL;
}
