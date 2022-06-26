#include "hashlist.h"

short HshListVerify(HshList list) {
    return (list.first == list.last);
}

void HshListCreate(HshList *list)
{ list->first = (HshCellAp)malloc(sizeof(HshCell));
    list->last = list->first;
    list->first->prox = NULL;
}

void HshListPrint(HshList list){
    HshCellAp Aux;
    Aux = list.first->prox;
    while (Aux != NULL)
    {
        printf("\n\t\t\t>> %.*s >> \t", N, Aux->palavra);
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

HshCellAp FindQntPalavra(Palavra palavra, HshList list)
{
    HshCellAp Aux;
    Aux = list.first->prox;

    while (Aux != NULL)
    {
        if (strcmp(Aux->palavra, palavra) == 0) {
            return Aux->qnt;
        }
        Aux = Aux -> prox;
    }
    return NULL;
}

int qntDocHaveTermHash(int idDoc,HshList list,Palavra palavra){
    int contador = 0;
    HshCellAp aux;
    for(int i = 1,i<=idDoc,i++){
        InvListAp p = FindIdDoc(i, *list);
        aux = FindPalavra(palavra, p);
        if(aux != NULL){
            contador++;
        }
    }
    return contador;
}