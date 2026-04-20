#ifndef experimento_h
#define experimento_h

#include "leitor_csv.h"

// Gera um vetor de ids para busca seguindo o protocolo experimental
void gerar_ids_busca(Produto* produtos, int quantidade, int** ids_busca, int* num_ids);

// Salva o vetor de IDs em um arquivo de texto
void salvar_ids_busca(int* ids_busca, int num_ids, const char* nome_arquivo);

// Carrega os IDs de um arquivo de texto
int carregar_ids_busca(int** ids_busca, int* num_ids, const char* nome_arquivo);

// Realiza buscas sequenciais e mede o tempo total
double executar_protocolo_experimental(Produto* produtos, int quantidade, int* ids_busca, int num_ids);

#endif