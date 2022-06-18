#include <stdlib.h> 
#include <stdio.h>
#include <sys/time.h>

#define D 8   /* depende de Palavra */

typedef unsigned char Palavra[64]; /* a definir, dependendo da aplicacao */

typedef unsigned char IndexLetra;

// typedef unsigned char TipoDib;

typedef enum {
  Interno, Externo
} TipoNo;

typedef struct No* Apontador; 

typedef struct No {
  TipoNo tipo;
  union {
    struct {
      IndexLetra index;
      Apontador esq, dir;
      char comp;
    } NoInterno ;
    Palavra palavra;
  } No;
} No;

short VerifExterno(Apontador p);

Apontador NoInternoCriar(int i, Apontador *esq,  Apontador *dir, char comp);

void PrintOrdemSimples(Apontador t);

Apontador NoExternoCriar(Palavra palavra);

void Pesquisar(Palavra palavra, Apontador t);

Apontador InserirEntre(Palavra palavra, Apontador *t, int i, char comp);

Apontador Inserir(Palavra palavra, Apontador *t);