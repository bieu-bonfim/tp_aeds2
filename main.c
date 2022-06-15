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
    return 0;
}