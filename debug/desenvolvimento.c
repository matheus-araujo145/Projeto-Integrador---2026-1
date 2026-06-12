#include <stdio.h>
#include <stdlib.h>

#include "../src/include/leitor_csv.h"
#include "../src/include/tabela_hash.h"

int main() {

    int quantidade;

    Produto* produtos = ler_csv("../data/dataset1.csv", &quantidade);

    printf("Quantidade: %d\n", quantidade);

    TabelaHash* hash = criar_tabela(quantidade);

    printf("Hash criada!\n");

    for (int i = 0; i < quantidade; i++) {
        inserir(hash, produtos[i]);
    }

    printf("Produtos inseridos!\n");
    printf("Colisoes: %d\n", hash->colisoes);

    free(produtos);
    liberar_tabela(hash);

    return 0;
}