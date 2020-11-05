#ifndef _MAPEAMENTO_LOCALIDES
#define _MAPEAMENTO_LOCALIDADES

int comp(const void *a, const void *b);

char** preenche_vet_id(char** vet_localidades_ordenado,int pontes, int *tam_vet_id);

int busca_binaria( char**  vet_id,char* localidade,int n);

void add_id_nas_localidades(char** vet_localidades,int* vet_localidades_com_id,int pontes,char** vet_id,int tam_vet_id);

#endif
