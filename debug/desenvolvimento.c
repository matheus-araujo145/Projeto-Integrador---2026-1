#include <stdio.h>
#include <stdlib.h>
#include "leitor_csv.h"

int main() {

    int quantidade = 0;

    Produto* produtos = ler_csv("data/dataset1.csv", &quantidade);

    if (produtos == NULL) {
        return 1;
    }

    printf("Total de produtos: %d\n\n", quantidade);

    //Mostrar os 5 primeiros
    for (int i = 0; i < quantidade && i < 5; i++) {

        printf("%d | %s | %s | %.2f\n",
               produtos[i].id,
               produtos[i].nome,
               produtos[i].categoria,
               produtos[i].valor);
    }

    free(produtos);
    return 0;
}
