#include "../include/busca_sequencial.h"

int busca_sequencial(Produto* produtos, int quantidade, int id) {

    for (int i = 0; i < quantidade; i++) {

        if (produtos[i].id == id) {
            return i;
        }
    }

    return -1;
}
