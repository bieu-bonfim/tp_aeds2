#include "estruturas/patricia/patricia.h"
#include "estruturas/hash/hash.h"

#define SIZE 20

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

void InsertWords (char * fileName, int idDoc, PatAp * a, HashTable b, Pesos p) {
    unsigned char str[1024];
    FILE *doc;
    doc = fopen(fileName, "r");

    while (fscanf(doc, " %1023s", str) == 1) {
        NoPunctAllLower(str);
        *a = PatInsert(str, idDoc, a);
        HshTableInsert(str, idDoc, p, b);
    }
}

int main(){
    // Criação da PATRICIA
    PatAp patricia = NULL;

    // Criação da Hash Table
    Pesos p;
    HashTable hashTable;
    HshTableGeraPesos(p);
    HshTableCreate(hashTable);

    FILE *in_ptr;
    char str[50];
    char file[50];
    char **files = NULL;
    int n = 0, opcao, set = 0;
    while (1)
    {
        /* code */
        system("CLS");
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
            printf("\n\t\t\t>> Insira o nome do arquivo: ");
//            scanf("%d",file);

            in_ptr = fopen("../input.txt", "r");
            for (int i = 0; i < n; i++)
            {
                free(files[i]);
            }
            free(files);
            
            if (NULL == in_ptr) {
                printf("O arquivo nao foi encontrado.\n");
            }
            n = 0;
            set = 0;
            while (!feof (in_ptr)) {
                if (n==0) {
                    fscanf(in_ptr, "%d", &n);
                    files = malloc(n * sizeof(char*));
                    for (int i = 0; i < n; i++) {
                        files[i] = malloc((SIZE+1) * sizeof(char));
                    }
                } else {
                    fgets(str, 50, in_ptr);
                    if (strlen(str) > 4) {
                        str[strcspn(str, "\n")] = '\0'; 
                        strcpy(files[set], str);
                        set++;
                    }
                }
            }
            fclose(in_ptr);

        }else if(opcao == 2){
            if (files == NULL)
            {
                printf("insira um arquivo de entrada primeiro");
                continue;
            }
            for (int i = 0; i < n; i++)
            {
                InsertWords(files[i], i+1, &patricia, hashTable, p);
            }

        }else if(opcao == 3){
            PatPrintAlfabetico(patricia);
            HshTablePrint(hashTable);
        }else if(opcao == 4){

        }else if(opcao == 5){
            break;
        }else{
            printf("Opcao nao encontrada, por favor insira uma opcao valida");
        }
    }

    return 0;
}
