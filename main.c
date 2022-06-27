#include "aux.c"

int main() {

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

    // Variáveis funcionamento da lógica do código
    short patUse = 0;
    short hshUse = 0;
    char *terms[10];
    char term[64];
    int nTerm = 0;
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
            if (DocListVerify(docs))
            {
                printf("\n\t\t\t>> Primeiro, insira um arquivo de entrada na opcao 1");
                continue;
            }
            if (patUse == 0 && hshUse == 0)
            {
                printf("\n\t\t\t>> Primeiro, construa pelo menos um dos indices invertidos");
                continue;
            }
            while(1) {
                printf("\n\t\t\t//====================================================================\\\\ \n");
                printf("\t\t\t||                           Busca de Termos                          ||\n");
                printf("\t\t\t|]====================================================================[|\n");
                printf("\t\t\t||                                                                    ||\n");
                printf("\t\t\t||  1 - Inserir / Alterar termos;                                     ||\n");
                printf("\t\t\t||  2 - Realizar busca de termos;                                     ||\n");
                printf("\t\t\t||  3 - Voltar                                                        ||\n");
                printf("\t\t\t||                                                                    ||\n");
                printf("\t\t\t\\\\====================================================================// \n");
                printf("\n\t\t\t>> Escolha uma das opcoes acima: ");
                scanf("%d",&opcao);
                if (opcao == 1) {
                    printf("\n\t\t\t>> Insira os termos de busca (digite . para concluir): ");
                    nTerm = 0;

                    while (1) {
                        terms[nTerm] = malloc(sizeof (term)+1);
                        printf("\n\t\t\t>> ");
                        scanf("%s", term);
                        if (strcmp(".", term) == 0 || nTerm == 9) {
                            break;
                        }
                        strcpy(terms[nTerm], term);

                        nTerm++;

                    }
                } else if(opcao == 2) {
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
                        scanf("%d", &opcao);
                        float w, relev;
                        if (opcao == 1) {
                            if (patUse == 0) {
                                printf("\n\t\t\t>> Primeiro, construa o indice invetido da PATRICIA");
                                continue;
                            }
                            printf("\n\t\t\t>> Fazendo calculos utilizando a PATRICIA...");
                            for (int i = 1; i <= n; ++i) {
                                for (int j = 0; j < nTerm; ++j) {
                                    w += TermWeightPat(terms[j], i, n, patricia);
                                }
                                float qntPalavras = (float) FindDoc(i, docs)->qntPalavras;
                                relev = (1/(qntPalavras)*w);
                                printf("%f", relev);
                            }

                        } else if (opcao == 2) {
                            if (patUse == 0) {
                                printf("\n\t\t\t>> Primeiro, construa o indice invetido da Tabela Hash");
                                continue;
                            }
                            printf("\n\t\t\t>> Fazendo calculos utilizando a Tabela Hash...");
                            for (int i = 1; i <= n; ++i) {
                                for (int j = 0; j < nTerm; ++j) {
                                    w += TermWeightHsh(terms[j], i, n, hashTable, p);
                                }
                                float qntPalavras = (float) FindDoc(i, docs)->qntPalavras;
                                relev = (1/(qntPalavras)*w);
                                printf("%f", relev);
                            }

                        } else if (opcao == 3) {
                            break;
                        }
                    }
                    // TODO: buscar termos


                } else if(opcao == 3) {
                    break;
                }
            }

        }else if(opcao == 5){
            break;
        }else{
            printf("\n\t\t\t>> Opcao nao encontrada, por favor insira uma opcao valida");
        }
    }

    return 0;
}

