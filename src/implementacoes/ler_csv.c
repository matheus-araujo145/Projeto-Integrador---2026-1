#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/leitor_csv.h"

Produto* ler_csv(const char* nome_arquivo, int* quantidade) {

    FILE* arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {

        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    int capacidade = 100;
    Produto* produtos = malloc(capacidade * sizeof(Produto));

    if (produtos == NULL) {

        printf("Erro de alocação de memória.\n");
        fclose(arquivo);
        return NULL;
    }

    *quantidade = 0;
    char linha[256];
    int registros_invalidos = 0;

    //Pular cabeçalho
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {

        //Aumenta se necessário
        if (*quantidade >= capacidade) {

            capacidade *= 2;
            Produto* temp = realloc(produtos, capacidade * sizeof(Produto));

            if (temp == NULL) {

                printf("Erro ao realocar memória.\n");
                free(produtos);
                fclose(arquivo);
                return NULL;
            }

            produtos = temp;
        }

        Produto p;

        //Quebrar linha do CSV usando strtok
        char* token = strtok(linha, ","); // strtok divide a string 'linha' pelos delimitadores ',' e retorna o primeiro token

        //ID
        if (token == NULL) continue;
        p.id = atoi(token);

        if (p.id <= 0) {
            registros_invalidos++;
            continue;
        }

        //Nome
        token = strtok(NULL, ","); // strtok continua dividindo, usando NULL para processar a string anterior
        if (token == NULL) continue;
        strncpy(p.nome, token, 50); // strncpy copia até 50 caracteres do token para o campo nome (evita overflow)
        p.nome[50] = '\0';

        if (strlen(p.nome) == 0) {
            registros_invalidos++;
            continue;
        }

        //Categoria
        token = strtok(NULL, ","); // strtok obtém o próximo token separado por vírgula
        if (token == NULL) continue;
        strncpy(p.categoria, token, 30); // strncpy copia até 30 caracteres do token para o campo categoria
        p.categoria[30] = '\0';

        if (strlen(p.categoria) == 0) {
            printf("Registro %d ignorado: categoria vazia.\n", p.id);
            continue;
        }

        //Valor
        token = strtok(NULL, ",");
        if (token == NULL) continue;
            p.valor = atof(token);

        if (p.valor < 0) {
            printf("Registro %d ignorado: valor invalido.\n", p.id);
            continue;
        }

        p.nome[strcspn(p.nome, "\n")] = '\0'; // strcspn encontra a posição do caractere '\n' em p.nome e substitui por '\0' para remover quebra

        p.categoria[strcspn(p.categoria, "\n")] = '\0'; // strcspn encontra a posição do caractere '\n' em p.categoria e substitui por '\0' para remover quebra

        produtos[*quantidade] = p;
        (*quantidade)++;
    }
    printf("\nVALIDACAO DOS DADOS\n");
    printf("Registros validos: %d\n", *quantidade);
    printf("Registros invalidos: %d\n", registros_invalidos);

    fclose(arquivo);
    return produtos;
}
