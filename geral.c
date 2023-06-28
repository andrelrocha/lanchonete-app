#include <stdio.h>
#include <stdlib.h>

void checaTxt(FILE* f) {
    if (f == NULL) {
        printf("Desculpe, database nao disponivel no momento.\n\n");
        exit(1); 
    }
}

void editarSaldo(float saldo) {
    FILE *arquivo = fopen("saldo.txt", "r+");
    checaTxt(arquivo);

    // Transforma o float em uma string para ser gravada no arquivo
    char saldoEmString[20];
    snprintf(saldoEmString, sizeof(saldoEmString), "%.2f", saldo);

    rewind(arquivo);
    fputs(saldoEmString, arquivo);
    fclose(arquivo);
}

float retornaSaldo() {
    FILE *arquivo = fopen("saldo.txt", "r");
    checaTxt(arquivo);

    char linha[20];
    fgets(linha, sizeof(linha), arquivo);

    float saldo = atof(linha);

    fclose(arquivo);
    return saldo;
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