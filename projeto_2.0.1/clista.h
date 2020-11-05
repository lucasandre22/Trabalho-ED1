#ifndef _CLISTA
#define _CLISTA

typedef struct _no {
  char* chave;
  struct _no *proximo, *anterior;
} no;

typedef struct {
  no *cabesalho;
} clista;

void init(clista *l);

int inserir(clista *l , char* chave);

no *busca(clista *l, char* chave);

void escrever( clista *l);

void remover(clista *l, char chave);

void liberar(clista *l);

#endif
