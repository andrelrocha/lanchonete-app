#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_ESTOQUE "estoque.txt"

void checaTxt(FILE* f) {
    if (f == 0) {
        printf("Desculpe, database nao disponivel no momento.\n\n");
        exit(1); 
    }
}

void editarSaldo(float saldo) {
    FILE *arquivo = fopen("saldo.txt", "r+");
    checaTxt(arquivo);

    //transforma o inteiro em char para ser passado para fputs
    char saldoEmString[20];
    snprintf(saldoEmString, sizeof(saldoEmString), "%f", saldo);

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

int adicionarMantimento(int saldo, const char *nome, int codigo, float preco, int quantidade) {

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

    //ADICIONAR QUESTÃO DE EDIÇÃO SOMENTE DA QUANTIDADE { O MANTIMENTO DESEJADO JÁ EXISTE EM NOSSo DATABASE, POR FAVOR }
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

//ANALISAR QUESTÃO DO SALDO E MUDANÇA (TALVEZ POR O SALDO EM UM ARQUIVO SEPARADO AO INVÉS DA VARIÁVEL??!!)

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
            continue;
        }
        
        fputs(linha, temporario);

    }
        fprintf(temporario, "nome: %s, codigo: %d, preco: %.2f, quantidade: %d \n", nome, codigoMantimento, precoMantimento, qtdMantimento);
    


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






void main() {

    float saldo = retornaSaldo();
    int escolha;

    char nomeMantimento[50];
    int codigoMantimento;
    float precoMantimento;
    int qtdMantimento;

    printf("Qual operacao voce deseja realizar?\n");
    printf("1-visualizar estoque\n2-adicionar mantimento\n3-editar mantimento\n4-remover mantimento\n");
    scanf(" %d", &escolha);

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
        scanf(" %f", &precoMantimento);

        printf("Digite a quantidade de mantimentos: ");
        scanf(" %d", &qtdMantimento);

        adicionarMantimento(saldo, nomeMantimento, codigoMantimento, precoMantimento, qtdMantimento);
        break;
    case 3:
        printf("Digite o nome do mantimento a ser alterado: ");
        scanf(" %s", &nomeMantimento);
        alterarMantimento(nomeMantimento);
        break;
    case 4:
        printf("Digite o nome do mantimento a ser removido: ");
        scanf(" %s", &nomeMantimento);
        removerMantimento(nomeMantimento);
        break;
    default:
        break;
    }
}