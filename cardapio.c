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
        printf("O item ja esta cadastrado no cardapio, por favor selecione a opcao de edicao!");
        exit(1); 
    }
}

//-------------------------------------------------------------------------------------------------------------
void adicionarRefeicao(char *nome, int codigo, float preco) {
    FILE *arquivo = fopen("cardapio.txt", "a");
    checaTxt(arquivo);

    int esc = 0;
    printf("Quantos ingredientes o prato possui?\n");
    scanf(" %d", &esc);

    char ingredientesNecessarios[esc][100];
    for(int i = 0; i < esc; i++) {
        printf("Digite o nome do ingrediente %d: \n", i+1);
        scanf(" %s", ingredientesNecessarios[i]);
    }

    char ingredientesString[1000];
    ingredientesString[0] = '\0';
    for (int i = 0; i < esc; i++) {
        strcat(ingredientesString, ingredientesNecessarios[i]);
        if (i != esc - 1) {
            strcat(ingredientesString, ",");
        }
    }   

    char qtds[esc][100];
    for(int i = 0; i < esc; i++) {
        printf("Digite a quantidade do ingrediente %s: \n", ingredientesNecessarios[i]);
        scanf(" %s", &qtds[i]);
    }

    char qtdsString[1000];
    qtdsString[0] = '\0';
    for (int i = 0; i < esc; i++) {
        strcat(qtdsString, qtds[i]);
        if (i != esc - 1) {
            strcat(qtdsString, ",");
        }
    }


    fprintf(arquivo, "\nnome: %s, codigo: %d, preco: %.2f, lista: [%s], qtd: <%s>", nome, codigo, preco, ingredientesString, qtdsString);

    fclose(arquivo);

    printf("Refeicao adicionada ao cardapio.\n");
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
}
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
