#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estoque.h"
#include "geral.h"
#include "pedido.h"
#include "capitalismo.h"
#include "cardapio.h"


void main() {

    float saldo = retornaSaldo();
    int escolha;

    char nomeMantimento[50];
    int codigoMantimento;
    float precoMantimento;
    int qtdMantimento;

    char nomePrato[50];
    int codidoPrato;
    float precoPrato;

    float financeiro = 0;

    printf("Qual operacao voce deseja realizar?\n");
    printf("1-visualizar estoque\n2-adicionar mantimento\n3-editar mantimento\n4-remover mantimento\n5-visualizar cardapio\n6-adicionar prato\n7-editar prato\n8-remover prato\n9-realizar pedido\n10-informacoes financeiras\n11-depositar dinheiro\n12-sacar dinheiro\n13-sair\n");
    scanf(" %d", &escolha);

    switch (escolha)
    {
    case 1:
        lerMantimento();
        break;
    case 2: 
        printf("Digite o nome do mantimento: ");
        scanf(" %s", nomeMantimento);
        checaNome(nomeMantimento);

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
    case 5:
        visualizarCardapio();
        break;
    case 6:
        printf("Digite o nome do prato: ");
        scanf(" %s", &nomePrato);
        checaExistencia(nomePrato);

        printf("Digite o codigo do prato: ");
        scanf(" %d", &codidoPrato);

        printf("Digite o preco do prato: ");
        scanf(" %f", &precoPrato);

        adicionarRefeicao(nomePrato, codidoPrato, precoPrato);
        break;
    case 7:
        //
        break;
    case 8: 
        printf("Digite o nome do prato a ser removido: ");
        scanf(" %s", &nomePrato);
        removerRefeicaoCardapio(nomePrato);
        break;
    case 9: 
        printf("Digite o nome do prato do pedido: ");
        scanf(" %s", &nomePrato);
        realizarPedido(nomePrato);
        break;
    case 10:
        infoFinaceiras();
        break;
    case 11:
        printf("Quanto voce quer depositar: ");
        scanf(" %f", &financeiro);
        depositarDinheiro(financeiro);
        break;
    case 12:
        printf("Quanto voce quer sacar: ");
        scanf(" %f", &financeiro);
        sacarDinheiro(financeiro);
        break;
    case 13:
        exit(1);
        break;
    default:
        printf("Selecione uma opcao valida.");
        break;
    }
}