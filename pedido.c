#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "geral.h"
#include "estoque.h"

int checaEstoque(char *ingrediente) {
    FILE *arquivo = fopen("estoque.txt", "r");
    checaTxt(arquivo);

    char linha[1000];
    fseek(arquivo, 0, SEEK_SET);  // redefine o ponteiro de leitura para o início do arquivo

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nomeProcurado[50];
        snprintf(nomeProcurado, sizeof(nomeProcurado), "nome: %s", ingrediente);
        
        if (strncmp(linha, nomeProcurado, strlen(nomeProcurado)) == 0) {
            return 1;
        }
    }

    return 0;

    fclose(arquivo);
}

void realizarPedido(char *pedido) {
    FILE *arquivo = fopen("cardapio.txt", "r");
    checaTxt(arquivo);

    char linha[1000];
    int encontrado = 0;
    while(fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nomePedido[50];
        snprintf(nomePedido, sizeof(nomePedido), "nome: %s", pedido);
        
        if (strncmp(linha, nomePedido, strlen(nomePedido)) == 0) {
            encontrado = 1;
        }
    }

    if(encontrado == 0) {
        printf("O prato nao esta presente no cardapio!");
        exit(1);
    }

    rewind(arquivo);

    FILE *arquivoPedido = fopen("pedido.txt", "a");
    checaTxt(arquivoPedido);

    FILE *arquivoCustoPedido = fopen("custopedido.txt", "a");
    checaTxt(arquivoCustoPedido);
    

    char listaIngredientesString[100];
    char qtdIngredientesString[100];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nomePedido[50];
        snprintf(nomePedido, sizeof(nomePedido), "nome: %s", pedido);
        
        if (strncmp(linha, nomePedido, strlen(nomePedido)) == 0) {
            
            //MANIPULANDO OS INGREDIENTES
            /*procura pela substring "lista: [" e extrai a lista de ingredientes encontrada entre colchetes.*/
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

            int armazenaContador = 0;
                
            for (int i = 0; i < tamanhoVetor; i++) {
                armazenaContador += checaEstoque(vetorIngredientes[i]);
                if (checaEstoque(vetorIngredientes[i]) == 0) {
                    printf("O ingrediente %s nao esta presente no estoque.\nImpossivel preparar o prato solicitado.", vetorIngredientes[i]);
                    exit(1);
                }
            }

            if (armazenaContador == tamanhoVetor) {
                printf("Todos os igredientes estao presentes no estoque.");
            } 
            

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
        
            fprintf(arquivoCustoPedido, "Pedido feito de %s, custando: R$ %.2f\n", pedido, custoPrato);
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
            snprintf(lucroEmString, sizeof(lucroEmString), "%.2f", lucro);
            
            fprintf(arquivoLucro, "%s: R$ %s\n", pedido, lucroEmString);
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