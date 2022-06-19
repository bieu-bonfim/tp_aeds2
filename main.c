#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "estruturas/patricia/patricia.h"

#define SIZE 20


int main(){
    FILE *in_ptr, *nxt_ptr;
    char str[50];
    char **files;
    int n = 0, opcao, set = 0;
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

        if (NULL == in_ptr) {
            printf("O arquivo não foi encontrado.\n");
        }

        while (!feof (in_ptr)) {
            if (n==0) {
                fscanf(in_ptr, "%d", &n);
                files = malloc(n * sizeof(char*));
                for (int i = 0; i < n; i++)
                    files[i] = malloc((SIZE+1) * sizeof(char)); // yeah, I know sizeof(char) is 1, but to make it clear...
            } else {
                fgets(str, 50, in_ptr);
                if (strlen(str) > 4)
                {
                    str[strcspn(str, "\n")] = '\0'; 
                    strcpy(files[set], str);
                    set++;
                }
            }
        }

        fclose(in_ptr);
        // fclose(nxt_ptr);

    }else if(opcao == 2){

    }else if(opcao == 3){

    }else if(opcao == 4){

    }else if(opcao == 5){

    }else{
        printf("Opcao nao encontrada, por favor insira uma opcao valida");
    }


    return 0;
}