#ifndef leitor_csv_h
#define leitor_csv_h

typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} Produto;

// Função para ler o csv
Produto* ler_csv(const char* nome_arquivo, int* quantidade);

#endif
