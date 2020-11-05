 
#ifndef _PROBLEMA
#define _PROBLEMA

void acha_bat_cave( clista* vet, clista *caminho, int pontes, int *aux);

int conta_num_bat_caves( clista *vet, int ponte);

void monta_caminho(clista* vet, clista* caminho, int pontes, int *aux, int num_bat_caves);

void verifica_se_tem_solucao(clista *caminho);

void add_na_lista(clista *vet , char **pontes_separadas, int pontes );

#endif

