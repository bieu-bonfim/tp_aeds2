#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(){
    FILE *in_ptr, *nxt_ptr;
    char str[50];
    char * bin = (char *) malloc(33);
    char inputfile[50];
    int n = 0;
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
            } else {
                fgets(str, 50, in_ptr);
                printf("%s", str);
            }
        }

        fclose(in_ptr);
        fclose(nxt_ptr);

    }else if(opcao == 2){

    }else if(opcao == 3){

    }else if(opcao == 4){

    }else if(opcao == 5){

    }else{
        printf("Opcao nao encontrada, por favor insira uma opcao valida");
    }


    return 0;
}