#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "geral.h"


void pratoLucrativo() {
    FILE *arquivo = fopen("lucro.txt", "r");
    checaTxt(arquivo);

    char linha[1000];
    float maiorLucro = -FLT_MAX;
    char pratoMaiorLucro[1000];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *pratoInicio = strstr(linha, ": R$ ");
        if (pratoInicio != NULL) {
            float lucro = atof(pratoInicio + strlen(": R$ "));

            if (lucro > maiorLucro) {
                maiorLucro = lucro;
                strcpy(pratoMaiorLucro, linha);
            }
        }
    }

    fclose(arquivo);

    printf("Prato com maior lucro: %s", pratoMaiorLucro);
}

void pratoBolsonaro() {
    FILE *arquivo = fopen("lucro.txt", "r");
    checaTxt(arquivo);

    char linha[1000];
    float menorLucro = FLT_MAX;
    char pratoMenorLucro[1000];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *pratoInicio = strstr(linha, ": R$ ");
        if (pratoInicio != NULL) {
            float lucro = atof(pratoInicio + strlen(": R$ "));

            if (lucro < menorLucro) {
                menorLucro = lucro;
                strcpy(pratoMenorLucro, linha);
            }
        }
    }

    fclose(arquivo);

    printf("Prato com menor lucro: %s", pratoMenorLucro);
}

void infoFinaceiras() {
    FILE *arquivo = fopen("saldo.txt", "r");
    checaTxt(arquivo);

    char linha[1000];
    float saldo = retornaSaldo();

    if (saldo > 1000) {
        printf("Lucro da lanchonete: R$ %.2f\n", saldo-1000);
    } else if (saldo < 1000) {
        printf("Prejuizo da lanchonete: R$ %.2f\n", 1000-saldo);
    } else {
        printf("A lanchonete nao teve lucro nem prejuizo.\n");
    }

    fclose(arquivo);

    pratoLucrativo();
    pratoBolsonaro();
}

void depositarDinheiro(int qtd) {
    FILE *arquivo = fopen("saldo.txt","r+");
    
    float saldo = retornaSaldo();
    
    saldo += qtd;

    editarSaldo(saldo);

    printf("Novo saldo: R$ %.2f\n", saldo);

    fclose(arquivo);
}

void sacarDinheiro(int qtd) {
    FILE *arquivo = fopen("saldo.txt","r+");
    
    float saldo = retornaSaldo();
    
    saldo -= qtd;

    editarSaldo(saldo);
    
    printf("Novo saldo: R$ %.2f\n", saldo);

    fclose(arquivo);
}