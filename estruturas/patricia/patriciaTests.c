#include "patricia.h"

short PatVerifyExterno(PatAp p) { 
  return (p->tipo == Externo);
}

PatAp PatCreateInterno(int i, PatAp *esq,  PatAp *dir, char comp) { 
  PatAp p;
  p = (PatAp)malloc(sizeof(PatNo));
  p->tipo = Interno; 
  p->No.NoInterno.esq = *esq;
  p->No.NoInterno.dir = *dir; 
  p->No.NoInterno.comp = comp; 
  p->No.NoInterno.index = i; 

  printf("no interno com caractere <%c> ", comp);
  printf("em <%d> para o outro lado", i);

  return p;
} 

void PatPrintAlfabetico(PatAp t) {
  if (t != NULL) {
    if (t->tipo == Interno)
      PatPrintAlfabetico(t->No.NoInterno.esq);
    if (t->tipo == Externo)
      printf("\n%s\n", t->No.palavra);
    if (t->tipo == Interno)
      PatPrintAlfabetico(t->No.NoInterno.dir);
  }
}

PatAp PatCreateExterno(Palavra palavra, int idDoc) { 
  PatAp p;
  p = (PatAp)malloc(sizeof(PatNo));
  p->tipo = Externo; 
      printf("criado no exeterno para <%s>\n ", palavra);
  InvIndexCreateList(&p->No.invIndexList);
  InvIndexAdd(idDoc, &p->No.invIndexList);
  strcpy(p->No.palavra, palavra);
  return p;
}  

void PatSearch(Palavra palavra, PatAp t)
{
    printf("\nA palavra <%s> esta nesse no", t->No.palavra);
  if (PatVerifyExterno(t)) {
    printf("\nA palavra <%s> esta nesse no externo!", t->No.palavra);

    if (strcmp(palavra, t->No.palavra) != 0) {
      printf("Palavra nao encontrada na arvore");
      return;
    } else {
      printf("\nA palavra <%s> foi encontrada!", palavra);
      return;
    }
  }
  printf("\nA palavra buscada <%s> ", palavra);

  if (strlen(palavra) < t->No.NoInterno.index) {
    printf("\nesquerda 1");
    return PatSearch(palavra, t->No.NoInterno.esq);
  } else if (palavra[t->No.NoInterno.index] < t->No.NoInterno.comp) {
    printf("\nA palavra buscada <%s> ", palavra);
    printf("\nletra da palavra: <%c> ", palavra[t->No.NoInterno.index]);
    printf("\nletra comparada no no: <%c>", t->No.NoInterno.comp);
    printf("\nposicao da letra no no: <%d>", t->No.NoInterno.index);
    printf("\ncaso esquerda 2\n\n");
    return PatSearch(palavra, t->No.NoInterno.esq);
  } else {
    printf("\nA palavra buscada <%s> ", palavra);
    printf("\nletra da palavra: <%c>  ", palavra[t->No.NoInterno.index]);
    printf("\nletra comparada no no: <%c>", t->No.NoInterno.comp);
    printf("\nposicao da letra no no: <%d>", t->No.NoInterno.index);
    printf("\nposicao direita\n\n");
    return PatSearch(palavra, t->No.NoInterno.dir);
  }
} 

PatAp PatInsertEntre(Palavra palavra, PatAp *t, int i, char comp, int idDoc) { 
  PatAp p;
  if (PatVerifyExterno(*t)) 
  { 
    p = PatCreateExterno(palavra, idDoc);
    if (strcmp(palavra, (*t)->No.palavra) < 0) {
      printf("\npalavra comparada <%s>\n", (*t)->No.palavra);
      printf("\nno externo de <%s> foi para a esquerda\n", palavra);
      return (PatCreateInterno(i, &p, t, comp));
    } else if (strcmp(palavra, (*t)->No.palavra) > 0) {
      printf("\npalavra comparada <%s>\n", (*t)->No.palavra);
      printf("\nno externo de <%s> foi para a direita\n", palavra);
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

    if(palavra[newIndex] < (*t)->No.NoInterno.comp) {
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
        printf("\nLetra de %s e <%c> em <%d>\n", palavra, palavra[p->No.NoInterno.index], p->No.NoInterno.index);
        printf("Letra do no atual e <%c>\n", p->No.NoInterno.comp);
        printf("foi pra esquerda");
        p = p->No.NoInterno.esq;
      } else if (palavra[p->No.NoInterno.index] >= p->No.NoInterno.comp) {
        printf("\nLetra de %s e <%c> em <%d>\n", palavra, palavra[p->No.NoInterno.index], p->No.NoInterno.index);
        printf("Letra do no atual e <%c>\n", p->No.NoInterno.comp);
        printf("foi pra direita");
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
            printf("\nA palavra em insercao e <%s> ", palavra);
            printf("\nletra da palavra: <%c> ", palavra[i]);
            printf("letra da palavra no no atual: <%c> ", p->No.palavra[i]);
          if (palavra[i] < p->No.palavra[i]) {
            comp =  p->No.palavra[i];
            break;
          } else {
            comp =  palavra[i];
            break;
          }
        }
      }
      printf("\n<%c> ", comp);
      printf("em <%d> ", i);
      printf("para <%s>\n", palavra);
      // printf(" caso direita \n");
      return PatInsertEntre(palavra, t, i, comp, idDoc);
    } else {
      printf("A palavra <%s> ja foi inserida", palavra);
      return (*t);
    }
  }
}

void InvIndexCreateList(InvIndexList *list) {
  list -> first = (InvListAp) malloc(sizeof(Cell));
  list -> last = list -> first;
  list -> first -> prox = NULL;
}

void InvIndexAdd(int idDoc, InvIndexList *list) {
  Cell *p = FindIdDoc(idDoc, list->first);
  if (p != NULL) {
    p->qnt++;
    return;
  }
  list -> last -> prox = (InvListAp) malloc(sizeof(Cell));
  list -> last = list -> last -> prox;
  list -> last -> idDoc = idDoc;
  list -> last -> qnt = 1;
  list -> last -> prox = NULL;
}

void InvIndexPrint(InvIndexList lista) {
  InvListAp Aux;
  Aux = lista.first -> prox;
  while (Aux != NULL) 
  { 
    printf("< %d,", Aux -> qnt);
    printf("%d >\n", Aux -> idDoc);
    Aux = Aux -> prox;
  }
}

Cell* FindIdDoc(int idDoc, Cell *cell)
{
  if (cell == NULL)  return NULL;
  if (cell->idDoc == idDoc)  return cell;
  return FindIdDoc (idDoc, cell->prox);
}

int main() {
  PatAp a = NULL;
  int idDoc = 1;

  a = PatInsert("rato", idDoc, &a);
  a = PatInsert("rataria", idDoc, &a);
  a = PatInsert("roeu", idDoc, &a);
  a = PatInsert("roupa", idDoc, &a);
  a = PatInsert("rei", idDoc, &a);
  a = PatInsert("roma", idDoc, &a);
  a = PatInsert("rios", idDoc, &a);
  a = PatInsert("ratos", idDoc, &a);

  PatSearch("rato", a);
  PatSearch("rataria", a);
  PatSearch("roeu", a);
  PatSearch("roupa", a);
  PatSearch("rei", a);
  PatSearch("roma", a);
  PatSearch("rios", a);
  PatSearch("ratos", a);
  PatSearch("macaco", a);

  PatPrintAlfabetico(a);

  return 0;
}
