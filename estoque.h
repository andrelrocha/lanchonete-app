#ifndef ESTOQUE_H

#define ESTOQUE_H

void checaNome(char *nome);
int adicionarMantimento(int saldo, char *nome, int codigo, float preco, int quantidade);
int lerMantimento();
void alterarMantimento(char *nome);
void removerMantimento(char *nome);

#endif