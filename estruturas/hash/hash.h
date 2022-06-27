#include "hashlist.h"
#define M 29
#define TAMALFABETO 256

typedef unsigned Pesos[N][TAMALFABETO];

typedef HshList HashTable[M];

void HshTableGeraPesos(Pesos p);

int h(Palavra palavra, Pesos p);

void HshTableCreate(HashTable T);

HshCellAp HshTableSearch(Palavra palavra, Pesos p, HashTable T);

void HshTableInsert(Palavra palavra, int idDoc, Pesos peso, HashTable t);

void HshTablePrint(HashTable Tabela);

