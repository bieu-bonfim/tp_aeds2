#include <math.h>
#include <ctype.h>
#include "estruturas/patricia/patricia.h"

#define SIZE 20

void NoPunctAllLower(char * str) {
    int i = 0;
    int p = 0;
    int len = strlen(str);
    for (i = 0; i < len; i++) {
        if (!ispunct(str[i])) {
            str[p] = tolower(str[i]);
            p++;
        }
    }
}

void InsertWords (char * fileName, int idDoc, PatAp * a) {
    unsigned char str[1024];
    FILE *doc;
    doc = fopen(fileName, "r");

    while (fscanf(doc, " %1023s", str) == 1) {
        NoPunctAllLower(str);
        *a = PatInsert(str, idDoc, a);
    }
}

int main(){
    PatAp a = NULL; 
    FILE *in_ptr;
    char str[50];
    char **files = NULL;
    int n = 0, opcao, set = 0;
    while (1)
    {
        /* code */    
        printf("Menu:\n"
            "1-Enviar o arquivo de entrada com os textos para indexamento;\n"
            "2-Construir os indices invertidos;\n"
            "3-Imprimir os indices invertidos;\n"
            "4-Realizar busca de termo(s) nos indices construidos;\n"
            "5-Sair.\n"
            "Escolha uma das opcoes acima:");
        scanf("%d",&opcao);
        if(opcao == 1){
            printf("Insira o nome do arquivo: ");
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
//                InsertWords(files[i], i+1, &a);


            }
            a = PatInsert("rato", 1, &a);
            a = PatInsert("rato", 1, &a);
            a = PatInsert("rato", 1, &a);
            a = PatInsert("rato", 2, &a);
            a = PatInsert("rato", 2, &a);

            a = PatInsert("roeu", 1, &a);
            a = PatInsert("rataria", 1, &a);
            a = PatInsert("roupa", 1, &a);
            a = PatInsert("rei", 1, &a);
            a = PatInsert("roma", 1, &a);
            a = PatInsert("rola", 1, &a);

        }else if(opcao == 3){

            PatPrintAlfabetico(a);
//            printf("insira um arquivo de entrada primeiro");

        }else if(opcao == 4){
            InvIndexList list;
            InvIndexCreateList(&list);
            InvIndexAdd(1, &list);
            InvIndexAdd(1, &list);
            InvIndexAdd(1, &list);
            InvIndexAdd(1, &list);
            InvIndexAdd(2, &list);
            InvIndexAdd(2, &list);
            InvIndexAdd(3, &list);
            InvIndexAdd(3, &list);
            InvIndexAdd(3, &list);
            InvIndexAdd(4, &list);
            InvIndexPrint(list);
        }else if(opcao == 5){
            break;
        }else{
            printf("Opcao nao encontrada, por favor insira uma opcao valida");
        }
    }

    return 0;
}
