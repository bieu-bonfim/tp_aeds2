#include "invIndex.h"

void InvIndexCreateList(InvIndexList *list) {
list -> first = (InvListAp) malloc(sizeof(Cell));
list -> last = list -> first;
list -> first -> prox = NULL;
}

void InvIndexAdd(int idDoc, InvIndexList *list) {
  Cell *p = FindIdDoc(idDoc, list->first);
  if (p != NULL) {
    p->qnt = p->qnt + 1;
    return;
  }
  list -> last -> prox = (InvListAp) malloc(sizeof(Cell));
  list -> last = list -> last -> prox;
  list -> last -> idDoc = idDoc;
  list -> last -> qnt = 1;
  list -> last -> prox = NULL;
}

void InvIndexPrint(InvIndexList lista) {
  InvListAp Aux;
    printf("< saa,");

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
  printf("<%d, %d>", cell->qnt, cell->idDoc);
  if (cell == NULL)  return NULL;
  if (cell->idDoc == idDoc)  return cell;
  return FindIdDoc (idDoc, cell->prox);
}