typedef struct InvIndex {
  int idDoc;
  int qnt;
} InvIndex;

typedef struct Cell *InvListAp;

typedef struct Cell {
  InvIndex inv;
  InvListAp prox;
} Cell;

typedef struct {
  InvListAp first, last;
} InvIndexList;


void FLVazia(InvIndexList *list)
{ 
  list -> first = (InvListAp) malloc(sizeof(Cell));
  list -> last = list -> first;
  list -> first -> prox = NULL;
}

int Vazia(InvIndexList list)
{ return (list.first == list.last);
}

void Insere(InvIndex x, InvIndexList *list)
{ list -> last -> prox = (InvListAp) malloc(sizeof(Cell));
  list -> last = list -> last -> prox;
  list -> last -> inv = x;
  list -> last -> prox = NULL;
}

void Retira(InvListAp p, InvIndexList *lista, InvIndex *inv)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
  InvListAp q;
  if (Vazia(*lista) || p == NULL || p -> prox == NULL) 
  { printf(" Erro   lista vazia ou posi  c   a o n  a o existe\n");
    return;
  }
  q = p -> prox;
  *inv = q -> inv;
  p -> prox = q -> prox;
  if (p -> prox == NULL) lista -> last = p;
  free(q);
}

void Imprime(InvIndexList lista)
{ InvListAp Aux;
  Aux = lista.first -> prox;
  while (Aux != NULL) 
    { printf("%d\n", Aux -> inv.idDoc);
      Aux = Aux -> prox;
    }
}