#include <stdlib.h> 
#include <stdio.h>
#include "../invIndex/invIndex.h"

#define D 8   /* depende de Palavra */

typedef unsigned char Palavra[64]; /* a definir, dependendo da aplicacao */

typedef unsigned char IndexLetra;

typedef enum {
  Interno, Externo
} TipoNo;

typedef struct PatNo* PatAp; 

typedef struct PatNo {
  TipoNo tipo;
  union {
    struct {
      int index;
      PatAp esq, dir;
      char comp;
    } NoInterno ;
    Palavra palavra;
    InvIndexList invIndexList;
  } No;
} PatNo;

short VerifExterno(PatAp p);

PatAp NoInternoCriar(int i, PatAp *esq,  PatAp *dir, char comp);

void PrintOrdemSimples(PatAp t);

PatAp NoExternoCriar(Palavra palavra);

void Pesquisar(Palavra palavra, PatAp t);

PatAp InserirEntre(Palavra palavra, PatAp *t, int i, char comp);

PatAp Inserir(Palavra palavra, PatAp *t);