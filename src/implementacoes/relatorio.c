#include <stdio.h>
#include "../include/relatorio.h"

void salvar_relatorio(int quantidade, double* tempos, int num_ciclos, int buscas_por_ciclo,
                      int ids_inicio, int ids_meio, int ids_fim, int ids_inexistentes) {

    FILE* arquivo = fopen("relatorio_resultados.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao criar arquivo de relatorio.\n");
        return;
    }

    fprintf(arquivo, "PROTOCOLO EXPERIMENTAL - BUSCA SEQUENCIAL\n\n");

    fprintf(arquivo, "ESPECIFICACOES DO AMBIENTE\n");
    fprintf(arquivo, "Processador: [PREENCHER MANUALMENTE]\n");
    fprintf(arquivo, "Memoria RAM: [PREENCHER MANUALMENTE]\n");
    fprintf(arquivo, "Sistema Operacional: [PREENCHER MANUALMENTE]\n");
    fprintf(arquivo, "Compilador: [PREENCHER MANUALMENTE]\n\n");

    fprintf(arquivo, "DADOS GERAIS\n");
    fprintf(arquivo, "Total de registros: %d\n", quantidade);
    fprintf(arquivo, "Buscas por ciclo: %d\n", buscas_por_ciclo);
    fprintf(arquivo, "Numero de ciclos: %d\n\n", num_ciclos);

    fprintf(arquivo, "DISTRIBUICAO DOS IDS SELECIONADOS\n");
    fprintf(arquivo, "Elementos do inicio do vetor: %d\n", ids_inicio);
    fprintf(arquivo, "Elementos do meio do vetor: %d\n", ids_meio);
    fprintf(arquivo, "Elementos do fim do vetor: %d\n", ids_fim);
    fprintf(arquivo, "Elementos inexistentes: %d\n", ids_inexistentes);
    fprintf(arquivo, "Total: %d\n\n", ids_inicio + ids_meio + ids_fim + ids_inexistentes);

    fprintf(arquivo, "DETALHAMENTO DO PROTOCOLO\n");
    fprintf(arquivo, "O protocolo experimental foi executado conforme as especificacoes:\n");
    fprintf(arquivo, "- %.1f%% dos IDs representam elementos no inicio do vetor\n", 
            (ids_inicio * 100.0) / buscas_por_ciclo);
    fprintf(arquivo, "- %.1f%% representam elementos no meio do vetor\n", 
            (ids_meio * 100.0) / buscas_por_ciclo);
    fprintf(arquivo, "- %.1f%% representam elementos no fim do vetor\n", 
            (ids_fim * 100.0) / buscas_por_ciclo);
    fprintf(arquivo, "- %.1f%% sao IDs comprovadamente inexistentes (valores negativos)\n", 
            (ids_inexistentes * 100.0) / buscas_por_ciclo);
    fprintf(arquivo, "\nEsta distribuicao garante cobertura de todos os cenarios:\n");
    fprintf(arquivo, "1. Busca em elemento encontrado rapidamente (inicio)\n");
    fprintf(arquivo, "2. Busca em elemento intermediario\n");
    fprintf(arquivo, "3. Busca em elemento encontrado lentamente (fim)\n");
    fprintf(arquivo, "4. Busca em elemento inexistente (pior caso)\n\n");

    fprintf(arquivo, "RESULTADOS DOS TESTES\n");
    fprintf(arquivo, "Ciclo | Tempo Total (s) | Tempo Medio (s)\n");

    double tempo_total_geral = 0.0;

    for (int i = 0; i < num_ciclos; i++) {

        double tempo_medio = tempos[i] / buscas_por_ciclo;
        fprintf(arquivo, "%d | %.10f | %.10f\n", i + 1, tempos[i], tempo_medio);
        tempo_total_geral += tempos[i];
    }

    double tempo_medio_geral = tempo_total_geral / (num_ciclos * buscas_por_ciclo);
    double tempo_medio_ciclos = tempo_total_geral / num_ciclos;

    fprintf(arquivo, "\nMEDIA | %.10f | %.10f\n\n", tempo_medio_ciclos, tempo_medio_geral);

    fprintf(arquivo, "ANALISE PRELIMINAR\n\n");

    fprintf(arquivo, "1. Comportamento Observado:\n");
    fprintf(arquivo, "Tempo medio por busca: %.10f segundos\n", tempo_medio_geral);
    fprintf(arquivo, "Algoritmo: Busca Sequencial\n");
    fprintf(arquivo, "Complexidade teorica: O(n)\n\n");

    fprintf(arquivo, "2. Relacao entre Tamanho do Vetor e Tempo de Busca:\n");
    fprintf(arquivo, "Total de registros: %d\n", quantidade);
    fprintf(arquivo, "Buscas realizadas: %d por ciclo\n", buscas_por_ciclo);
    fprintf(arquivo, "Tempo medio final: %.10f segundos\n\n", tempo_medio_geral);

    fprintf(arquivo, "3. Limitacoes da Busca Sequencial:\n");
    fprintf(arquivo, "- Deve percorrer ate n elementos no pior caso\n");
    fprintf(arquivo, "- Sem dependencia da ordem dos dados\n");
    fprintf(arquivo, "- Ineficiente para grandes volumes de dados\n");
    fprintf(arquivo, "- Sera comparada com Tabela Hash na Fase II\n");

    fclose(arquivo);
    printf("Relatorio salvo em: relatorio_resultados.txt\n");
}