#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

typedef struct Cell *InvListAp;

typedef struct Cell {
  int idDoc;
  int qnt;
  InvListAp prox;
} Cell;

typedef struct {
  InvListAp first, last;
} InvIndexList;


void InvIndexCreateList(InvIndexList *list);

void InvIndexAdd(int idDoc, InvIndexList *list);

void InvIndexPrint(InvIndexList lista);

Cell* FindIdDoc(int idDoc, Cell *cell);