#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include "leitor_csv.h"

//nós da tabela hash
typedef struct No {
    Produto produto;
    struct No* prox;
} No;

//estrutura da tabela hash
typedef struct {
    No** tabela;
    int tamanho;
    int colisoes;
} TabelaHash;

//função determinada para a tabela hash
int funcao_hash(int id, int tamanho);

//criar tabela hash
TabelaHash* criar_tabela(int tamanho);

//inserir produto na tabela hash
void inserir(TabelaHash* tabela, Produto produto);

//buscar produto na tabela hash
Produto* buscar(TabelaHash* tabela, int id);

//liberar memoria da tabela hash
void liberar_tabela(TabelaHash* tabela);

#endif
