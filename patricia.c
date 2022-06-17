#include <stdlib.h> 
#include <stdio.h>
#include <sys/time.h>

#define D 8   /* depende de Palavra */

typedef unsigned char Palavra[64]; /* a definir, dependendo da aplicacao */

typedef unsigned char IndexPalavra;

// typedef unsigned char TipoDib;

typedef enum {
  Interno, Externo
} TipoNo;

typedef struct No* Apontador; 

typedef struct No {
  TipoNo tipo;
  union {
    struct {
      IndexPalavra index;
      Apontador esq, dir;
      char comp;
    } NoInterno ;
    Palavra palavra;
  } No;
} No;

short VerifExterno(Apontador p)
{ /* Verifica se p^ e nodo externo */
  return (p->tipo == Externo);
}

Apontador NoInternoCriar(int i, Apontador *esq,  Apontador *dir, char comp)
{ 
  Apontador p;
  p = (Apontador)malloc(sizeof(No));
  p->tipo = Interno; 
  p->No.NoInterno.esq = *esq;
  p->No.NoInterno.dir = *dir; 
  p->No.NoInterno.comp = comp; 
  p->No.NoInterno.index = i; 
  return p;
} 

Apontador NoExternoCriar(Palavra palavra)
{ 
  Apontador p;
  p = (Apontador)malloc(sizeof(No));
  p->tipo = Externo; 
  strcpy(p->No.palavra, palavra);
  return p;
}  

void Pesquisar(Palavra palavra, Apontador t)
{
  if (VerifExterno(t)) {
    printf("A palavra <%s> foi encontrada!", t->No.palavra);

    if (strcmp(palavra, t->No.palavra) != 0) {
      printf("Palavra nao encontrada na arvore");
      return;
    } else {
      printf("A palavra <%s> foi encontrada!", palavra);
      return;
    }
  }

  printf("\n%c ", t->No.NoInterno.comp);
  printf(" %d ", t->No.NoInterno.index);
  printf(" %c\n", palavra[t->No.NoInterno.index]);

  if (strlen(palavra) < t->No.NoInterno.index) {
    return Pesquisar(palavra, t->No.NoInterno.esq);
  } else if (palavra[t->No.NoInterno.index] <= t->No.NoInterno.comp) {
    return Pesquisar(palavra, t->No.NoInterno.esq);
  } else {
    return Pesquisar(palavra, t->No.NoInterno.dir);
  }
} 

Apontador InserirEntre(Palavra palavra, Apontador *t, int i, char comp)
{ 
  Apontador p;
  if (VerifExterno(*t)) 
  { 
    p = NoExternoCriar(palavra);
    if (strcmp((*t)->No.palavra, palavra) > 0) {
      return (NoInternoCriar(i, &p, t, comp));
    } else if (strcmp((*t)->No.palavra, palavra) < 0) {
      return (NoInternoCriar(i, t, &p, comp));
    } 
  } else if (i < (*t)->No.NoInterno.index) {
    p = NoExternoCriar(palavra);
    if (palavra[i] < comp)
    { 
      return (NoInternoCriar(i, &p, t, comp));
    } else {
      return (NoInternoCriar(i, t, &p, comp));
    }
  } else { 
    int newIndex = (*t)->No.NoInterno.index;

    if(palavra[newIndex] > (*t)->No.NoInterno.comp) {
      (*t)->No.NoInterno.esq = InserirEntre(palavra, &(*t)->No.NoInterno.esq, i, comp);
    } else {
      (*t)->No.NoInterno.dir = InserirEntre(palavra, &(*t)->No.NoInterno.dir, i, comp);
    }
    return (*t);
  }
}

Apontador Inserir(Palavra palavra, Apontador *t)
{ 
  Apontador p;
  int i;
  if (*t == NULL) {
    return (NoExternoCriar(palavra));
  } else { 
    p = *t;
    while (!VerifExterno(p)) { 
      if (palavra[p->No.NoInterno.index] <= p->No.NoInterno.comp) {
        p = p->No.NoInterno.esq;
      } else if (palavra[p->No.NoInterno.index] > p->No.NoInterno.comp) {
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

      for (i = 0; i < tam; i++) {
        if (palavra[i] != p->No.palavra[i]) {
          if (palavra[i] <= p->No.palavra[i]) {
            comp =  p->No.palavra[i];
          } else {
            comp =  palavra[i];
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

int main(int argc, char *argv[])
{ 
  Apontador a = NULL;
  Palavra c;

  a = Inserir("rato", &a);
  a = Inserir("rataria", &a);
  a = Inserir("roeu", &a);
  a = Inserir("roupa", &a);
  // a = Inserir("rei", &a);
  // a = Inserir("roma", &a);
  // a = Inserir("ratos", &a);
  Pesquisar("roeu", a);

  return 0;
} 
