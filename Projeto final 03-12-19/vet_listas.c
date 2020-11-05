#include "clista.h"
#include <stdio.h>

void init_vetor_de_listas(clista* vet, int tam_vet_id){
   int i;
   for(i = 0; i < tam_vet_id; i++)
      init(&vet[i]);
}
                                                                              /*tam == 2*numero de pontes*/
void monta_vetor_de_listas(clista* vetor_lista_localidades, int tam_vetor_id, int* vet_localidades_com_id, int tam ){  /*ndl numeor de localidades tam o tamanho do vet_localidades_com_id*/
  int i;
  no *u1,*u2;

  for(i = 0; i < (tam-1); i+=2){
    u1 = inserir(&vetor_lista_localidades[vet_localidades_com_id[i]],vet_localidades_com_id[i+1]);
    u2 = inserir(&vetor_lista_localidades[vet_localidades_com_id[i+1]],vet_localidades_com_id[i]);
    vetor_lista_localidades[vet_localidades_com_id[i]].cabesalho->respectivo = u2;
    vetor_lista_localidades[vet_localidades_com_id[i+1]].cabesalho->respectivo = u1;
  }
}
