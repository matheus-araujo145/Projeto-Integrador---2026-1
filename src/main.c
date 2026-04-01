#include <stdio.h>
#include <stdlib.h>
#include "./include/leitor_csv.h"

int main() { //Lê o csv e cria arquvio .txt dos ids selecionados para usar nas buscas, padronizando os dados

    int quantidade = 0;

    // Lê csv
    Produto* produtos = ler_csv("../data/dataset1.csv", &quantidade);
    if (!produtos) return 1;

    // ve se o arquivo ja existe
    FILE* f = fopen("ids_selecionados.txt", "r");

    if (!f) {

        // cria se não existir
        f = fopen("ids_selecionados.txt", "w");

        if (!f) {

            printf("Erro ao criar arquivo.\n");
            free(produtos);
            return 1;
        }

        // 100 primeiros
        int n_primeiros = quantidade < 100 ? quantidade : 100;

        for (int i = 0; i < n_primeiros; i++)

            fprintf(f, "%d\n", produtos[i].id);

        // 200 do meio
        if (quantidade > 200) {

            int inicio = quantidade / 2 - 100;
            int fim = inicio + 200;

            if (inicio < 0) inicio = 0;

            if (fim > quantidade) fim = quantidade;

            for (int i = inicio; i < fim; i++)

                fprintf(f, "%d\n", produtos[i].id);
        }

        // 300 finais
        int inicio_finais = quantidade - 300;

        if (inicio_finais < 0) inicio_finais = 0;

        for (int i = inicio_finais; i < quantidade; i++)

            fprintf(f, "%d\n", produtos[i].id);

        fclose(f);
        printf("Arquivo ids_selecionados.txt criado.\n");

    } else {

        // se existir só fecha
        fclose(f);
        printf("Arquivo ids_selecionados.txt já existe\n");
    }

    f = fopen("ids_selecionados.txt", "r");

    if (!f) {

        printf("Erro ao abrir arquivo de IDs.\n");
        free(produtos);
        return 1;
    }

    int id;
    printf("\n");
    while (fscanf(f, "%d", &id) == 1) {

        for (int i = 0; i < quantidade; i++) {

            if (produtos[i].id == id) {

                printf("ID: %d | Nome: %s | Categoria: %s | Valor: %.2f\n",
                       produtos[i].id,
                       produtos[i].nome,
                       produtos[i].categoria,
                       produtos[i].valor);

                break;
            }
        }
    }

    fclose(f);
    free(produtos);
    return 0;
}
