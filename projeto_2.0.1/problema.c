#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "clista.h"


void acha_bat_cave( clista* vet, clista *caminho, int pontes, int *aux){

   char bat_cave[9] = "bat_cave";
   int i;
   no *u;

   for( i = 0; i < pontes; i++){
	u = busca( &vet[i], bat_cave);
	if( u != NULL){
	  break;
  	}
   }

   if(u != NULL){
	init(caminho);
	inserir(caminho, u->chave);
        inserir(caminho, u->proximo->chave);
        liberar(&vet[i]);
	*aux += -1;  		/*zoado#$#*/
   }
}

int conta_num_bat_caves( clista *vet, int ponte){
   char bat_cave[9] = "bat_cave";
   int bat_caves = 0;

   for(int i =0; i < ponte; i++){
      if(vet[i].cabesalho != NULL){
	if ( busca( &vet[i], bat_cave) != NULL)
       	   bat_caves++;
      }
   }
   return bat_caves;
}


void monta_caminho(clista* vet, clista* caminho, int pontes, int *aux, int num_bat_caves){
   char bat_cave[9] = "bat_cave";
   int i;
   no *u;

   while((*aux) > 0){
	   for( i = 0; i < pontes; i++){


	   	if(vet[i].cabesalho != NULL){
			u = busca( &vet[i], caminho->cabesalho->chave);
			if( u != NULL && busca( &vet[i], bat_cave) == NULL || u != NULL && *aux <= num_bat_caves){
			  break;
		  	}
		}
	   }
	   if(u != NULL){

		inserir(caminho, u->proximo->chave);
		*aux += -1;  /*zoado*/
		liberar(&vet[i]);
	   }
	   else
		break;
   }
}

void verifica_se_tem_solucao(clista *caminho){
   no* u = caminho->cabesalho;

   if( strcmp(u->chave, u->anterior->chave) == 0)
	escrever(caminho);
   else{
        printf("\n Why so serious?  :)\n");
   	escrever(caminho);
   }

}

void add_na_lista(clista *vet , char **pontes_separadas, int pontes ){
   int aux = 0;

   for(int i = 0; i < pontes; i++){
	inserir( &vet[i], pontes_separadas[aux]);
	aux++;
	inserir( &vet[i], pontes_separadas[aux]);
	aux++;
   }
}
