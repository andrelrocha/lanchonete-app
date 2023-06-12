#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geral.h"


void checaNome(char *nome) {
    FILE *arquivo = fopen("estoque.txt", "r");
    checaTxt(arquivo);

    int encontrado = 0;

    char linha[1000];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nomeComparacao[50];
        snprintf(nomeComparacao, sizeof(nomeComparacao), "nome: %s", nome);
        
        if (strncmp(linha, nomeComparacao, strlen(nomeComparacao)) == 0) {
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if(encontrado==1) {
        printf("O mantimento ja esta cadastrado em nosso database, por favor selecione a opcao de edicao!");
        exit(1); 
    }
}

int adicionarMantimento(int saldo, char *nome, int codigo, float preco, int quantidade) {

    if (saldo - (preco*quantidade) < 0) {
        printf("Saldo insuficiente para pagar o mantimento!\n");
        return 0;
    } else {
        FILE *arquivo = fopen("estoque.txt", "a");
        checaTxt(arquivo);

        fprintf(arquivo, "nome: %s, codigo: %d, preco: %f, quantidade: %d \n", nome, codigo, preco, quantidade);
                    
        fclose(arquivo);

        editarSaldo(saldo - ((preco)*quantidade));
    }
}

int lerMantimento() {
    FILE *arquivo = fopen("estoque.txt", "r");
    checaTxt(arquivo);

    char linha[1000];
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s\n", linha);
    }

    fclose(arquivo);
}

void alterarMantimento(char *nome) {
    FILE *arquivo = fopen("estoque.txt", "r");
    checaTxt(arquivo);

    FILE *temporario = fopen("temporario.txt", "w");

    char linha[1000];

    int codigoMantimento;
    float precoMantimento;
    int qtdMantimento;

    printf("Digite o codigo do mantimento %s: \n", nome);
    scanf("%d", &codigoMantimento);

    printf("Digite o preco do mantimento %s: \n", nome);
    scanf("%f", &precoMantimento);

    printf("Digite a quantidade de mantimentos %s: \n", nome);
    scanf("%d", &qtdMantimento);

    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        
        char nomeComparacao[50];
        snprintf(nomeComparacao, sizeof(nomeComparacao), "nome: %s", nome);
        
        if (strncmp(linha, nomeComparacao, strlen(nomeComparacao)) == 0) {
            int qtdAntigo;
            float precoAntigo;
            
            //checa para conferir se na mudança de qtd e preco, se há uma diminuição do saldo
            if (sscanf(linha, "nome: %*[^,], codigo: %*d, preco: %f, quantidade: %d", &precoAntigo, &qtdAntigo) == 2) {
                float novoValor = precoMantimento*qtdMantimento;
                float antigoValor = precoAntigo*qtdAntigo;

                if (novoValor > antigoValor) {
                    float saldoAtual = retornaSaldo();
                    float diferencaSaldo = novoValor - antigoValor;

                    float saldoFinal = saldoAtual - diferencaSaldo;

                    if(saldoFinal < 0) {
                        printf("Saldo insuficiente para pagar o mantimento!\n");
                        exit(1);
                    }

                    editarSaldo(saldoFinal);
                }
            }
            
            continue;
        }
        
        fputs(linha, temporario);

    }
    fprintf(temporario, "nome: %s, codigo: %d, preco: %f, quantidade: %d \n", nome, codigoMantimento, precoMantimento, qtdMantimento);


    fclose(arquivo);
    fclose(temporario);

    remove("estoque.txt");
    rename("temporario.txt", "estoque.txt");
    
}

void removerMantimento(char *nome) {
    FILE *arquivo = fopen("estoque.txt", "r");
    checaTxt(arquivo);

    FILE *temporario = fopen("temporario.txt", "w");

    char linha[1000];
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nomeComparacao[50];
        snprintf(nomeComparacao, sizeof(nomeComparacao), "nome: %s", nome);
        
        if (strncmp(linha, nomeComparacao, strlen(nomeComparacao)) == 0) {
            continue;
        }
        
        fputs(linha, temporario);
    }

    fclose(arquivo);
    fclose(temporario);

    remove("estoque.txt");
    rename("temporario.txt", "estoque.txt");
}