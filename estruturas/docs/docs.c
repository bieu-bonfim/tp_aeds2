#include "docs.h"

void DocCreateList(DocList *list) {
    list -> first = (DocListAp) malloc(sizeof(DocCell));
    list -> last = list -> first;
    list -> first -> prox = NULL;
}

void DocDeleteList(DocList *list)
{

    DocListAp Aux, Aux2;
    Aux = list -> first -> prox;

    while (Aux != NULL)
    {
        Aux2 = Aux->prox;
        free(Aux);
        Aux = Aux2;
    }

    free(list -> first);

}

short DocListVerify(DocList list) {
    return (list.first == list.last);
}

void DocAdd(int idDoc, Palavra docName, DocList *list) {
    list -> last -> prox = (DocListAp) malloc(sizeof(DocCell));
    list -> last = list -> last -> prox;
    list -> last -> idDoc = idDoc;
    strcpy(list -> last -> docName, docName);
    list -> last -> qntPalavras = 0;
    list -> last -> prox = NULL;
}

void DocPrint(DocList list) {
    DocListAp Aux;
    Aux = list.first -> prox;
    while (Aux != NULL)
    {
        printf("\n\t\t\t>> Documento %d: %s", Aux->idDoc, Aux->docName);
        Aux = Aux -> prox;
    }
}

DocListAp FindDoc(int idDoc, DocList list)
{
    DocListAp Aux;
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
