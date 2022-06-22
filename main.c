#include <math.h>
#include "estruturas/patricia/patricia.h"

#define SIZE 20

void InsertWords (char * fileName, int idDoc, PatAp * a) {
    unsigned char str[1024];
    FILE *doc;
    doc = fopen(fileName, "r");

    while (fscanf(doc, " %1023s", str) == 1) {
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
            in_ptr = fopen("input.txt", "r");
            for (int i = 0; i < n; i++)
            {
                free(files[i]);
            }
            free(files);
            
            if (NULL == in_ptr) {
                printf("O arquivo não foi encontrado.\n");
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
                InsertWords(files[i], i+1, &a);
            }

        }else if(opcao == 3){

        }else if(opcao == 4){

        }else if(opcao == 5){
            break;
        }else{
            printf("Opcao nao encontrada, por favor insira uma opcao valida");
        }
    }

    return 0;
}
