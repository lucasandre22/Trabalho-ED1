#include "clista.h"
#include <stdio.h>

void init_vetor_de_listas( clista* vet, int ndl){
   int i;

   for(i = 0; i < ndl; i++)
      init(&vet[i]);

}
                                                                              /*tam == 2*numero de pontes*/
void monta_vetor_de_listas(clista* vet,int ndl, int* vet_localidades_com_id,int tam ){  /*ndl numeor de localidades tam o tamanho do vet_localidades_com_id*/
  int i;
  no *u1,*u2;

  for(i = 0; i < (tam-1); i+=2){
    u1 = inserir(&vet[vet_localidades_com_id[i]],vet_localidades_com_id[i+1]);
    u2 = inserir(&vet[vet_localidades_com_id[i+1]],vet_localidades_com_id[i]);
    vet[vet_localidades_com_id[i]].cabesalho->respectivo = u2;
    vet[vet_localidades_com_id[i+1]].cabesalho->respectivo = u1;
  }

}

void mostra_lista(clista *vet, int ndl){
  int i;

  printf("\nVetor de listas de cada localidade");
  for(i = 0; i < ndl; i ++){
    printf("\n");
    escrever(&vet[i]);
  }
}
