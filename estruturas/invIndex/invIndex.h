#ifndef INVINDEX_H
#define INVINDEX_H
#include "../includes.h"

typedef struct InvCell *InvListAp;

typedef struct InvCell {
  int idDoc;
  int qnt;
  InvListAp prox;
} InvCell;

typedef struct {
  InvListAp first, last;
} InvIndexList;


void InvIndexCreateList(InvIndexList* list);

void InvIndexAdd(int idDoc, InvIndexList *list);

InvListAp InvIndexSearch(int idDoc,InvIndexList *list,Palavra palavra);

void InvIndexPrint(InvIndexList lista);

InvListAp FindIdDoc(int idDoc, InvIndexList list);
#endif

