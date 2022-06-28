#include "estruturas/patricia/patricia.h"
#include "estruturas/hash/hash.h"
#include "estruturas/docs/docs.h"

float TermWeightPat(char term[64], int idDoc, int nDocs, PatAp a);

float TermWeightHsh(char term[64], int idDoc, int nDocs, HashTable a, Pesos p);

void NoPunctAllLower(char * str);

void InsertWordsPat (DocList docs, int idDoc, PatAp * a);

void InsertWordsHsh (DocList docs, int idDoc, HashTable b, Pesos p);

void swap(float* xp, float* yp);

void selectionSort(float arr[], int n);