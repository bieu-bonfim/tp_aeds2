#include "estruturas/patricia/patricia.h"
#include "estruturas/hash/hash.h"
#include "estruturas/docs/docs.h"

#define SIZE 20

void NoPunctAllLower(char * str);
void InsertWordsPat (DocList docs, int idDoc, PatAp * a);
void InsertWordsHsh (DocList docs, int idDoc, HashTable b, Pesos p);
int calculoRelevancia(int numDocumentos,int qntTermosDoc,int numOcorrencias,int numDocContemTermo);
void quick_sort(int *a, int left, int right);

int main(){

    // Criação da PATRICIA
    PatAp patricia = NULL;
    //---------------------------

    // Criação da Hash Table
    Pesos p;
    HashTable hashTable;
    HshTableGeraPesos(p);
    HshTableCreate(hashTable);
    //---------------------------

    // Criação da lista de documentos
    DocList docs;
    DocCreateList(&docs);
    int cont = 1;
    //---------------------------

    // Variáveis para interação com o menu e leitura do arquivo de entrada
    FILE *in_ptr;
    char str[50];
    int n = 0, opcao;
    //---------------------------

    // Variáveis funcionamento limpo do código
    short patUse = 0;
    short hshUse = 0;
    //---------------------------

    while (1) {
        printf("\n\t\t\t//====================================================================\\\\ \n");
        printf("\t\t\t||                           Menu Principal                           ||\n");
        printf("\t\t\t|]====================================================================[|\n");
        printf("\t\t\t||                                                                    ||\n");
        printf("\t\t\t||  1 - Enviar o arquivo de entrada com os textos para indexamento;   ||\n");
        printf("\t\t\t||  2 - Construir os indices invertidos;                              ||\n");
        printf("\t\t\t||  3 - Imprimir os indices invertidos;                               ||\n");
        printf("\t\t\t||  4 - Realizar busca de termo(s) nos indices construidos            ||\n");
        printf("\t\t\t||  5 - Sair.                                                         ||\n");
        printf("\t\t\t||                                                                    ||\n");
        printf("\t\t\t\\\\====================================================================// \n");
        printf("\n\t\t\t>> Escolha uma das opcoes acima: ");
        scanf("%d",&opcao);
        if(opcao == 1){
//            printf("\n\t\t\t>> Insira o nome do arquivo: ");
//            scanf("%d",file);

            in_ptr = fopen("../input.txt", "r");
            if (NULL == in_ptr) {
                printf("O arquivo nao foi encontrado.\n");
            }
            if (!DocListVerify(docs)) {
                DocDeleteList(&docs);
                n=0;
                cont = 1;
                DocCreateList(&docs);
            }
            while (!feof (in_ptr)) {
                if (n==0) {
                    fscanf(in_ptr, "%d", &n);
                } else {
                    fgets(str, 50, in_ptr);
                    if (strlen(str) > 4) {
                        str[strcspn(str, "\n")] = '\0';
                        DocAdd(cont, str, &docs);
                        cont++;
                    }
                }
                //criando vetor com base na quantidade de arquivos para armazenar quantidade de palavras
                char quantidadePalavrasPat[n];
                char quantidadePalavrasHash[n];
            }
            fclose(in_ptr);

            if (DocListVerify(docs)) {
                printf("\n\t\t\t>> Nenhum arquivo foi descoberto na leitura do arquivo de entrada, tente novamente ");
            } else {
                printf("\n\t\t\t>> %d Arquivos foram descobertos e salvos", n);
                DocPrint(docs);
                printf("\n");
            }

        }else if(opcao == 2){
            if (DocListVerify(docs))
            {
                printf("\n\t\t\t>> Primeiro, insira um arquivo de entrada na opcao 1");
                continue;
            }
            while (1) {
                printf("\n\t\t\t//====================================================================\\\\ \n");
                printf("\t\t\t||                      Criar Indices Invertidos                      ||\n");
                printf("\t\t\t|]====================================================================[|\n");
                printf("\t\t\t||                                                                    ||\n");
                printf("\t\t\t||  1 - Utilizando a arvore PATRICIA;                                 ||\n");
                printf("\t\t\t||  2 - Utilizando a Tabela Hash;                                     ||\n");
                printf("\t\t\t||  3 - Voltar                                                        ||\n");
                printf("\t\t\t||                                                                    ||\n");
                printf("\t\t\t\\\\====================================================================// \n");
                printf("\n\t\t\t>> Escolha uma das opcoes acima: ");
                scanf("%d",&opcao);
                if (opcao == 1) {
                    if (patUse) {
                        printf("\n\t\t\t>> Os indices invertidos ja foram criados na PATRICIA");
                        printf("\n\t\t\t>> Utilize outro arquivo de entrada para utilizar essa funcao");
                        continue;
                    }
                    printf("\n\t\t\t>> Criando indice invertido na PATRICIA...");
                    for (int i = 1; i <= n; i++)
                    {
                        InsertWordsPat(docs, i, &patricia);
                        quantidadePalavrasPat[i] = docInfo->qntPalavras;
                    }
                    printf("\n\t\t\t>> Indices invertidos criados com sucesso!");
                    patUse = 1;

                } else if(opcao == 2) {
                    if (hshUse) {
                        printf("\n\t\t\t>> Os indices invertidos ja foram criados na Tabela Hash");
                        printf("\n\t\t\t>> Utilize outro arquivo de entrada para utilizar essa funcao");
                        continue;
                    }
                    printf("\n\t\t\t>> Criando indice invertido na Tabela Hash...");
                    for (int i = 1; i <= n; i++)
                    {
                        InsertWordsHsh(docs, i, hashTable, p);
                        quantidadePalavrasHash[i] = docInfo->qntPalavras;

                    }
                    printf("\n\t\t\t>> Indices invertidos criados com sucesso!");
                    hshUse = 1;
                } else if(opcao == 3) {
                    break;
                }
            }
        }else if(opcao == 3){
            if (DocListVerify(docs))
            {
                printf("\n\t\t\t>> Primeiro, insira um arquivo de entrada na opcao 1");
                continue;
            }
            while (1) {
                printf("\n\t\t\t//====================================================================\\\\ \n");
                printf("\t\t\t||                     Imprimir Indices Invertidos                    ||\n");
                printf("\t\t\t|]====================================================================[|\n");
                printf("\t\t\t||                                                                    ||\n");
                printf("\t\t\t||  1 - Utilizando a arvore PATRICIA;                                 ||\n");
                printf("\t\t\t||  2 - Utilizando a Tabela Hash;                                     ||\n");
                printf("\t\t\t||  3 - Voltar                                                        ||\n");
                printf("\t\t\t||                                                                    ||\n");
                printf("\t\t\t\\\\====================================================================// \n");
                printf("\n\t\t\t>> Escolha uma das opcoes acima: ");
                scanf("%d",&opcao);
                if (opcao == 1) {
                    printf("\n\t\t\t>> Indice invertido criado na PATRICIA:");
                    PatPrintAlfabetico(patricia);

                } else if(opcao == 2) {

                    printf("\n\t\t\t>> Indice invertido criado na Tabela Hash:");
                    HshTablePrint(hashTable);

                } else if(opcao == 3) {
                    break;
                }
            }
        }else if(opcao == 4){
            char buffer[1000];
            int escolhaDePesquisa;
            int numDocumentos;
            printf("Qual(is) termo(os) você deseja buscar?\n"
            "Insira os termos seguindo os exemplos abaixo:\n"
            "pao rato bolo\n"
            "arroz\n"
            "quem casa\n"
            "Insira os termos:");
            scanf("%s",buffer);
            int tamanhoPalavra = strlen(buffer);
            char *palavraParaBusca = (char *)malloc(sizeof(char)*tamanhoPalavra);
            int matrizRelevancia[n][1];

            printf("Em qual estrutura você deseja fazer a busca de termo(s):\n"
            "1- Tabela Hash\n"
            "2- Árvore Patricia\n"
            "Digite o número da estrutura escolhida:");
            scanf("%d",escolhaDePesquisa);
            if(escolhaDePesquisa == 1){///pesquisa na hash
                for(int i = 1; i<=n;i++){
                    int numOcorrencias = InvIndexSearch(i,hashTable,palavraParaBusca);
                    int qntDocHave = qntDocHaveTermHash(i,hashTable,palavraParaBusca);
                    int valorRelevancia = calculoRelevancia(n,quantidadePalavrasHash[i],numOcorrencias,qntDocHave);
                    matrizRelevancia[i][0] = valorRelevancia;
                    ordenarRelevancia(int *a, int left, int right);
                }
                for(int j = 0;j<n;j++){
                        printf("Texto %d (arquivo%d.txt\n",matrizRelevancia[i][0]);
                    } 
            
            }else if(escolhaDePesquisa == 2){//pesquisa na patricia
                for(int i = 1; i<=n;i++){
                    int numOcorrencias = InvIndexSearch(i,patricia,palavraParaBusca);
                    int qntDocHave = int qntDocHaveTermPat(i,patricia,palavraParaBusca);
                    int valorRelevancia = calculoRelevancia(n,quantidadePalavrasHash[i],numOcorrencias,qntDocHave);
                    matrizRelevancia[i][0] = valorRelevancia;
                    ordenarRelevancia(int *a, int left, int right);
                }
                for(int j = 0;j<n;j++){
                    printf("Texto %d (arquivo%d.txt\n",matrizRelevancia[i][0]);
                } 

            }else{
                printf("Escolha inválida. Por favor escolha entre 1 e 2.");
            }

        }else if(opcao == 5){
            break;
        }else{
            printf("Opcao nao encontrada, por favor insira uma opcao valida");
        }
    }

    return 0;
}

void NoPunctAllLower(char * str) {
    int p = 0;
    char * str2;
    strcpy(str2, str);
    int len = strlen(str2);
    for (int i = 0; i < len; i++) {
        str[i] = (char) 0;
        if (!ispunct(str2[i])) {
            str[p] = tolower(str2[i]);
            p++;
        }
    }
}

void InsertWordsPat (DocList docs, int idDoc, PatAp * a) {
    unsigned char str[1024];
    int pCont = 0;

    DocListAp docInfo;
    docInfo = FindDoc(idDoc, docs);

    FILE *doc;
    doc = fopen(docInfo->docName, "r");

    while (fscanf(doc, " %1023s", str) == 1) {
        NoPunctAllLower(str);
        *a = PatInsert(str, idDoc, a);
        pCont++;
    }
    docInfo->qntPalavras = pCont;
}

void InsertWordsHsh (DocList docs, int idDoc, HashTable b, Pesos p) {
    unsigned char str[1024];
    int pCont = 0;

    DocListAp docInfo;
    docInfo = FindDoc(idDoc, docs);

    FILE *doc;
    doc = fopen(docInfo->docName, "r");

    while (fscanf(doc, " %1023s", str) == 1) {
        NoPunctAllLower(str);
        HshTableInsert(str, idDoc, p, b);
        pCont++;
    }
    docInfo->qntPalavras = pCont;
}

int calculoRelevancia(int numDocumentos,int qntTermosDoc,int numOcorrencias,int numDocContemTermo){

    int relevancia,somatorio = 0;

    for(int i = 1;i<qntTermosDoc;i++){
        somatorio = somatorio + (numOcorrencias * (log(numDocumentos)/numDocContemTermo));  
    }
    relevancia = (1/numDocumentos)*somatorio;
    
    return relevancia;
}

void ordenarRelevancia(int *a, int left, int right) {
    int i, j, x, y[1][1];
     
    i = left;
    j = right;
    x = a[(left + right) / 2][0];
     
    while(i <= j) {
        while(a[i][0] < x && i < right) {
            i++;
        }
        while(a[j][0] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y[1][1] = a[i][1];
            a[i][1] = a[j][1];
            a[j][1] = y[1][1];
            i++;
            j--;
        }
    }
     
    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}