/*
Geração de relatórios que mostrem o lucro ou prejuízo da lanchonete, além das seguintes informações:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "geral.h"


void pratoLula() {
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