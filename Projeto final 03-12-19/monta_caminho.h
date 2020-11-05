#ifndef _MONTA_CAMINHO
#define _MONTA_CAMINHO
#include "clista.h"

void monta_caminho(clista *vetor_lista_localidades, int tam_vet_id, char** vet_id);

void escreve_caminho(clista *l, char** vet_id, int tam_vet_id);

int verifica_solucao(clista *vetor_lista_localidades, int tam);

#endif
