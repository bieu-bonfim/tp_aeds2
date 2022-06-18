
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void){
  

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
  temp = strtok(palavras, " ");
  while(temp != NULL){
  printf("%s\n",temp);
  temp = strtok(NULL, " " );
}
free(line); 
fclose(arquivo);
fclose(arquivo2);
 
return 0;
}


