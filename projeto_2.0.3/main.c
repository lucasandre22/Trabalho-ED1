#include <stdlib.h>
#include <malloc.h>
#include <string.h>


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

int comp(const void *a, const void *b) {
  a = *(char **)a;
  b = *(char **)b;
  return strcmp(a, b);
}

char** preenche_vet_id(char** vet_localidades_ordenado,int pontes, int *tam_vet_id){
  int k = 0,i = 0;
  *tam_vet_id = 0;
  char ** vet_id = (char**)malloc(sizeof(char*));

  vet_id[k] = vet_localidades_ordenado[i]; /*adiciono o primeiro elemento no vetor*/

  for(i ; i < (2*pontes)-1; i++){
    if(strcmp(vet_localidades_ordenado[i],vet_localidades_ordenado[i+1]) != 0){
      k++;
      vet_id = (char**) realloc(vet_id, (k+1)*sizeof(char*));
      vet_id[k] = vet_localidades_ordenado[i+1];
    }
  }
  *tam_vet_id = k + 1;
  return vet_id;
}
int busca_binaria( char**  vet_id,char* localidade,int n){
   int a = 0, b = n-1, indice;

   do{
	    indice = (a+b)/2;

    	if( strcmp(vet_id[indice], localidade) == 0) return indice;
    	if( strcmp(vet_id[indice], localidade) < 0 ) a = indice+1;
    	else b = indice -1 ;

   } while( a <= b );
}

void add_id_nas_localidades(char** vet_localidades,int* vet_localidades_com_id,int pontes,char** vet_id,int tam_vet_id){
  int i, indice;

    for(i = 0; i < 2*pontes; i++){
   	indice = busca_binaria( vet_id, vet_localidades[i], tam_vet_id);
          vet_localidades_com_id[i] = indice;
     }
}

int main(){

  char ** vet_id,**vet_localidades,**vet_localidades_ordenado;
  int tam_vet_id,i, pontes, *vet_localidades_com_id;

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

  add_id_nas_localidades( vet_localidades,vet_localidades_com_id, pontes, vet_id, tam_vet_id);

  printf("\n vet_localidades\n");
  for(int i = 0; i < 2*pontes; i++) printf("%s  ", vet_localidades[i]);
  printf("\n vet_id\n");
  for(int i = 0; i < tam_vet_id; i++) printf("%s  ", vet_id[i]);
  printf("\n vet_localidades_com_id\n");
  for(int i = 0; i < 2*pontes; i++) printf("%d  ", vet_localidades_com_id[i]);
}
