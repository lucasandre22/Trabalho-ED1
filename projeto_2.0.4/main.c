#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "id.h"
#include "vet_listas.h"
#include "clista.h"


char* lerstring(){
    int i;
    char c, *text;

    text = (char*) malloc(sizeof(char) + 1);
    for( i = 0; (c = getchar()) != '\n' && c!= EOF && c != '\0' && c != ' '; i++){

    text[i] = c;
    text = (char*) realloc(text, strlen(text)+ sizeof(char));
    }
    text[i] = '\0';

    return text;
}

int main(){

  char ** vet_id,**vet_localidades,**vet_localidades_ordenado;
  int tam_vet_id,i, pontes, *vet_localidades_com_id;
  clista *vet;

  printf(" Numero de pontes: ");
  scanf("%d", &pontes);
  getchar();

  vet_id = (char **) malloc( sizeof(char*));   /*inicializa o vetor que guardara as localidades diferente sendo sua possição i o id para essa localidade. OBS sera realocado depois*/
  vet_localidades = (char **)malloc((2 * pontes) * sizeof(char*));
  vet_localidades_ordenado = (char **)malloc((2*pontes)*sizeof(char*));
  vet_localidades_com_id = (int *) malloc((2 * pontes) * sizeof(int));


  printf(" Digite uma string: \n");
  for(i = 0; i < 2 * pontes;i++){
      vet_localidades[i] = lerstring();
      vet_localidades_ordenado[i] = vet_localidades[i];
  }
  qsort( vet_localidades_ordenado, 2*pontes, sizeof(char*), &comp ); /*ordenara o vet_string_ordenado*/
  vet_id = preenche_vet_id(vet_localidades_ordenado, pontes, &tam_vet_id);  /*gero o vetor de id a partir de vet_localidades_ordenado, sendo o vet_id o vetor com as localidades de cada problema*/
  /* alocarei o vetor de listas */
  vet = (clista*) malloc(tam_vet_id * sizeof(clista));

  add_id_nas_localidades( vet_localidades,vet_localidades_com_id, pontes, vet_id, tam_vet_id);

  /*printf("\n vet_localidades\n");
  for(int i = 0; i < 2*pontes; i++) printf("%s  ", vet_localidades[i]);
  printf("\n vet_id\n");
  for(int i = 0; i < tam_vet_id; i++) printf("%s  ", vet_id[i]);
  printf("\n vet_localidades_com_id\n");
  for(int i = 0; i < 2*pontes; i++) printf("%d  ", vet_localidades_com_id[i]);*/

/*  MANIPULAÇÕES PARA MONTAR O VETOR DE LISTAS PARA CADA LOCALIDADE    */
  init_vetor_de_listas( vet, tam_vet_id);
  monta_vetor_de_listas( vet,tam_vet_id, vet_localidades_com_id, 2*pontes );
  mostra_lista(vet, tam_vet_id);
}
