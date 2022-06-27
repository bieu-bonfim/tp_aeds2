#include "patricia.h"

short PatVerifyExterno(PatAp p) {
    return (p->tipo == Externo);
}

PatAp PatCreateInterno(int i, PatAp *esq, PatAp *dir, char comp) {
    PatAp p;
    p = (PatAp) malloc(sizeof(PatNo));
    p->tipo = Interno;
    p->No.NoInterno.esq = *esq;
    p->No.NoInterno.dir = *dir;
    p->No.NoInterno.comp = comp;
    p->No.NoInterno.index = i;
    return p;
}

PatAp PatCreateExterno(Palavra palavra, int idDoc) {
    PatAp p;
    p = (PatAp) malloc(sizeof(PatNo));
    p->tipo = Externo;
    strcpy(p->No.palavra, palavra);
    p->invIndexList = (InvIndexList *) malloc(sizeof(InvIndexList));
    InvIndexCreateList(p->invIndexList);
    InvIndexAdd(idDoc, p->invIndexList);
    return p;
}

void PatPrintAlfabetico(PatAp t) {
    if (t != NULL) {
        if (t->tipo == Interno) {
            PatPrintAlfabetico(t->No.NoInterno.esq);
        }
        if (t->tipo == Externo) {
            printf("\n\t\t\t>> %s >> \t", t->No.palavra);
            InvIndexPrint(*t->invIndexList);

        }
        if (t->tipo == Interno) {
            PatPrintAlfabetico(t->No.NoInterno.dir);
        }
    }
}


void PatSearch(Palavra palavra, PatAp t) {
    if (PatVerifyExterno(t)) {
        if (strcmp(palavra, t->No.palavra) != 0) {
            printf("Palavra nao encontrada na arvore");
            return;
        } else {
            printf("\nA palavra <%s> foi encontrada!", palavra);
            return;
        }
    }
    if (strlen(palavra) < t->No.NoInterno.index) {
        return PatSearch(palavra, t->No.NoInterno.esq);
    } else if (palavra[t->No.NoInterno.index] < t->No.NoInterno.comp) {
        return PatSearch(palavra, t->No.NoInterno.esq);
    } else {
        return PatSearch(palavra, t->No.NoInterno.dir);
    }
}

PatAp PatSearchNode(Palavra palavra, PatAp t) {
    if (PatVerifyExterno(t)) {
        if (strcmp(palavra, t->No.palavra) != 0) {
            return NULL;
        } else {
            return t;
        }
    }
    if (strlen(palavra) < t->No.NoInterno.index) {
        return PatSearchNode(palavra, t->No.NoInterno.esq);
    } else if (palavra[t->No.NoInterno.index] < t->No.NoInterno.comp) {
        return PatSearchNode(palavra, t->No.NoInterno.esq);
    } else {
        return PatSearchNode(palavra, t->No.NoInterno.dir);
    }
}

PatAp PatInsertEntre(Palavra palavra, PatAp *t, int i, char comp, int idDoc) {
    PatAp p;
    if (PatVerifyExterno(*t)) {
        p = PatCreateExterno(palavra, idDoc);
        if (strcmp(palavra, (*t)->No.palavra) < 0) {
            return (PatCreateInterno(i, &p, t, comp));
        } else if (strcmp(palavra, (*t)->No.palavra) > 0) {
            return (PatCreateInterno(i, t, &p, comp));
        }
        return NULL;
    } else if (i < (*t)->No.NoInterno.index) {
        p = PatCreateExterno(palavra, idDoc);
        if (palavra[i] < comp) {
            return (PatCreateInterno(i, &p, t, comp));
        } else {
            return (PatCreateInterno(i, t, &p, comp));
        }
    } else {
        int newIndex = (*t)->No.NoInterno.index;

        if (palavra[newIndex] < (*t)->No.NoInterno.comp) {
            (*t)->No.NoInterno.esq = PatInsertEntre(palavra, &(*t)->No.NoInterno.esq, i, comp, idDoc);
        } else {
            (*t)->No.NoInterno.dir = PatInsertEntre(palavra, &(*t)->No.NoInterno.dir, i, comp, idDoc);
        }
        return (*t);
    }
}

PatAp PatInsert(Palavra palavra, int idDoc, PatAp *t) {
    PatAp p;
    int i;

    if (*t == NULL) {
        return (PatCreateExterno(palavra, idDoc));
    } else {
        p = *t;
        while (!PatVerifyExterno(p)) {

            if (palavra[p->No.NoInterno.index] < p->No.NoInterno.comp) {
                p = p->No.NoInterno.esq;
            } else if (palavra[p->No.NoInterno.index] >= p->No.NoInterno.comp) {
                p = p->No.NoInterno.dir;
            }
        }

        if (strcmp(palavra, p->No.palavra) != 0) {
            int tam1 = strlen(palavra), tam2 = strlen(p->No.palavra), tam;
            if (tam1 < tam2) {
                tam = tam1;
            } else {
                tam = tam2;
            }

            char comp;

            for (i = 0; i <= tam; i++) {
                if (palavra[i] != p->No.palavra[i]) {
                    if (palavra[i] < p->No.palavra[i]) {
                        comp = p->No.palavra[i];
                        break;
                    } else {
                        comp = palavra[i];
                        break;
                    }
                }
            }
            return PatInsertEntre(palavra, t, i, comp, idDoc);
        } else {
            InvIndexAdd(idDoc, p->invIndexList);
            return (*t);
        }
    }
}