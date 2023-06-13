#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "geral.h"
#include "estoque.h"
/*
void checaEstoque(char **igredientes,  int tamanho) {
    FILE *arquivo = fopen("estoque.txt", "r");
    checaTxt(arquivo);

    int igredientesExistentes = 0;

    for(int i = 0; i < tamanho; i++) {
        char *nomeIgrediente = igredientes[i];

        char linha[1000];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            char nomeProcurado[50];
            snprintf(nomeProcurado, sizeof(nomeProcurado), "nome: %s", nomeIgrediente);
        
            if (strncmp(linha, nomeProcurado, strlen(nomeProcurado)) == 0) {
                igredientesExistentes++;
            }
        }
        
        //redefine o ponteiro de leitura para o início do arquivo antes de iniciar a próxima iteração do loop 
        fseek(arquivo, 0, SEEK_SET);
    }


    if (igredientesExistentes == tamanho) {
        printf("Todos os igredientes estao presentes no estoque.");
    } else {
        printf("Nem todos os igredientes estao presentes no estoque.\nImpossivel preparar o prato solicitado.");
        exit(1);
    }

    fclose(arquivo);
}
*/

/*
void consumirMantimentos(char **mantimentos, int quantidades[], int tamanho) {
    FILE *arquivo = fopen("estoque.txt", "r");
    checaTxt(arquivo);

    FILE *temporario = fopen("temporario.txt", "w");
    
    for (int j = 0; j < tamanho; j++) {
        char linha[1000];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            
            char nomeComparacao[50];
            snprintf(nomeComparacao, sizeof(nomeComparacao), "nome: %s", mantimentos[j]);
            
            if (strncmp(linha, nomeComparacao, strlen(nomeComparacao)) == 0) {
                char nomeMantimento[100];
                int codigoMantimento;
                float precoMantimento;
                int qtdAntigo;
                sscanf(linha, "nome: %s, codigo: %d, preco: %f, quantidade: %d", nomeMantimento, &codigoMantimento, &precoMantimento, &qtdAntigo);
                int qtdNova = qtdAntigo - quantidades[j];
                if (qtdNova == 0) {
                    continue;
                } else {
                    fprintf(temporario, "nome: %s, codigo: %d, preco: %f, quantidade: %d", nomeMantimento, codigoMantimento, precoMantimento, qtdNova);
                    continue;
                }
            }
            fputs(linha, temporario);

        }
    }
    fclose(arquivo);
    fclose(temporario);

    remove("estoque.txt");
    rename("temporario.txt", "estoque.txt");
}
*/

int contarVirgulas(char *str) {
    int contador = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            contador++;
        }
    }
    return contador;
}

void realizarPedido(char *pedido) {
    FILE *arquivo = fopen("cardapio.txt", "r");
    checaTxt(arquivo);

    FILE *arquivoPedido = fopen("pedido.txt", "a");
    checaTxt(arquivoPedido);

    FILE *arquivoCustoPedido = fopen("custopedido.txt", "a");
    checaTxt(arquivoCustoPedido);
    

    char listaIngredientesString[100];
    char qtdIngredientesString[100];

    char linha[1000];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nomePedido[50];
        snprintf(nomePedido, sizeof(nomePedido), "nome: %s", pedido);
        
        if (strncmp(linha, nomePedido, strlen(nomePedido)) == 0) {
            
            //MANIPULANDO OS INGREDIENTES
            char *inicioLista = strstr(linha, "lista: [");
            if (inicioLista != NULL) {
                inicioLista += strlen("lista: [");
                char *fimLista = strchr(inicioLista, ']');
                if (fimLista != NULL) {
                    size_t tamanho = fimLista - inicioLista;
                    strncpy(listaIngredientesString, inicioLista, tamanho);
                    listaIngredientesString[tamanho] = '\0';
                }
            }

            int tamanhoVetor = contarVirgulas(listaIngredientesString) + 1;

            char vetorIngredientes[tamanhoVetor][100];

            char *token;
            token = strtok(listaIngredientesString, ",");
            int index = 0;
            while (token != NULL && index < tamanhoVetor) {
                strcpy(vetorIngredientes[index], token);
                token = strtok(NULL, ",");
                index++;
            }
        
            //checaEstoque((char**)vetorIngredientes,tamanhoVetor); ------------------------------------------------------------------------------------

            //MANIPULANDO A QUANTIDADE
            char *inicioQtd = strstr(linha, "qtd: <");
            if (inicioQtd != NULL) {
                inicioQtd += strlen("qtd: <");
                char *fimQtd = strchr(inicioQtd, '>');
                if (fimQtd != NULL) {
                    size_t tamanho = fimQtd - inicioQtd;
                    strncpy(qtdIngredientesString, inicioQtd, tamanho);
                    qtdIngredientesString[tamanho] = '\0';
                }
            }

            char vetorQtdIngredientes[tamanhoVetor][100];

            char *token2;
            token2 = strtok(qtdIngredientesString, ",");
            index = 0;
            while (token2 != NULL && index < tamanhoVetor) {
                strcpy(vetorQtdIngredientes[index], token2);
                token2 = strtok(NULL, ",");
                index++;
            }
            
            int vetorQtdIngredientesInt[tamanhoVetor];
            for (int i = 0; i < tamanhoVetor; i++) {
                vetorQtdIngredientesInt[i] = atoi(vetorQtdIngredientes[i]);
            }

            //MANIPULANDO PRECO E QUANTIDADE DE MANTIMENTOS
            float custoPrato = 0;
            FILE *arquivoEstoque = fopen("estoque.txt", "r");
            checaTxt(arquivoEstoque);


            for (int i = 0; i < tamanhoVetor; i++) {

                float precoMantimento = 0;
                rewind(arquivoEstoque);

                char linha2[1000];
                while (fgets(linha2, sizeof(linha2), arquivoEstoque) != NULL) {
                    char nomePedido[50];
                    snprintf(nomePedido, sizeof(nomePedido), "nome: %s", vetorIngredientes[i]);
                        
                    
                    if (strncmp(linha2, nomePedido, strlen(nomePedido)) == 0) {
                        char* precoInicio = strstr(linha2, "preco:");
                        if (precoInicio != NULL) {
                            float preco = atof(precoInicio + strlen("preco:"));
                            precoMantimento = preco;
                        }
                    }
                }
                custoPrato+= precoMantimento * vetorQtdIngredientesInt[i];
            }

            //consumirMantimentos((char**)vetorIngredientes, vetorQtdIngredientes, tamanhoVetor); ---------------------------------------------

        
            fprintf(arquivoCustoPedido, "Pedido feito de %s, custando: R$ %f\n", pedido, custoPrato);
            fclose(arquivoEstoque);

            //MANIPULANDO SALDO 
            float precoPrato = 0;
            char* precoInicio = strstr(linha, "preco:");
            if (precoInicio != NULL) {
                float preco = atof(precoInicio + strlen("preco:"));
                precoPrato = preco;
            }
            float lucro = precoPrato - custoPrato;
            
            float saldo = retornaSaldo();
            editarSaldo(saldo+lucro); 
            

            FILE *arquivoLucro = fopen("lucro.txt", "a");
            checaTxt(arquivoLucro);
            char lucroEmString[20];
            snprintf(lucroEmString, sizeof(lucroEmString), "%f", lucro);
            
            fprintf(arquivoLucro, "Lucro prato %s: R$ %s\n", pedido, lucroEmString);
            fclose(arquivoLucro);

            fprintf(arquivoPedido, "Pedido feito de %s, com os seguintes ingredientes: ", pedido);
            for (int j = 0; j < tamanhoVetor; j++) {
                if(vetorQtdIngredientesInt[j] == 1) {
                    fprintf(arquivoPedido, "1 unidade de %s ", vetorIngredientes[j]);
                } else {
                    fprintf(arquivoPedido, "%d unidades de %s ", vetorQtdIngredientesInt[j], vetorIngredientes[j]);
                }
            }
            fprintf(arquivoPedido,"\n");
        }
    }
    fclose(arquivo);
    fclose(arquivoPedido);
    fclose(arquivoCustoPedido);
}