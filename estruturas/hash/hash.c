#include "hash.h"

void HshTableGeraPesos(Pesos p){
	int i, j;
	struct timeval semente;

	gettimeofday(&semente, NULL); 
	srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
	
	for (i = 0; i < N; i++) {
		for (j = 0; j < TAMALFABETO; j++) {
			p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
		}
	}
}

int h(Palavra palavra, Pesos p){ int i; unsigned int Soma = 0;
	int comp = strlen(palavra);
	for (i = 0; i < comp; i++) {
		Soma += p[i][(unsigned int)palavra[i]];
	}
	return (Soma % M);
}

void HshTableCreate(HashTable t){
    int i;
    for (i = 0; i < M; i++) HshListCreate(&t[i]);
}

HshCellAp HshTableSearch(Palavra palavra, Pesos p, HashTable t) {
	int i;
	HshCellAp Ap;
	i = h(palavra, p);
	if (HshListVerify(t[i])) {
        return NULL;
    }
	else {
        Ap = t[i].first;
		while (Ap->prox->prox != NULL && strncmp(palavra, Ap->prox->palavra, sizeof(Palavra))) {
            Ap = Ap->prox;
        }
		if (!strncmp(palavra, Ap->prox->palavra, sizeof(Palavra))) {
            return Ap;
        } else {
            return NULL;
        }
	}
}  

void HshTableInsert(Palavra palavra, int idDoc, Pesos peso, HashTable t)
{ 
	if (HshTableSearch(palavra, peso, t) == NULL) {
		HshListInsert(palavra, &t[h(palavra, peso)],idDoc);
	} else {
		InvIndexAdd(idDoc, FindPalavra(palavra, t[h(palavra, peso)])->invIndexList);
	}
				
} 

void HshTablePrint(HashTable Tabela){ 
	int i;
	for (i = 0; i < M; i++) 
		{
			if (!HshListVerify(Tabela[i])) {
                HshListPrint(Tabela[i]);
            }
		}
} 

