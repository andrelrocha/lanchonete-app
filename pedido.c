#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geral.h"

/*
Capacidade de registrar um pedido feito por um cliente, contendo as comidas e suas respectivas quantidades.
• Uma comida só pode ser preparada se todos os seus ingredientes estiverem disponíveis no estoque. • O sistema deve calcular o preço de venda das comidas, que será o lucro. • O sistema deve registrar o custo total dos mantimentos utilizados em cada porção da comida pedida.
*/

void realizarPedido(char *pedido) {
    
    
    
    
    //comidas e quantidades { puxar info do cardápio, pedido.txt }
    //conferir no estoque.txt se todos os igredientes existem no estoque




    //calcular o preço { puxar preco do cardapio.txt } { puxar preco de todos os mantimentos }
    //deve adicionar o saldo.txt a partir do lucro

    //registrar em custo.txt o custo de cada pedido

    //nome: baiao, codigo: 123, preco: 20.0, lista: [arroz,feijao]

}

void checaEstoque(char igredientes[],  int tamanho) {
    FILE *arquivo = fopen("estoque.txt", "r");
    checaTxt(arquivo);

    int igredientesExistentes = 0;

    for(int i = 0; i < tamanho; i++) {
        char nomeIgrediente = igredientes[i];

        char linha[1000];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            char nomeProcurado[50];
            snprintf(nomeProcurado, sizeof(nomeProcurado), "nome: %s", nomeIgrediente);
        
            if (strncmp(linha, nomeProcurado, strlen(nomeProcurado)) == 0) {
                igredientesExistentes++;
            }
        }
        
        //redefine o ponteiro de leitura para o início do arquivo antes de iniciar a próxima iteração do loop 
        fseek(arquivo, 0, SEEK_SET);
    }

    if (igredientesExistentes == tamanho) {
        printf("Todos os igredientes estao presentes no estoque");
    } else {
        printf("Nem todos os igredientes estao presentes no estoque.\nImpossivel preparar o prato solicitado.");
        exit(1);
    }

    fclose(arquivo);
}