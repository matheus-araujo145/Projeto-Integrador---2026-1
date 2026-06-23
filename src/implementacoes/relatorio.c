#include <stdio.h>
#include "../include/relatorio.h"

void salvar_relatorio(int quantidade, double* tempos_seq, double* tempos_hash, int colisoes, int num_ciclos, int buscas_por_ciclo,
                      int ids_inicio, int ids_meio, int ids_fim, int ids_inexistentes) {

    FILE* arquivo = fopen("relatorio_resultados_fase_II.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao criar arquivo de relatorio.\n");
        return;
    }

    fprintf(arquivo, "PROTOCOLO EXPERIMENTAL\n\n");

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

    fprintf(arquivo, "RESULTADOS DOS TESTES\n\n");

    fprintf(arquivo, "BUSCA SEQUENCIAL\n");
    fprintf(arquivo, "Ciclo | Tempo Total (s) | Tempo Medio (s)\n");

    double tempo_total_seq = 0.0;

    for (int i = 0; i < num_ciclos; i++) {
        double tempo_medio = tempos_seq[i] / buscas_por_ciclo;

        fprintf(arquivo, "%d | %.10f | %.10f\n",
                i + 1,
                tempos_seq[i],
                tempo_medio);

        tempo_total_seq += tempos_seq[i];
    }

    double tempo_medio_seq = tempo_total_seq / (num_ciclos * buscas_por_ciclo);

    fprintf(arquivo, "\nMEDIA | %.10f | %.10f\n\n",
            tempo_total_seq / num_ciclos,
            tempo_medio_seq);

    fprintf(arquivo, "TABELA HASH\n");
    fprintf(arquivo, "Ciclo | Tempo Total (s) | Tempo Medio (s)\n");

    double tempo_total_hash = 0.0;

    for (int i = 0; i < num_ciclos; i++) {
        double tempo_medio = tempos_hash[i] / buscas_por_ciclo;

        fprintf(arquivo, "%d | %.10f | %.10f\n",
                i + 1,
                tempos_hash[i],
                tempo_medio);

        tempo_total_hash += tempos_hash[i];
    }

    double tempo_medio_hash = tempo_total_hash / (num_ciclos * buscas_por_ciclo);

    fprintf(arquivo, "\nMEDIA | %.10f | %.10f\n\n",
            tempo_total_hash / num_ciclos,
            tempo_medio_hash);
        

    fprintf(arquivo, "ANALISE DOS RESULTADOS\n\n");

    fprintf(arquivo, "1. Busca Sequencial:\n");
    fprintf(arquivo, "Tempo medio por busca: %.10f segundos\n", tempo_medio_seq);
    fprintf(arquivo, "Complexidade teorica: O(n)\n\n");

    fprintf(arquivo, "2. Tabela Hash:\n");
    fprintf(arquivo, "Tempo medio por busca: %.10f segundos\n", tempo_medio_hash);
    fprintf(arquivo, "Complexidade teorica: O(1)\n");
    fprintf(arquivo, "Numero total de colisoes: %d\n\n", colisoes);

    fprintf(arquivo, "3. Comparacao entre os algoritmos:\n");
    fprintf(arquivo, "Total de registros: %d\n", quantidade);
    fprintf(arquivo, "Buscas realizadas por ciclo: %d\n\n", buscas_por_ciclo);

    fprintf(arquivo, "Busca Sequencial\n");
    fprintf(arquivo, "- Tempo medio: %.10f segundos\n", tempo_medio_seq);
    fprintf(arquivo, "- Complexidade: O(n)\n\n");

    fprintf(arquivo, "Tabela Hash\n");
    fprintf(arquivo, "- Tempo medio: %.10f segundos\n", tempo_medio_hash);
    fprintf(arquivo, "- Complexidade: O(1)\n");
    fprintf(arquivo, "- Colisoes registradas: %d\n\n", colisoes);

    fprintf(arquivo, "4. Observacoes experimentais:\n");

    fprintf(arquivo, "TABELA COMPARATIVA\n\n");

    fprintf(arquivo, "Metrica                     Busca Sequencial      Tabela Hash\n");
    fprintf(arquivo, "Tempo medio (s)             %.10f        %.10f\n",
            tempo_medio_seq,
            tempo_medio_hash);

    fprintf(arquivo, "Complexidade                O(n)                  O(1)\n");
    fprintf(arquivo, "Colisoes                    -                     %d\n\n",
            colisoes);

    if (tempo_medio_hash < tempo_medio_seq) {
        fprintf(arquivo, "- A Tabela Hash apresentou melhor desempenho medio nas buscas.\n");
    } else {
        fprintf(arquivo, "- A Busca Sequencial apresentou desempenho semelhante ou superior neste experimento.\n");
    }

    fprintf(arquivo, "- A funcao hash utilizada distribuiu os elementos com %d colisoes.\n", colisoes);
    fprintf(arquivo, "- Colisoes podem aumentar o tempo de busca na Tabela Hash.\n");
    fprintf(arquivo, "- A Busca Sequencial possui desempenho linear e depende da posicao do elemento no vetor.\n");

    fclose(arquivo);
    printf("Relatorio salvo em: relatorio_resultados_fase_II.txt\n");
}