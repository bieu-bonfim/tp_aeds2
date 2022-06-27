#include "../invIndex/invIndex.h"

#define N 64

typedef struct HshCell* HshCellAp;

typedef struct HshCell {
    Palavra palavra;
    InvIndexList *invIndexList;
    HshCellAp prox;
} HshCell;

typedef struct HshList {
    HshCellAp first, last;
} HshList;

short HshListVerify(HshList list);

void HshListCreate(HshList *list);

void HshListPrint(HshList list);

void HshListInsert(Palavra palavra, HshList *list,int idDoc);

HshCellAp FindPalavra(Palavra palavra, HshList list);