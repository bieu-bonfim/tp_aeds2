#include "../includes.h"

typedef struct DocCell *DocListAp;

typedef struct DocCell {
    int idDoc;
    int qntPalavras;
    Palavra docName;
    float relev;
    DocListAp prox;
} DocCell;

typedef struct {
    DocListAp first, last;
} DocList;


void DocCreateList(DocList* list);

void DocDeleteList(DocList *list);

short DocListVerify(DocList list);

void DocAdd(int idDoc, Palavra docName, DocList *list);

void DocPrint(DocList lista);

DocListAp FindDoc(int idDoc, DocList list);

DocListAp FindDocByRelev(float relev, DocList list);

