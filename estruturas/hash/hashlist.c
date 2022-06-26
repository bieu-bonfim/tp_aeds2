#include "hashlist.h"

short HshListVerify(HshList Lista) {
    return (Lista.first == Lista.last);
}

void HshListCreate(HshList *Lista)
{ Lista->first = (HshCellAp)malloc(sizeof(HshCell));
    Lista->last = Lista->first;
    Lista->first->prox = NULL;
}

void HshListPrint(HshList Lista){
    HshCellAp Aux;
    Aux = Lista.first->prox;
    while (Aux != NULL)
    {
        printf("%.*s ", N, Aux->palavra);
        InvIndexPrint(*Aux->invIndexList);
        Aux = Aux->prox;
    }
}

void HshListInsert(Palavra palavra, HshList *list,int idDoc) { 
    list->last->prox = (HshCellAp)malloc(sizeof(HshCell));
    list->last = list->last->prox;
    strcpy(list->last->palavra, palavra);
    list->last->prox = NULL;
    list->last->invIndexList = (InvIndexList*) malloc(sizeof (InvIndexList));
    InvIndexCreateList(list->last->invIndexList);
    InvIndexAdd(idDoc, list->last->invIndexList);
}

HshCellAp FindPalavra(Palavra palavra, HshList list)
{
    HshCellAp Aux;
    Aux = list.first->prox;

    while (Aux != NULL)
    {
        if (strcmp(Aux->palavra, palavra) == 0) {
            return Aux;
        }
        Aux = Aux -> prox;
    }
    return NULL;
}