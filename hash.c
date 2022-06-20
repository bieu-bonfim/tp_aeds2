#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "fila.c"
#define M 11
#define N 12   
#define TAMALFABETO 256

/* typedef unsigned int  Pesos[n]; */
typedef char Palavra[64];
typedef char Chave[N];
typedef unsigned Pesos[N][TAMALFABETO];
typedef struct Item {
  /* outros componentes */
  Chave Chave;
} Item;

typedef unsigned int TipoIndice;
typedef struct Celula* Apontador;

typedef struct Celula {
  char *conteudo;
  Item Item;
  Apontador Prox;
} Celula;

typedef struct TipoLista {
  Celula *Primeiro, *Ultimo;
} TipoLista;

typedef TipoLista TipoDicionario[M];

TipoDicionario Tabela;
Item Elemento;
Pesos p;
Apontador i;

void FLVazia(TipoLista *Lista)
{ Lista->Primeiro = (Celula *)malloc(sizeof(Celula));
  Lista->Ultimo = Lista->Primeiro; 
  Lista->Primeiro->Prox = NULL;
}  

short Vazia(TipoLista Lista)
{
  return (Lista.Primeiro == Lista.Ultimo); 
}

void Ins(Palavra palavra, TipoLista *Lista)
{ Lista->Ultimo->Prox = (Celula *)malloc(sizeof(Celula));
  Lista->Ultimo = Lista->Ultimo->Prox; 
  Lista->Ultimo->conteudo = palavra;
  Lista->Ultimo->Prox = NULL;
}  



void GeraPesos(Pesos p){ /* Gera valores randomicos entre 1 e 10.000 */
  int i, j;
  struct timeval semente;
  /* Utilizar o tempo como semente para a funcao srand() */
  gettimeofday(&semente, NULL); 
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  for (i = 0; i < N; i++)
    for (j = 0; j < TAMALFABETO; j++)
      p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

TipoIndice h(Palavra palavra, Pesos p){ int i; unsigned int Soma = 0; 
  int comp = strlen(palavra);
  for (i = 0; i < comp; i++)
    Soma += p[i][(unsigned int)palavra[i]];
  return (Soma % M);
}

void Inicializa(TipoDicionario T){ int i;
  for (i = 0; i < M; i++) FLVazia(&T[i]);
}

Apontador Pesquisa(Palavra palavra, Pesos p, TipoDicionario T){ /* Obs.: Apontador de retorno aponta para o item anterior da lista */
  TipoIndice i;
  Apontador Ap;
  i = h(palavra, p);
  if (Vazia(T[i])) return NULL;  /* Pesquisa sem sucesso */
  else 
  { Ap = T[i].Primeiro;
    while (Ap->Prox->Prox != NULL &&
        strncmp(palavra, Ap->Prox->conteudo, sizeof(Chave))) 
      Ap = Ap->Prox;
    if (!strncmp(palavra, Ap->Prox->conteudo, sizeof(Chave))) 
    return Ap;
    else return NULL;  /* Pesquisa sem sucesso */
  }
}  

void Insere(Palavra palavra, Pesos p, TipoDicionario T)
{ 
  //if (Pesquisa(palavra, p, T) == NULL)
  Ins(palavra, &T[h(palavra, p)]);
  //else printf(" Registro ja  esta  presente\n");
} 


void Imp(TipoLista Lista){ 
  Apontador Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL) 
    { printf("%.*s ", N, Aux->conteudo);
      Aux = Aux->Prox;
    }
}

void Imprime(TipoDicionario Tabela){ 
  int i;
  for (i = 0; i < M; i++) 
    { printf("%d: ", i);
      if (!Vazia(Tabela[i]))
      Imp(Tabela[i]);
      putchar('\n');
    }
} 

void LerPalavra(FILE *arquivo,FILE* arquivo2,char *temp, int Tam){ 
  char* palavras;
  char* line;
  int count = 0;
  char c;
  int i = 0;
  for (c = getc(arquivo2); c != EOF; c = getc(arquivo2))
       count++;
 if(arquivo == NULL)
   printf("Erro, nao foi possivel abrir o arquivo\n");
  
 else{
  line = (char*) malloc(count * sizeof(char));
  fgets(line, (sizeof line)*count, arquivo);
  palavras = strdup(line);
 }
  temp = strtok(palavras, " ");
  while(temp != NULL){
    Insere(temp,p,Tabela);
    temp = strtok(NULL, " " );
}
  }


/*
void separaPalavras(){
  char* palavras;
  char* line;
  int count = 0;
  char c;
  FILE *arquivo;
  FILE *arquivo2;
  arquivo = fopen("arquivo.txt", "r");
  arquivo2 = fopen("arquivo.txt", "r");
  char* temp,*temp2;
  int i = 0;
  for (c = getc(arquivo2); c != EOF; c = getc(arquivo2))
       count++;
 if(arquivo == NULL)
   printf("Erro, nao foi possivel abrir o arquivo\n");
 else{
     line = (char*) malloc(count * sizeof(char));
     fgets(line, (sizeof line)*count, arquivo);
     palavras = strdup(line);
 }
  LerPalavra(arquivo,Elemento.Chave,N);
  Insere(Elemento,p,Tabela);
  while(temp != NULL){
  printf("%s\n",temp);
  temp = strtok(NULL, " " );
}
free(line); 
fclose(arquivo);
fclose(arquivo2);
}
  */

int main(int argc, char *argv[]){

  FILE *arquivo;
  FILE *arquivo2;
  arquivo = fopen("arquivo.txt", "r");
  arquivo2 = fopen("arquivo.txt", "r");
  Inicializa(Tabela);
  GeraPesos(p);
  LerPalavra(arquivo,arquivo2,Elemento.Chave,N);
  printf("Tabela apos insercao:\n");
  Imprime(Tabela);

  fclose(arquivo);
  fclose(arquivo2);
  return 0;
}
  
