#include "estruturas/patricia/patricia.h"
#include "estruturas/hash/hash.h"
#include "estruturas/docs/docs.h"

float TermWeightPat(char term[64], int idDoc, int nDocs, PatAp a) {
    float w;
    PatAp p = PatSearchNode(term, a);
    int occur = 0;
    int docsOccur = 1;
    if (p != NULL) {
        occur = InvIndexOccurInDoc(idDoc, *p->invIndexList);
        docsOccur = InvIndexNDocs(*p->invIndexList);
    }
    w = occur*(log2f(nDocs)/docsOccur);
    return w;
}

float TermWeightHsh(char term[64], int idDoc, int nDocs, HashTable a, Pesos p) {
    float w;
    HshCellAp h = HshTableSearch(term, p, a);
    int occur = 0;
    int docsOccur = 1;
    if (h != NULL) {
        occur = InvIndexOccurInDoc(idDoc, *h->invIndexList);
        docsOccur = InvIndexNDocs(*h->invIndexList);
    }
    w = occur*(log2f(nDocs)/docsOccur);
    return w;
}

void NoPunctAllLower(char * str) {
    int p = 0;
    char * str2;
    strcpy(str2, str);
    int len = strlen(str2);
    for (int i = 0; i < len; i++) {
        str[i] = (char) 0;
        if (!ispunct(str2[i])) {
            str[p] = tolower(str2[i]);
            p++;
        }
    }
}

void InsertWordsPat (DocList docs, int idDoc, PatAp * a) {
    unsigned char str[1024];
    int pCont = 0;

    DocListAp docInfo;
    docInfo = FindDoc(idDoc, docs);

    FILE *doc;
    doc = fopen(docInfo->docName, "r");

    while (fscanf(doc, " %1023s", str) == 1) {
        NoPunctAllLower(str);
        *a = PatInsert(str, idDoc, a);
        pCont++;
    }
    docInfo->qntPalavras = pCont;
}

void InsertWordsHsh (DocList docs, int idDoc, HashTable b, Pesos p) {
    unsigned char str[1024];
    int pCont = 0;

    DocListAp docInfo;
    docInfo = FindDoc(idDoc, docs);

    FILE *doc;
    doc = fopen(docInfo->docName, "r");

    while (fscanf(doc, " %1023s", str) == 1) {
        NoPunctAllLower(str);
        HshTableInsert(str, idDoc, p, b);
        pCont++;
    }
    docInfo->qntPalavras = pCont;
}
