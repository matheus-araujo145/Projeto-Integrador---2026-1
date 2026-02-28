# Projeto-Integrador---2026-1
## Análise Experimental de Algoritmos de Busca em Estruturas de Dados

Este repositório contém o desenvolvimento do **Projeto Integrador da disciplina de Estrutura de Dados**, cujo objetivo é **analisar experimentalmente o desempenho de algoritmos de busca**, utilizando **dados reais**, **protocolo experimental padronizado** e **comparação entre abordagens distintas**.

O projeto é dividido em **duas fases complementares**, que evoluem incrementalmente a partir de um baseline experimental até uma solução otimizada.

---

## 📌 Contexto Acadêmico

A eficiência de algoritmos de busca é um tema central em Estruturas de Dados. Embora a análise assintótica forneça uma visão teórica, **resultados práticos dependem de fatores como tamanho dos dados, distribuição, colisões e implementação**.

Este projeto busca:
- Conectar **teoria e prática**
- Aplicar **metodologia experimental**
- Avaliar empiricamente algoritmos de busca
- Desenvolver documentação técnica e científica

---

## 🎯 Objetivos Gerais

- Ler e estruturar dados reais a partir de arquivos CSV
- Implementar algoritmos de busca clássicos
- Medir tempo de execução de forma controlada
- Executar experimentos repetíveis
- Comparar desempenho teórico e prático
- Produzir relatório técnico e artigo científico

---

## 🌱 Estrutura de Desenvolvimento (Git)

Branches Principais

main
Contém apenas a versão final e estável do projeto (entrega).

develop
Branch de integração contínua, onde todas as funcionalidades consolidadas são reunidas.

feature/*
Branches de desenvolvimento individual ou de funcionalidades específicas.

## 🔀 Fluxo de Pull Request (PR)

Criar uma branch a partir de develop

git checkout develop
git checkout -b feature/nome-da-feature

Desenvolver a funcionalidade ou main individual

Realizar commits pequenos e descritivos

Abrir um Pull Request para a branch develop

Revisar o código em grupo

Após aprovação, realizar o merge

❌ Commits diretos na branch main não são permitidos.

## 🧾 Boas Práticas de Commit

Commits frequentes

Mensagens claras e objetivas

Exemplos

feat: implementa leitura do CSV

feat: adiciona busca sequencial

feat: cria main individual para testes

fix: corrige erro de leitura do arquivo

docs: atualiza README

## 🧪 Fases do Projeto

### 🔹 Fase I — Modelagem, Dataset e Baseline Experimental

Nesta fase é construído o **baseline experimental**, utilizando **busca sequencial** como referência.

#### Objetivos da Fase I
- Estruturar o dataset em memória
- Implementar busca sequencial
- Medir tempo médio de execução
- Analisar o impacto do tamanho do vetor no desempenho
- Identificar limitações do algoritmo

#### Funcionalidades
- Leitura de CSV com validação de erros
- Armazenamento em vetor dinâmico
- Busca sequencial por `id`
- Medição automática de tempo
- Execução de múltiplos testes consecutivos

---

### 🔹 Fase II — Otimização, Análise Experimental e Artigo Científico

Na segunda fase, o baseline é utilizado para **comparação com uma estrutura otimizada**: a **Tabela Hash**.

#### Objetivos da Fase II
- Implementar Tabela Hash com tratamento de colisões
- Avaliar eficiência prática da função hash
- Comparar busca sequencial vs tabela hash
- Validar experimentalmente a superioridade da solução otimizada

#### Funcionalidades
- Implementação de Tabela Hash com encadeamento
- Função hash definida pelo grupo
- Contabilização do número de colisões
- Execução automatizada de testes
- Análise comparativa detalhada

---


## 📦 Dataset

Os dados são fornecidos em formato CSV e representam produtos com a seguinte estrutura lógica:

```c
typedef struct {
    int id;
    char name[51];
    char categoria[31];
    float valor;
} Produto;

