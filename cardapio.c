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

    int enc = 0;

    char linha[1000];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nomeComparacao[50];
        snprintf(nomeComparacao, sizeof(nomeComparacao), "nome: %s", nome);
        
        if (strncmp(linha, nomeComparacao, strlen(nomeComparacao)) == 0) {
            enc = 1;
            continue;
        }
        
        fputs(linha, temporario);
    }

    if (enc == 0) {
        printf("Prato nao encontrado.\n");
    } else {
        printf("Prato removido com sucesso.\n");
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

    char linha[1000];
    int encontrado = 0;

    while(fgets(linha, sizeof(linha),arquivo) != NULL) {
        char nomeComparacao[50];
        snprintf(nomeComparacao, sizeof(nomeComparacao), "nome: %s", nome);
        
        if (strncmp(linha, nomeComparacao, strlen(nomeComparacao)) == 0) {
            encontrado = 1;
            break;
        }
    }

    if(encontrado == 0) {
        printf("Prato %s nao encontrado.\n", nome);
        exit(1);
    }

    rewind(arquivo);

    int codigoAlimento;
    float precoAlimento;

    char qtdAlimentoStr[1000];
    char listaAlimentosStr[1000];
    
    sscanf(linha, "nome: %*[^,], codigo: %*[^,], preco: %*[^,], lista: [%[^]]], qtd: <%[^>]>", listaAlimentosStr, qtdAlimentoStr);

    int qtdAlimentosInt = contarVirgulas(qtdAlimentoStr) + 1;
    
    int qtdAlimentos[qtdAlimentosInt];

    printf("Digite o novo codigo da refeicao %s: \n", nome);
    scanf("%d", &codigoAlimento);

    printf("Digite o novo preco da refeicao %s: \n", nome);
    scanf("%f", &precoAlimento);

    printf("Os ingredientes para o prato %s sao: %s\n", nome, listaAlimentosStr);

    for (int i = 0; i < qtdAlimentosInt; i++) {
        printf("Digite a nova quantidade do ingrediente %d: \n", i+1);
        scanf("%d", &qtdAlimentos[i]);
    }

    char qtdsString[1000];
    qtdsString[0] = '\0';
    for (int i = 0; i < qtdAlimentosInt; i++) {
        char qtdString[10];
        snprintf(qtdString, sizeof(qtdString), "%d", qtdAlimentos[i]);
        strcat(qtdsString, qtdString);
        if (i != qtdAlimentosInt - 1) {
            strcat(qtdsString, ",");
        }
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        char nomeComparacao[50];
        snprintf(nomeComparacao, sizeof(nomeComparacao), "nome: %s", nome);
        
        if (strncmp(linha, nomeComparacao, strlen(nomeComparacao)) == 0) {
            fprintf(temporario, "nome: %s, codigo: %d, preco: %.2f, lista: [%s], qtd: <%s>\n", nome, codigoAlimento, precoAlimento, listaAlimentosStr, qtdsString);
        } else {
            fputs(linha, temporario);
        }
    }
  
    printf("Alimento %s alterado com sucesso!\n", nome);
    
    fclose(arquivo);
    fclose(temporario);

    remove("cardapio.txt");
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
