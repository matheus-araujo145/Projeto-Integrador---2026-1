#include <time.h>
#include "../include/tempo.h"

clock_t obter_tempo_inicial(void) {

    return clock();
}

double calcular_tempo_decorrido(clock_t tempo_inicial) {

    clock_t tempo_final = clock();
    double duracao = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    return duracao;
}