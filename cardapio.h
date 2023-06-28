#ifndef CARDAPIO_H

#define CARDAPIO_H

void checaExistencia(char *nome);
int adicionarRefeicao(int saldo, char *nome, int codigo, float preco, int quantidade);
int visualizarRefeicao();
void alterarRefeicao(char *nome);
void removerRefeicaoCardapio(char *nome);

#endif