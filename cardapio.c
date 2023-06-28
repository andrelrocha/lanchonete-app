#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "geral.h"
//-------------------------------------------------------------------------------------------------------------
void checaExistencia(char *nome) {
    FILE *arquivo = fopen("cardapio.txt", "r");
    checaTxt(arquivo);

    int encontrado = 0;
    char linha[1000];
  
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nomeComparacao[50];
        snprintf(nomeComparacao, sizeof(nomeComparacao), "nome: %s", nome);
        
        if (strncmp(linha, nomeComparacao, strlen(nomeComparacao)) == 0) {
            encontrado = 1;
          break;
        }
    }

    fclose(arquivo);

    if(encontrado==1) {
        printf("O item ja esta cadastrado no cardápio, por favor selecione a opcao de edicao!");
        exit(1); 
    }
}
//-------------------------------------------------------------------------------------------------------------

    void fazerRefeicao(int codigo, double preco, char nomes[][50], int quantidades[], int numIngredientes) {
    FILE *arquivo = fopen("cardapio.txt", "a");
    checaTxt(arquivo);

    for (int i = 0; i < numIngredientes; i++) {
        if (quantidades[i] <= 0) {
            printf("Ingredientes insuficientes para fazer a refeição!\n");
            return;
        }
    }

    fprintf(arquivo, "Código: %d\n Preço: %.2f\n", codigo, preco);
    for (int i = 0; i < numIngredientes; i++) {
        fprintf(arquivo, "Nome: %s, Quantidade: %d\n", nomes[i], quantidades[i]);
    }
    
    fclose(arquivo);

}
//-------------------------------------------------------------------------------------------------------------
void adicionarRefeicao(char *nome, int codigo, float preco, char ingredientesNecessarios[], int qnt[]) {
    FILE *arquivo = fopen("cardapio.txt", "a");
    checaTxt(arquivo);

    fprintf(arquivo, "Nome: %s\n Código: %d\n Preço: %.2f\n Ingredientes Necessários: %s\n Qnt: %d\n", nome, codigo, preco, ingredientesNecessarios, qnt);

    fclose(arquivo);

    printf("Refeição adicionada ao cardápio.\n");
}


//---------------------------------------------------------------------------------------------------------------
void removerRefeicaoCardapio(const char *nome) {
    FILE *arquivo = fopen("cardapio.txt", "r");
    checaTxt(arquivo);

    FILE *temporario = fopen("temporario.txt", "w");
    checaTxt(temporario);

    int encontrado = 0;

    char linha[1000];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *token = strtok(linha, ",");
        if (token != NULL && strcmp(token, nome) == 0) {
            encontrado = 1;
        } else {
            fputs(linha, temporario);
        }
    }
    if (encontrado) {
        printf("Alimento %s removido do cardápio.\n", nome);
    } else {
        printf("Alimento %s não encontrado no cardápio.\n", nome);
    }

    fclose(arquivo);
    fclose(temporario);

    remove("cardapio.txt");

    rename("temporario.txt", "cardapio.txt");
}
  
//-------------------------------------------------------------------------------------------------------------
void editarCardapio(char *nome) {
    FILE *arquivo = fopen("cardapio.txt", "r");
    checaTxt(arquivo);

    FILE *temporario = fopen("temporario.txt", "w");
    checaTxt(arquivo);

    int codigoAlimento;
    float precoAlimento;
    int qtdAlimento;

    printf("Digite o novo codigo da refeição %s: \n", nome);
    scanf("%d", &codigoAlimento);

    printf("Digite o novo preco da refeição %s: \n", nome);
    scanf("%f", &precoAlimento);

    printf("Digite a nova quantidade de pratos %s: \n", nome);
    scanf("%d", &qtdAlimento);
  
    char linha[1000];
  
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nomeComparacao[50];
        snprintf(nomeComparacao, sizeof(nomeComparacao), "Nome: %s", nome);
        
        if (strncmp(linha, nomeComparacao, strlen(nomeComparacao)) == 0) {
        fprintf(temporario, "Nome: %s\nCódigo: %d\nPreço: %.2f\nQuantidade: %d\n\n", nome, codigoAlimento, precoAlimento, qtdAlimento);
        encontrado = 1;
        } else {
        fputs(linha, temporario);
          }
    }
  //falta alterar saldo
  
   // Olhando se o alimento foi encontrado
    if (encontrado) {
        printf("Alimento %s alterado com sucesso!\n", nome);
    } else {
        printf("Alimento %s não encontrado.\n", nome);
    }

    // Fechando os arquivos aqui
    fclose(arquivo);
    fclose(temporario);

    // Apaga o arquivo de cardápio
    remove("cardapio.txt");

    // Troca de nome
    rename("temporario.txt", "cardapio.txt");
//------------------------------------------------------------------------------------------------------------
void visualizarCardapio() {
    FILE *arquivo = fopen("cardapio.txt", "r");
    checaTxt(arquivo);

    char linha[1000];
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s\n", linha);
    }

    fclose(arquivo);
}
