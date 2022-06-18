#include "patricia.h"

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

      printf("no interno com caractere <%c> ", comp);
      printf("em <%d> para o outro lado", i);

  return p;
} 

void PrintOrdemSimples(Apontador t) {
  if (t != NULL) {
    if (t->tipo == Interno)
      OrdemAlfabetica(t->No.NoInterno.esq);
    if (t->tipo == Externo)
      printf("\n%s\n", t->No.palavra);
    if (t->tipo == Interno)
      OrdemAlfabetica(t->No.NoInterno.dir);
  }
}

Apontador NoExternoCriar(Palavra palavra)
{ 
  Apontador p;
  p = (Apontador)malloc(sizeof(No));
  p->tipo = Externo; 
      printf("criado no exeterno para <%s>\n ", palavra);
  strcpy(p->No.palavra, palavra);
  return p;
}  

void Pesquisar(Palavra palavra, Apontador t)
{
    printf("\nA palavra <%s> esta nesse no", t->No.palavra);
  if (VerifExterno(t)) {
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
    return Pesquisar(palavra, t->No.NoInterno.esq);
  } else if (palavra[t->No.NoInterno.index] < t->No.NoInterno.comp) {
    printf("\nA palavra buscada <%s> ", palavra);
    printf("\nletra da palavra: <%c> ", palavra[t->No.NoInterno.index]);
    printf("\nletra comparada no no: <%c>", t->No.NoInterno.comp);
    printf("\nposicao da letra no no: <%d>", t->No.NoInterno.index);
    printf("\ncaso esquerda 2\n\n");
    return Pesquisar(palavra, t->No.NoInterno.esq);
  } else {
    printf("\nA palavra buscada <%s> ", palavra);
    printf("\nletra da palavra: <%c>  ", palavra[t->No.NoInterno.index]);
    printf("\nletra comparada no no: <%c>", t->No.NoInterno.comp);
    printf("\nposicao da letra no no: <%d>", t->No.NoInterno.index);
    printf("\nposicao direita\n\n");
    return Pesquisar(palavra, t->No.NoInterno.dir);
  }
} 

Apontador InserirEntre(Palavra palavra, Apontador *t, int i, char comp)
{ 
  Apontador p;
  if (VerifExterno(*t)) 
  { 
    p = NoExternoCriar(palavra);
    if (strcmp(palavra, (*t)->No.palavra) < 0) {
      printf("\npalavra comparada <%s>\n", (*t)->No.palavra);
      printf("\nno externo de <%s> foi para a esquerda\n", palavra);
      return (NoInternoCriar(i, &p, t, comp));
    } else if (strcmp(palavra, (*t)->No.palavra) > 0) {
      printf("\npalavra comparada <%s>\n", (*t)->No.palavra);
      printf("\nno externo de <%s> foi para a direita\n", palavra);
      return (NoInternoCriar(i, t, &p, comp));
    } 
    return NULL;
  } else if (i < (*t)->No.NoInterno.index) {
    p = NoExternoCriar(palavra);
    if (palavra[i] < comp) { 
      return (NoInternoCriar(i, &p, t, comp));
    } else {
      return (NoInternoCriar(i, t, &p, comp));
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

Apontador Inserir(Palavra palavra, Apontador *t)
{ 
  Apontador p;
  int i;
  
  if (*t == NULL) {
    return (NoExternoCriar(palavra));
  } else { 
    p = *t;
    while (!VerifExterno(p)) { 

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
      return InserirEntre(palavra, t, i, comp);
    } else {
      printf("A palavra <%s> ja foi inserida", palavra);
      return (*t);
    }
    

  }
}

int main()
{ 
  Apontador a = NULL;
  Palavra c;

  a = Inserir("rato", &a);
  a = Inserir("rataria", &a);
  a = Inserir("roeu", &a);
  a = Inserir("roupa", &a);
  a = Inserir("rei", &a);
  a = Inserir("roma", &a);
  a = Inserir("rios", &a);
  a = Inserir("ratos", &a);


  Pesquisar("rato", a);
  Pesquisar("rataria", a);
  Pesquisar("roeu", a);
  Pesquisar("roupa", a);
  Pesquisar("rei", a);
  Pesquisar("roma", a);
  Pesquisar("rios", a);
  Pesquisar("ratos", a);
  Pesquisar("macaco", a);

  OrdemAlfabetica(a);

  // printf("\n%c", a->No.NoInterno.comp);
  // printf(" %d", a->No.NoInterno.index);

  // printf("\n%s", a->No.NoInterno.dir->No.palavra);

  // printf("\n%c", a->No.NoInterno.esq->No.NoInterno.comp);
  // printf(" %d", a->No.NoInterno.esq->No.NoInterno.index);

  // printf("\n%s", a->No.NoInterno.esq->No.NoInterno.esq->No.palavra);
  // printf("\n%s", a->No.NoInterno.esq->No.NoInterno.dir->No.palavra);
  // printf(" %d",a->No.NoInterno.dir->No.NoInterno.index);



  // printf("\n%s", a->No.NoInterno.esq->No.palavra);

  return 0;
} 
