#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "geral.h"

/*
Capacidade de registrar um pedido feito por um cliente, contendo as comidas e suas respectivas quantidades.
• Uma comida só pode ser preparada se todos os seus ingredientes estiverem disponíveis no estoque. • O sistema deve calcular o preço de venda das comidas, que será o lucro. • O sistema deve registrar o custo total dos mantimentos utilizados em cada porção da comida pedida.
*/

void checaEstoque(char igredientes[],  int tamanho) {
    FILE *arquivo = fopen("estoque.txt", "r");
    checaTxt(arquivo);

    int igredientesExistentes = 0;

    for(int i = 0; i < tamanho; i++) {
        char nomeIgrediente = igredientes[i];

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


    // FALTA EDITAR A QUANTIDADE DE MANTIMENTOS E PRIMEIRO VER SE PODE OU NÃO FAZER O PRATO

    if (igredientesExistentes == tamanho) {
        printf("Todos os igredientes estao presentes no estoque.");
    } else {
        printf("Nem todos os igredientes estao presentes no estoque.\nImpossivel preparar o prato solicitado.");
        exit(1);
    }

    fclose(arquivo);
}

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

    FILE *arquivoCustoPedido = fopen("custoPedido.txt", "a");
    checaTxt(arquivoCustoPedido);
    

    char listaIngredientesString[100];

    char linha[1000];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nomePedido[50];
        snprintf(nomePedido, sizeof(nomePedido), "nome: %s", pedido);
        
        if (strncmp(linha, nomePedido, strlen(nomePedido)) == 0) {
            //MANIPULANDO OS INGREDIENTES
            sscanf(linha, "lista: [%[^]]", listaIngredientesString);

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
        
            checaEstoque(vetorIngredientes,tamanhoVetor);

            //MANIPULANDO A QUANTIDADE
            int qtdIngredientes[tamanhoVetor];
            sscanf(linha, "qtd: <%[^>]", qtdIngredientes);
            char *token2;
            token2 = strtok(qtdIngredientes, ",");
            index = 0;
            while (token2 != NULL && index < tamanhoVetor) {
                strcpy(vetorIngredientes[index], token2);
                token2 = strtok(NULL, ",");
                index++;
            }

            //MANIPULANDO PRECO E QUANTIDADE DE MANTIMENTOS
            float custoPrato = 0;
            FILE *arquivoEstoque = fopen("estoque.txt", "r");
            checaTxt(arquivoEstoque);
            for (int i = 0; i < tamanhoVetor; i++) {

                float precoMantimento = 0;

                char linha2[1000];
                while (fgets(linha2, sizeof(linha2), arquivoEstoque) != NULL) {
                    char nomePedido[50];
                    snprintf(nomePedido, sizeof(nomePedido), "nome: %s", vetorIngredientes[i]);
                    
                    if (strncmp(linha2, nomePedido, strlen(nomePedido)) == 0) {
                        sscanf(linha2, "preco: %f", &precoMantimento);
                    }
                
                custoPrato+= precoMantimento * qtdIngredientes[i];
                }
            }

            fprintf(arquivoCustoPedido, "Pedido feito de %s, custando: R$ %f", pedido, custoPrato);
            fclose(arquivoEstoque);

            //MANIPULANDO SALDO 
            float precoPrato = 0;
            sscanf(linha, "preco: %f", &precoPrato);
            float lucro = precoPrato - custoPrato;

            float saldo = retornaSaldo();
            editarSaldo(saldo+lucro);

            fprintf(arquivoPedido, "Pedido feito de %s, com os seguintes igredientes: ", pedido);
            for (int j = 0; j < tamanhoVetor; j++) {
                if(qtdIngredientes[j] == 1) {
                    fprintf(arquivoPedido, "1 unidade de %s ", vetorIngredientes[j]);
                } else {
                    fprintf(arquivoPedido, "%d unidades de %s", qtdIngredientes[j], vetorIngredientes[j]);
                }
            }
            fprintf(arquivoPedido,"\n");
        }
    }

    fclose(arquivo);
    fclose(arquivoPedido);
    fclose(arquivoCustoPedido);
}