#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define M 11
#define N 12   
#define TAMALFABETO 256

// typedef unsigned int  Pesos[n]; 
typedef char Palavra[64];
typedef char Chave[N];
typedef unsigned Pesos[N][TAMALFABETO];
typedef struct Item {
  // outros componentes 
  Chave Chave;
} Item;

typedef unsigned int TipoIndice;
typedef struct Celula* Apontador;

typedef struct Celula {
  char *conteudo;
  Item Item;
  Apontador Prox;
} Celula;

typedef struct TipoLista {
  Celula *Primeiro, *Ultimo;
} TipoLista;

typedef TipoLista TipoDicionario[M];

TipoDicionario Tabela;
Item Elemento;
Pesos p;
Apontador i;

void FLVazia(TipoLista *Lista);

short Vazia(TipoLista Lista);

void Ins(Palavra palavra, TipoLista *Lista);

void GeraPesos(Pesos p);

TipoIndice h(Palavra palavra, Pesos p);

void Inicializa(TipoDicionario T);

Apontador Pesquisa(Palavra palavra, Pesos p, TipoDicionario T);

void Insere(Palavra palavra, Pesos p, TipoDicionario T);

void Imp(TipoLista Lista);

void Imprime(TipoDicionario Tabela);

void LerPalavra(FILE *arquivo,FILE* arquivo2,char *temp, int Tam);