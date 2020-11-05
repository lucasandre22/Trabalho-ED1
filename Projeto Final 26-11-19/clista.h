#ifndef _CLISTA
#define _CLISTA

typedef struct _no {
  int chave;
  struct _no *proximo, *anterior, *respectivo;  /*respectivo � a variavel que guardara a possi��o da respectiva ponte de outra localidade*/
} no;

typedef struct {
  no *cabesalho;
} clista;

void init(clista *l);

no* inserir(clista *l , int chave);

no *busca(clista *l, int chave);

void escrever( clista *l);

int conta_no( clista *l );

void remover(clista *l, int key);

void remover_no(clista *l, no *u);

void liberar(clista *l);

#endif
