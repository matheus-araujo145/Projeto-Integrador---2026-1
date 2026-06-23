#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/experimento.h"
#include "../include/busca_sequencial.h"
#include "../include/tempo.h"

void gerar_ids_busca(Produto* produtos, int quantidade, int** ids_busca, int* num_ids) {

    int capacidade = 1000;
    *ids_busca = malloc(capacidade * sizeof(int));

    if (*ids_busca == NULL) {
        printf("Erro ao alocar memoria.\n");
        *num_ids = 0;
        return;
    }

    *num_ids = 0;
    int indice = 0;

    // 100 primeiros
    int n_primeiros;
    if (quantidade < 100) {
        n_primeiros = quantidade;
    } else {
        n_primeiros = 100;
    }

    for (int i = 0; i < n_primeiros; i++) {
        (*ids_busca)[indice++] = produtos[i].id;
        (*num_ids)++;
    }

    // 200 do meio
    if (quantidade > 200) {
        int inicio = quantidade / 2 - 100;
        int fim = inicio + 200;

        if (inicio < 0) {
            inicio = 0;
        }
        if (fim > quantidade) {
            fim = quantidade;
        }

        for (int i = inicio; i < fim; i++) {
            (*ids_busca)[indice++] = produtos[i].id;
            (*num_ids)++;
        }
    }

    // 300 finais
    int inicio_finais = quantidade - 300;
    if (inicio_finais < 0) {
        inicio_finais = 0;
    }

    for (int i = inicio_finais; i < quantidade; i++) {
        (*ids_busca)[indice++] = produtos[i].id;
        (*num_ids)++;
    }

    // IDs inexistentes para chegar a 1000+
    int ids_inexistentes = 1000 - (*num_ids);
    for (int i = 0; i < ids_inexistentes; i++) {
        (*ids_busca)[indice++] = -1 - i;
        (*num_ids)++;
    }
}

void salvar_ids_busca(int* ids_busca, int num_ids, const char* nome_arquivo) {

    FILE* arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao criar arquivo de IDs.\n");
        return;
    }

    for (int i = 0; i < num_ids; i++) {
        fprintf(arquivo, "%d\n", ids_busca[i]);
    }

    fclose(arquivo);
    printf("Arquivo %s criado com %d IDs.\n", nome_arquivo, num_ids);
}

int carregar_ids_busca(int** ids_busca, int* num_ids, const char* nome_arquivo) {

    FILE* arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {
        return 0;
    }

    int capacidade = 1000;
    *ids_busca = malloc(capacidade * sizeof(int));

    if (*ids_busca == NULL) {
        printf("Erro ao alocar memoria.\n");
        fclose(arquivo);
        return 0;
    }

    *num_ids = 0;
    int id;

    while (fscanf(arquivo, "%d", &id) == 1) {
        (*ids_busca)[*num_ids] = id;
        (*num_ids)++;

        if (*num_ids >= capacidade) {
            capacidade *= 2;
            int* temp = realloc(*ids_busca, capacidade * sizeof(int));

            if (temp == NULL) {
                printf("Erro ao realocar memoria.\n");
                free(*ids_busca);
                fclose(arquivo);
                return 0;
            }

            *ids_busca = temp;
        }
    }

    fclose(arquivo);
    printf("IDs carregados de %s (%d IDs).\n", nome_arquivo, *num_ids);
    return 1;
}

double executar_protocolo_experimental(Produto* produtos, int quantidade, int* ids_busca, int num_ids) {

    clock_t tempo_inicial = obter_tempo_inicial();

    // Executar as buscas
    for (int i = 0; i < num_ids; i++) {
        busca_sequencial(produtos, quantidade, ids_busca[i]);
    }

    double tempo_total = calcular_tempo_decorrido(tempo_inicial);
    return tempo_total;
}

double executar_protocolo_hash(TabelaHash *hash,int *ids_busca,int num_ids){

    clock_t tempo_inicial = obter_tempo_inicial();

    for (int i = 0; i < num_ids; i++) {
        buscar(hash, ids_busca[i]);
    }

    double tempo_total = calcular_tempo_decorrido(tempo_inicial);

    return tempo_total;
}
