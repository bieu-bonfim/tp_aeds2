#include "patricia.h"

short VerifExterno(Apontador p) {
  return (p->tipo == Externo);
}

Apontador CriarInterno(int i, Apontador *esq,  Apontador *dir, char comp) { 
  Apontador p;
  p = (Apontador)malloc(sizeof(No));
  p->tipo = Interno; 
  p->No.NoInterno.esq = *esq;
  p->No.NoInterno.dir = *dir; 
  p->No.NoInterno.comp = comp; 
  p->No.NoInterno.index = i; 
  return p;
} 

void PrintOrdemSimples(Apontador t) {
  if (t != NULL) {
    if (t->tipo == Interno) {
      PrintOrdemSimples(t->No.NoInterno.esq);
    }
    if (t->tipo == Externo) {
      printf("\n%s\n", t->No.palavra);
    }
    if (t->tipo == Interno) {
      PrintOrdemSimples(t->No.NoInterno.dir);
    }
  }
}

Apontador CriarExterno(Palavra palavra) { 
  Apontador p;
  p = (Apontador)malloc(sizeof(No));
  p->tipo = Externo; 
  strcpy(p->No.palavra, palavra);
  return p;
}  

void Pesquisar(Palavra palavra, Apontador t) {
  if (VerifExterno(t)) {
    if (strcmp(palavra, t->No.palavra) != 0) {
      printf("Palavra nao encontrada na arvore");
      return;
    } else {
      printf("\nA palavra <%s> foi encontrada!", palavra);
      return;
    }
  }
  if (strlen(palavra) < t->No.NoInterno.index) {
    return Pesquisar(palavra, t->No.NoInterno.esq);
  } else if (palavra[t->No.NoInterno.index] < t->No.NoInterno.comp) {
    return Pesquisar(palavra, t->No.NoInterno.esq);
  } else {
    return Pesquisar(palavra, t->No.NoInterno.dir);
  }
} 

Apontador InserirEntre(Palavra palavra, Apontador *t, int i, char comp) { 
  Apontador p;
  if (VerifExterno(*t)) 
  { 
    p = CriarExterno(palavra);
    if (strcmp(palavra, (*t)->No.palavra) < 0) {
      return (CriarInterno(i, &p, t, comp));
    } else if (strcmp(palavra, (*t)->No.palavra) > 0) {
      return (CriarInterno(i, t, &p, comp));
    } 
    return NULL;
  } else if (i < (*t)->No.NoInterno.index) {
    p = CriarExterno(palavra);
    if (palavra[i] < comp) { 
      return (CriarInterno(i, &p, t, comp));
    } else {
      return (CriarInterno(i, t, &p, comp));
    }
  } else { 
    int newIndex = (*t)->No.NoInterno.index;

    if(palavra[newIndex] < (*t)->No.NoInterno.comp) {
      (*t)->No.NoInterno.esq = InserirEntre(palavra, &(*t)->No.NoInterno.esq, i, comp);
    } else {
      (*t)->No.NoInterno.dir = InserirEntre(palavra, &(*t)->No.NoInterno.dir, i, comp);
    }
    return (*t);
  }
}

Apontador Inserir(Palavra palavra, Apontador *t) { 
  Apontador p;
  int i;
  
  if (*t == NULL) {
    return (CriarExterno(palavra));
  } else { 
    p = *t;
    while (!VerifExterno(p)) { 

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
            comp =  p->No.palavra[i];
            break;
          } else {
            comp =  palavra[i];
            break;
          }
        }
      }
      return InserirEntre(palavra, t, i, comp);
    } else {
      printf("A palavra <%s> ja foi inserida", palavra);
      return (*t);
    }
    

  }
}