#include "invIndex.h"

void CreateInvIndexList(InvIndexList *list) { 
  list -> first = (InvListAp) malloc(sizeof(Cell));
  list -> last = list -> first;
  list -> first -> prox = NULL;
}

void AddInvIndex(int idDoc, InvIndexList *list) { 
  Cell *p = FindIdDoc(idDoc, list->first);
  if (p != NULL) {
    p->qnt++;
    return;
  }
  list -> last -> prox = (InvListAp) malloc(sizeof(Cell));
  list -> last = list -> last -> prox;
  list -> last -> idDoc = idDoc;
  list -> last -> qnt = 1;
  list -> last -> prox = NULL;
}

void Imprime(InvIndexList lista) { 
  InvListAp Aux;
  Aux = lista.first -> prox;
  while (Aux != NULL) 
  { 
    printf("< %d,", Aux -> qnt);
    printf("%d >\n", Aux -> idDoc);
    Aux = Aux -> prox;
  }
}

Cell* FindIdDoc(int idDoc, Cell *cell)
{
  if (cell == NULL)  return NULL;
  if (cell->idDoc == idDoc)  return cell;
  return FindIdDoc (idDoc, cell->prox);
}