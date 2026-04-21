#include <stdio.h>
#include <stdlib.h>
#include "./include/leitor_csv.h"
#include "./include/busca_sequencial.h"
#include "./include/tempo.h"
#include "./include/experimento.h"
#include "./include/relatorio.h"

int main() { //Analise de dados e construção inicial do relatório

    int quantidade = 0;

    // Lê o arquivo CSV
    Produto* produtos = ler_csv("../data/dataset1.csv", &quantidade);

    if (!produtos) {
        
        printf("Erro ao carregar o arquivo CSV.\n");
        return 1;
    }

    printf("PROTOCOLO EXPERIMENTAL - BUSCA SEQUENCIAL\n\n");

    printf("Total de registros carregados: %d\n\n", quantidade);

    // Tenta carregar os IDs do arquivo
    int* ids_busca = NULL;
    int num_ids = 0;

    if (!carregar_ids_busca(&ids_busca, &num_ids, "ids_selecionados.txt")) {

        // Arquivo não existe, gera novos IDs
        printf("Arquivo nao encontrado. Gerando novos IDs...\n");
        gerar_ids_busca(produtos, quantidade, &ids_busca, &num_ids);

        if (!ids_busca) {

            printf("Erro ao gerar IDs de busca.\n");
            free(produtos);
            return 1;
        }

        // Salva os IDs para próximas execuções
        salvar_ids_busca(ids_busca, num_ids, "ids_selecionados.txt");

    } else {

        printf("Arquivo carregado com sucesso.\n");
    }

    printf("\nBuscas por ciclo: %d\n\n", num_ids);

    // Executar 3 ciclos do protocolo experimental
    int num_ciclos = 3;
    double tempos[3];
    double tempo_total_geral = 0.0;

    printf("Executando protocolo experimental...\n\n");

    for (int ciclo = 0; ciclo < num_ciclos; ciclo++) {

        printf("Ciclo %d em andamento...\n", ciclo + 1);
        tempos[ciclo] = executar_protocolo_experimental(produtos, quantidade, ids_busca, num_ids);
        tempo_total_geral += tempos[ciclo];
    }

    printf("\n\nRESULTADOS DOS TESTES\n");
    printf("Ciclo | Tempo Total (s) | Tempo Medio (s)\n");

    for (int i = 0; i < num_ciclos; i++) {

        double tempo_medio = tempos[i] / num_ids;
        printf("%d | %.10f | %.10f\n", i + 1, tempos[i], tempo_medio);
    }

    double tempo_medio_geral = tempo_total_geral / (num_ciclos * num_ids);
    printf("\nMedia | %.10f | %.10f\n\n", tempo_total_geral / num_ciclos, tempo_medio_geral);

    printf("ANALISE DE DADOS\n\n");

    printf("1. Comportamento Observado:\n");
    printf("Tempo medio por busca: %.10f segundos\n", tempo_medio_geral);
    printf("Algoritmo: Busca Sequencial\n");
    printf("Complexidade do algoritmo: O(n)\n\n");

    printf("2. Relacao entre Tamanho do Vetor e Tempo de Busca:\n");
    printf("Total de registros: %d\n", quantidade);
    printf("Buscas realizadas: %d por ciclo\n", num_ids);
    printf("Tempo medio final: %.10f segundos\n\n", tempo_medio_geral);

    printf("3. Limitacoes da Busca Sequencial:\n");
    printf("- Deve percorrer ate n elementos no pior caso\n");
    printf("- Sem dependencia da ordem dos dados\n");
    printf("- Ineficiente para grandes volumes de dados\n");
    printf("- Sera comparada com Tabela Hash na Fase II\n\n");

    // Calcular distribuicao dos IDs
    int ids_inicio, ids_meio, ids_fim, ids_inexistentes;
    
    if (quantidade > 100) {

        ids_inicio = 100;

    } else {

        ids_inicio = quantidade;
    }
    
    if (quantidade > 200) {

        ids_meio = 200;

    } else {

        ids_meio = 0;
    }
    
    int inicio_finais = quantidade - 300;

    if (inicio_finais < 0) {

        ids_fim = 0;

    } else {

        ids_fim = 300;
    }
    
    ids_inexistentes = num_ids - (ids_inicio + ids_meio + ids_fim);

    // Salvar relatorio em arquivo
    salvar_relatorio(quantidade, tempos, num_ciclos, num_ids, ids_inicio, ids_meio, ids_fim, ids_inexistentes);

    printf("\n");

    // Liberar memoria
    free(produtos);
    free(ids_busca);

    return 0;
}
