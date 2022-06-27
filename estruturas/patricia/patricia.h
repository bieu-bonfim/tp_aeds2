#include "../invIndex/invIndex.h"

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
  } No;
  InvIndexList *invIndexList;
} PatNo;

short PatVerifyExterno(PatAp p);

PatAp PatCreateExterno(Palavra palavra, int idF);

PatAp PatCreateInterno(int i, PatAp *esq,  PatAp *dir, char comp);

void PatPrintAlfabetico(PatAp t);

void PatSearch(Palavra palavra, PatAp t);

PatAp PatSearchNode(Palavra palavra, PatAp t);

PatAp PatInsertEntre(Palavra palavra, PatAp *t, int i, char comp, int idF);

PatAp PatInsert(Palavra palavra, int idF, PatAp *t);