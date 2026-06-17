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

    //Cria tabela hash
    TabelaHash* hash = criar_tabela(quantidade);

    //Insere os produtos na tabela hash
    for (int i = 0; i < quantidade; i++) {

        inserir(hash, produtos[i]);
    }

    //Informa quantidade de colisoes
    printf("Tabela Hash carregada.\n");
    printf("Colisoes registradas: %d\n", hash->colisoes);

    //Protocolo experimental - Tabela Hash vs Busca Sequencial

    printf("PROTOCOLO EXPERIMENTAL - BUSCA SEQUENCIAL vs TABELA HASH\n\n");
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

    double tempos_seq[3];
    double tempos_hash[3];

    double tempo_total_seq = 0.0;
    double tempo_total_hash = 0.0;

    printf("Executando protocolo experimental...\n\n");

    for (int ciclo = 0; ciclo < num_ciclos; ciclo++) {

        printf("Ciclo %d em andamento...\n", ciclo + 1);
        
        //busca sequencial
        tempos_seq[ciclo] = executar_protocolo_experimental(
            produtos,
            quantidade,
            ids_busca,
            num_ids
        );
        //busca tabela hash
        tempos_hash[ciclo] = executar_protocolo_hash(
            hash,
            ids_busca,
            num_ids
        );

        tempo_total_seq += tempos_seq[ciclo];
        tempo_total_hash += tempos_hash[ciclo];
    }

    // Apresentar resultados e análise dos dados
    printf("\n\nRESULTADOS DOS TESTES\n\n");
    printf("BUSCA SEQUENCIAL\n");
    printf("Ciclo | Tempo Total (s) | Tempo Medio (s)\n");

    for (int i = 0; i < num_ciclos; i++) {

        double tempo_medio = tempos_seq[i] / num_ids;
        printf("%d | %.10f | %.10f\n", i + 1, tempos_seq[i], tempo_medio);
    }

    double tempo_medio_seq = tempo_total_seq / (num_ciclos * num_ids);

    printf("\nMedia | %.10f | %.10f\n\n",
        tempo_total_seq / num_ciclos,
        tempo_medio_seq);


    printf("TABELA HASH\n");
    printf("Ciclo | Tempo Total (s) | Tempo Medio (s)\n");

    for (int i = 0; i < num_ciclos; i++) {

        double tempo_medio = tempos_hash[i] / num_ids;
        printf("%d | %.10f | %.10f\n", i + 1, tempos_hash[i], tempo_medio);
    }

    double tempo_medio_hash = tempo_total_hash / (num_ciclos * num_ids);

    printf("\nMedia | %.10f | %.10f\n\n",
        tempo_total_hash / num_ciclos,
        tempo_medio_hash);

    printf("ANALISE DE DADOS\n\n");

    printf("1. Comportamento Observado:\n");
    printf("Tempo medio por busca (Busca Sequencial): %.10f segundos\n", tempo_medio_seq);
    printf("Tempo medio por busca (Tabela Hash): %.10f segundos\n", tempo_medio_hash);
    printf("Numero total de colisoes: %d\n\n", hash->colisoes);

    printf("2. Relacao entre Tamanho do Vetor e Tempo de Busca:\n");
    printf("Total de registros: %d\n", quantidade);
    printf("Buscas realizadas: %d por ciclo\n", num_ids);
    printf("Tempo medio final Busca Sequencial: %.10f segundos\n", tempo_medio_seq);
    printf("Tempo medio final Tabela Hash: %.10f segundos\n\n", tempo_medio_hash);

    printf("3. Comparacao entre os Algoritmos:\n");
    printf("Busca Sequencial\n");
    printf("- Complexidade teorica: O(n)\n");
    printf("- Percorre os elementos sequencialmente\n");
    printf("- Pior caso: percorre todo o vetor\n\n");

    printf("Tabela Hash\n");
    printf("- Complexidade teorica: O(1)\n");
    printf("- Utiliza funcao hash para localizar os elementos\n");
    printf("- Desempenho pode ser afetado por colisoes\n\n");

    printf("4. Analise Experimental:\n");
    printf("- A Busca Sequencial apresentou tempo medio de %.10f segundos\n", tempo_medio_seq);
    printf("- A Tabela Hash apresentou tempo medio de %.10f segundos\n", tempo_medio_hash);
    printf("- Foram registradas %d colisoes durante o carregamento da tabela\n\n", hash->colisoes);

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
    salvar_relatorio(
    quantidade,
    tempos_seq,
    tempos_hash,
    hash->colisoes,
    num_ciclos,
    num_ids,
    ids_inicio,
    ids_meio,
    ids_fim,
    ids_inexistentes
    );

    printf("\n");

    // Liberar memoria
    liberar_tabela(hash);
    free(produtos);
    free(ids_busca);

    return 0;
}
