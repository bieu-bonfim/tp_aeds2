#include "invIndex.h"

void InvIndexCreateList(InvIndexList *list) {
    list -> first = (InvListAp) malloc(sizeof(Cell));
    list -> last = list -> first;
    list -> first -> prox = NULL;
}

void InvIndexAdd(int idDoc, InvIndexList *list) {

    InvListAp p = FindIdDoc(idDoc, *list);
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

void InvIndexPrint(InvIndexList list) {
    InvListAp Aux;
    Aux = list.first -> prox;
    while (Aux != NULL)
  {
      printf("< %d,", Aux -> qnt);
    printf("%d >\n", Aux -> idDoc);
    Aux = Aux -> prox;
  }
}

InvListAp FindIdDoc(int idDoc, InvIndexList list)
{
    InvListAp Aux;
    Aux = list.first->prox;

    while (Aux != NULL)
    {
        if (Aux->idDoc == idDoc) {
            return Aux;
        }
        Aux = Aux -> prox;
    }
    return NULL;
}