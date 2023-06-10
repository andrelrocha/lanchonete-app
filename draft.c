int main() {
    /*
    
    Mantimento novoMantimento;
    strcpy(novoMantimento.nome, nome);
    novoMantimento.codigo = codigo;
    novoMantimento.preco = preco;
    novoMantimento.quantidade = quantidade;
    */


   /*
        FILE *arquivo = fopen("estoque.txt", "r");
        
        char linha[50];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            if (strstr(linha, "nome: ") != NULL) {
                char *nomeEncontrado = strchr(linha, ':') + 2; // Pula o ':' e o espaço após "nome: "
                nomeEncontrado[strcspn(nomeEncontrado, "\n")] = '\0'; // Remove o caractere '\n' do final da linha
                
                if (strcmp(nomeEncontrado, novoMantimento.nome) == 0) {                    
                    

                    
                } else {
                    fclose(arquivo);
                    
                    FILE *arquivo = fopen("estoque.txt", "a");

                    fprintf(arquivo, "nome: %s, codigo: %d, preco: %.2f, quantidade: %d ", novoMantimento.nome, novoMantimento.codigo, novoMantimento.preco, novoMantimento.quantidade);
                    fprintf(arquivo, "\n"); 
                    
                    fclose(arquivo);
                    return saldo - ((novoMantimento.preco)*quantidade);
                }
            }
        }
    }*/
}