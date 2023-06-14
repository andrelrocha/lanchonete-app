#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estoque.h"
#include "geral.h"
#include "pedido.h"


void main() {

    float saldo = retornaSaldo();
    int escolha;

    char nomeMantimento[50];
    int codigoMantimento;
    float precoMantimento;
    int qtdMantimento;

    char nomePrato[50];

    printf("Qual operacao voce deseja realizar?\n");
    printf("1-visualizar estoque\n2-adicionar mantimento\n3-editar mantimento\n4-remover mantimento\n5-realizar pedido\n");
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
        //printf("Digite o nome do prato do pedido: ");
        //scanf(" %s", &nomePrato);
        //realizarPedido(nomePrato);
        realizarPedido("baiao");
        break;
    default:
        printf("Selecione uma opcao valida.");
        break;
    }
}