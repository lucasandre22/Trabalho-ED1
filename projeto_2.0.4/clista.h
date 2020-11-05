#ifndef _CLISTA
#define _CLISTA

typedef struct _no {
  int chave;
  struct _no *proximo, *anterior, *respectivo;  /*respectivo é a variavel que guardara a possição da respectiva ponte de outra localidade*/
} no;

typedef struct {
  no *cabesalho;
} clista;

void init(clista *l);

no* inserir(clista *l , int chave);

no *busca(clista *l, int chave);

void escrever( clista *l);

void remover(clista *l, int chave);

void liberar(clista *l);

#endif
