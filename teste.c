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

int adicionarMantimento(int saldo, const char *nome, int codigo, float preco, int quantidade) {

    if (saldo - (preco*quantidade) < 0) {
        printf("Saldo insuficiente para pagar o mantimento!\n");
        return 0;
    } else {
        FILE *arquivo = fopen("estoque.txt", "a");

        fprintf(arquivo, "nome: %s, codigo: %d, preco: %.2f, quantidade: %d ", nome, codigo, preco, quantidade);
        fprintf(arquivo, "\n"); 
                    
        fclose(arquivo);
        return saldo - ((preco)*quantidade);
    }
        
    //FALTA ADICIONAR PARTE QUE BUSCA PRODUTOS COM NOME JÁ CADASTRADO E ALTERA A QUANTIDADE
    //TRANSFORMAR ENTRADA DO SCANF EM MINUSCULO
}

int lerMantimento() {
    FILE *arquivo = fopen("estoque.txt", "r");

    char linha[50];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s\n", linha);
    }

    fclose(arquivo);
}










void main() {

    float saldo = 1000.0;
    int escolha;

    printf("Qual operacao voce deseja realizar?\n");
    printf("1-visualizar estoque\n2-adicionar mantimento\n3-comprar mantimento\n4-editar mantimento\n5-remover mantimento\n");
    scanf(" %d", &escolha);

    char nomeMantimento[50];
    int codigoMantimento;
    float precoMantimento;
    int qtdMantimento;

    switch (escolha)
    {
    case 1:
        lerMantimento();
        break;
    case 2: 
        printf("Digite o nome do mantimento: ");
        scanf(" %s", nomeMantimento);

        printf("Digite o codigo do mantimento: ");
        scanf(" %d", &codigoMantimento);

        printf("Digite o preco do mantimento: ");
        scanf(" %.2f", &precoMantimento);

        printf("Digite a quantidade de mantimentos: ");
        scanf(" %d", &qtdMantimento);


        adicionarMantimento(saldo, nomeMantimento, codigoMantimento, precoMantimento, qtdMantimento);
        break;
        break;
    default:
        break;
    }
}