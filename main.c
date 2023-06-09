/*
Capacidade de manipulação (adição, remoção, edição e visualização) de um estoque de
mantimentos.
• Cada mantimento deve possuir nome, código, preço e quantidade.
• É possível comprar ingredientes para o estoque apenas se a lanchonete tiver saldo
suficiente para pagar o preço deles.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MANTIMENTOS 100

#define ARQUIVO_ESTOQUE "estoque.txt"

typedef struct {
    char nome[50];
    int codigo;
    float preco;
    int quantidade;
} Mantimento;

typedef struct {
    Mantimento mantimentos[MAX_MANTIMENTOS];
    int quantidadeMantimentos;
    float saldo;
} Estoque;



void adicionarMantimento(Estoque *estoque, const char *nome, int codigo, float preco, int quantidade) {
    if (estoque->quantidadeMantimentos >= MAX_MANTIMENTOS) {
        printf("Estoque cheio!!!\n");
        return;
    }

    Mantimento novoMantimento;
    strcpy(novoMantimento.nome, nome);
    novoMantimento.codigo = codigo;
    novoMantimento.preco = preco;
    novoMantimento.quantidade = quantidade;

    estoque->mantimentos[estoque->quantidadeMantimentos++] = novoMantimento;
}

void removerMantimento(Estoque *estoque, int codigo) {
    char d[10];
    
    printf("Deletar Mantimento");
    scanf(" %s",d);


    
    for (int i = 0; i < estoque->quantidadeMantimentos; i++) {
        if (estoque->mantimentos[i].codigo == codigo) {
            for (int j = i; j < estoque->quantidadeMantimentos - 1; j++) {
                estoque->mantimentos[j] = estoque->mantimentos[j + 1];
            }
            estoque->quantidadeMantimentos--;
            printf("Mantimento removido do estoque.\n");
            return;
        }
    }
    printf("Mantimento com o codigo %d nao encontrado no estoque.\n", codigo);
}

void editarMantimento(Estoque *estoque, int codigo, float novoPreco, int novaQuantidade) {
    for (int i = 0; i < estoque->quantidadeMantimentos; i++) {
        if (estoque->mantimentos[i].codigo == codigo) {
            estoque->mantimentos[i].preco = novoPreco;
            estoque->mantimentos[i].quantidade = novaQuantidade;
            printf("Mantimento editado com sucesso.\n");
            return;
        }
    }
    printf("Mantimento com o codigo %d nao encontrado no estoque.\n", codigo);
}

void visualizarEstoque(const Estoque *estoque) {
    printf("----- Estoque -----\n");
    int i;
    for (i = 0; i < estoque->quantidadeMantimentos; i++) {
        printf("Nome: %s\n", estoque->mantimentos[i].nome);
        printf("Codigo: %d\n", estoque->mantimentos[i].codigo);
        printf("Preco: %.2f\n", estoque->mantimentos[i].preco);
        printf("Quantidade: %d\n", estoque->mantimentos[i].quantidade);
        printf("-------------------\n");
    }
    printf("Saldo disponivel: %.2f\n", estoque->saldo);
}

void salvarEstoque(const Estoque *estoque) {
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo do estoque.\n");
        return;
    }

    fprintf(arquivo, "%d\n", estoque->quantidadeMantimentos);
    fprintf(arquivo, "%.2f\n", estoque->saldo);

    int i;
    for (i = 0; i < estoque->quantidadeMantimentos; i++) {
        fprintf(arquivo, "%s;%d;%.2f;%d\n", estoque->mantimentos[i].nome, estoque->mantimentos[i].codigo,
                estoque->mantimentos[i].preco, estoque->mantimentos[i].quantidade);
    }

    fclose(arquivo);
}

void carregarEstoque(Estoque *estoque) {
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "r");
    if (arquivo == NULL) {
        printf("Arquivo do estoque nao encontrado. Criando novo arquivo.\n");
        return;
    }

    fscanf(arquivo, "%d\n", &estoque->quantidadeMantimentos);
    fscanf(arquivo, "%f\n", &estoque->saldo);

    int i;
    for (i = 0; i < estoque->quantidadeMantimentos; i++) {
        fscanf(arquivo, "%[^;];%d;%f;%d\n", estoque->mantimentos[i].nome, &estoque->mantimentos[i].codigo,
               &estoque->mantimentos[i].preco, &estoque->mantimentos[i].quantidade);
    }

    fclose(arquivo);
}

void comprarMantimento(Estoque *estoque, int codigo, float preco) {
    for (int i = 0; i < estoque->quantidadeMantimentos; i++) {
        if (estoque->mantimentos[i].codigo == codigo) {
            if (estoque->saldo >= preco) {
                estoque->mantimentos[i].quantidade++;
                estoque->saldo -= preco;
                printf("Mantimento comprado com sucesso.\n");
                salvarEstoque(estoque);
            } else {
                printf("Saldo insuficiente para comprar o mantimento.\n");
            }
            return;
        }
    }
    printf("Mantimento com o codigo %d nao encontrado no estoque.\n", codigo);
}

int main() {
    Estoque estoque;
    estoque.quantidadeMantimentos = 0;
    estoque.saldo = 1000.0; // Saldo inicial da lanchonete

    carregarEstoque(&estoque);

    adicionarMantimento(&estoque, "Pão", 1, 1.5, 10);
    adicionarMantimento(&estoque, "Queijo", 2, 3.0, 5);
    adicionarMantimento(&estoque, "Presunto", 3, 2.0, 7);

    visualizarEstoque(&estoque);

    comprarMantimento(&estoque, 2, 3.0); // Compra de queijo
    comprarMantimento(&estoque, 4, 1.5); // Tentativa de compra de mantimento inexistente
    comprarMantimento(&estoque, 1, 5.0); // Tentativa de compra de pão com saldo insuficiente

    visualizarEstoque(&estoque);

    removerMantimento(&estoque, 3); // Remoção de presunto
    editarMantimento(&estoque, 2, 4.0, 3); 
    visualizarEstoque(&estoque);

    salvarEstoque(&estoque); // Salvar o estoque final antes de encerrar o programa
}