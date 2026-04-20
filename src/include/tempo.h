#ifndef tempo_h
#define tempo_h

#include <time.h>

clock_t obter_tempo_inicial(void);

// Retorna o tempo decorrido em segundos
double calcular_tempo_decorrido(clock_t tempo_inicial);

#endif