#include<stdlib.h>
#include<stdio.h>
#include "tabela_hash.h"

//função dada para a tabela hash
int funcao_hash(int id, int tamanho) {

    long long quadrado = (long long)id * id;
    return (quadrado / 100) % tamanho;
}

//criando a tabela hash
TabelaHash* criar_tabela(int tamanho) {

    TabelaHash* hash = malloc(sizeof(TabelaHash));

    if (hash == NULL) {
        return NULL;
    }

    //cria tabela zerada
    hash->tamanho = tamanho;
    hash->colisoes = 0;

    hash->tabela = malloc(tamanho * sizeof(No*));

    if (hash->tabela == NULL) {
        free(hash);
        return NULL;
    }

    //ajusta quantidade de ponteiros para NULL
    for (int i = 0; i < tamanho; i++) {
        hash->tabela[i] = NULL;
    }

    return hash;
}

//inserir produto na tabela hash
void inserir(TabelaHash* hash, Produto produto) {

    int indice = funcao_hash(produto.id, hash->tamanho);

    No* novo = malloc(sizeof(No));

    if (novo == NULL) {
        return;
    }

    novo->produto = produto;
    novo->prox = NULL;

    // Verifica colisão
    if (hash->tabela[indice] != NULL) {
        hash->colisoes++;
    }

    // Insere no início da lista
    novo->prox = hash->tabela[indice];
    hash->tabela[indice] = novo;
}

//buscar produto na tabela hash
Produto* buscar(TabelaHash* tabela, int id) {

    //aplica função hash para encontrar o indice correto
    int indice = funcao_hash(id, tabela->tamanho);

    No* atual = tabela->tabela[indice];

    while (atual != NULL) {

        if (atual->produto.id == id) {
            return &(atual->produto);
        }

        atual = atual->prox;
    }

    return NULL;
}

//desalocar memoria da tabela hash
void liberar_tabela(TabelaHash* tabela) {

    if (tabela == NULL) {
        return;
    }

    for (int i = 0; i < tabela->tamanho; i++) {

        No* atual = tabela->tabela[i];

        while (atual != NULL) {

            No* temp = atual;

            atual = atual->prox;

            free(temp);
        }
    }

    free(tabela->tabela);
    free(tabela);
}