#include "mainAux.h"

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

// https://www.geeksforgeeks.org/c-program-to-sort-an-array-in-ascending-order/
void selectionSort(float arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {

        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] > arr[min_idx])
                min_idx = j;

        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

void swap(float* xp, float* yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}