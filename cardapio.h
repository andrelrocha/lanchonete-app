#ifndef CARDAPIO_H

#define CARDAPIO_H

void checaExistencia(char *nome);
void adicionarRefeicao(char *nome, int codigo, float preco);
int visualizarRefeicao();
void alterarRefeicao(char *nome);
void removerRefeicaoCardapio(char *nome);

#endif