# Sistema de Recomendação de Produtos com Suporte CSR (Versão Otimizada)

Um sistema robusto e otimizado em C++ para recomendação de produtos via filtragem colaborativa baseada em usuários (User-Based Collaborative Filtering). O projeto suporta tanto representação matricial densa quanto esparsa no formato **Compressed Sparse Row (CSR)**, permitindo alta eficiência de memória e processamento de grandes volumes de dados.

---

## 📌 Sumário

1. [Visão Geral](#-visão-geral)
2. [Arquitetura e Componentes](#-arquitetura-e-componentes)
3. [Estruturas de Dados e Algoritmos](#-estruturas-de-dados-e-algoritmos)
4. [Estrutura do Repositório](#-estrutura-do-repositório)
5. [Requisitos do Sistema](#-requisitos-do-sistema)
6. [Compilação](#-compilação)
7. [Como Executar](#-como-executar)
8. [Suíte de Testes e Atividades](#-suíte-de-testes-e-atividades)
9. [Análise de Desempenho e Memória (CSR vs Densa)](#-análise-de-desempenho-e-memória-csr-vs-densa)
10. [Licença](#-licença)

---

## 🏬 Visão Geral

Este sistema analisa históricos de compras de clientes a partir de arquivos no formato CSV, identifica padrões de similaridade entre consumidores e gera recomendações personalizadas de produtos. 

A inclusão da estrutura **CSR (Compressed Sparse Row)** visa otimizar drasticamente o consumo de memória RAM ao manipular matrizes de cliente-produto altamente esparsas (onde a grande maioria dos pares cliente/produto possui valor zero/não comprado).

---

## 🏗️ Arquitetura e Componentes

O projeto segue uma arquitetura modular em C++11, composta pelos seguintes módulos principais:

* **Módulo de Leitura e Mapeamento (`listacompras`)**: Leitura do arquivo CSV de entrada, indexação dinâmica de IDs únicos de clientes e produtos, e armazenamento do histórico em listas ligadas.
* **Módulo de Matrizes e CSR (`CSR`)**: Construtores de matrizes densas e rotinas de conversão/construção da matriz esparsa CSR (`values`, `col_index`, `row_ptr`).
* **Módulo de Similaridade (`Similaridade`)**: Algoritmos para cálculo da taxa de sobreposição/interseção entre vetores de preferências de clientes (suportando cálculo denso e direto via vetores CSR).
* **Módulo de Recomendação (`Recomendacao`)**: Algoritmos de ordenação e pontuação para ranking de produtos não adquiridos pelo cliente-alvo.
* **Módulo de Testes e Benchmarking (`Testadores`)**: Controladores das atividades do sistema, medição de tempo de execução e aferição do uso de memória física em MB.

---

## 💡 Estruturas de Dados e Algoritmos

### 1. Formato Compressed Sparse Row (CSR)
Em vez de alocar uma matriz bidimensional $M \times N$ de inteiros/floats, a estrutura CSR utiliza três vetores unidimensionais:
* **`values`**: Armazena os valores não-nulos da matriz (ex: quantidade comprada ou flag de compra).
* **`col_index`**: Armazena os índices das colunas correspondentes para cada valor não-nulo em `values`.
* **`row_ptr`**: Vetor de tamanho $M + 1$, onde cada elemento aponta para o índice de início de uma linha no vetor `values`.

### 2. Algoritmos de Similaridade
O cálculo de similaridade entre o Cliente $A$ e o Cliente $B$ baseia-se na razão entre os itens comprados em comum e o total de itens distintos comprados por ambos (Jaccard / Interseção normalizada):
$$\text{Similaridade}(A, B) = \frac{|P_A \cap P_B|}{|P_A \cup P_B|}$$

Na versão CSR, o acesso às compras de um cliente $A$ ocorre em tempo proporcional ao seu grau de esparsidade $O(\text{nnz}_A)$, sem percorrer colunas com valor zero.

### 3. Geração de Recomendação
A partir do cliente $C_{\text{target}}$ e seu vizinho mais similar $C_{\text{similar}}$:
1. Filtra-se a lista de produtos comprados por $C_{\text{similar}}$.
2. Removem-se os produtos que $C_{\text{target}}$ já adquiriu.
3. Ordenam-se os produtos restantes por relevância (quantidade/frequência de compra ou pontuação ponderada).
4. Retornam-se os top-$k$ produtos recomendados.

---

## 📁 Estrutura do Repositório

```text
.
├── main.cpp              # Ponto de entrada do programa e menu interativo
├── listacompras.h        # Declaração das estruturas Dados, ListaCompras e parser CSV
├── listacompras.cpp      # Implementação da leitura de dados e mapeamento
├── CSR.h                 # Declaração da classe/estrutura de Matriz CSR e Densa
├── CSR.cpp               # Construtores e manipulação de matrizes CSR
├── Similaridade.h        # Protótipos das funções de similaridade
├── Similaridade.cpp      # Implementação dos cálculos de similaridade (Denso e CSR)
├── Recomendacao.h        # Protótipos das funções de recomendação
├── Recomendacao.cpp      # Implementação da geração e ordenação de recomendações
├── Testadores.h          # Protótipo das rotinas de teste e medição
├── Testadores.cpp        # Implementação das Atividades 1, 2, 3 e 5
└── Makefile              # Script de automação de compilação (opcional)
```

---

## 💻 Requisitos do Sistema

* **Compilador C++**: `g++` (versão 4.8 ou superior com suporte a C++11) ou `clang++`.
* **Sistema Operacional**: Linux, macOS ou Windows (via WSL/MinGW).
* **Ferramentas opcionais**: `make` para automação de build.

---

## 🔨 Compilação

### Via Terminal Direto (g++)
```bash
g++ -std=c++11 -O3 main.cpp listacompras.cpp CSR.cpp Similaridade.cpp Recomendacao.cpp Testadores.cpp -o main
```

### Via Makefile
```bash
make
```

---

## 🚀 Como Executar

A aplicação requer **dois parâmetros obrigatórios** via linha de comando:

```bash
./main <caminho_do_arquivo_csv> <valor_k>
```

### Parâmetros:
1. `<caminho_do_arquivo_csv>`: Caminho relativo ou absoluto para o dataset de vendas.
2. `<valor_k>`: Número inteiro positivo ($k > 0$) indicando a quantidade de recomendações ou parâmetros de vizinhança.

### Exemplo de Execução:
```bash
./main dados/dados_venda_cluster_1.csv 5
```

---

## 🧪 Suíte de Testes e Atividades

Após inicializar a aplicação, um menu interativo permite navegar pelas atividades de avaliação:

* **Atividade 1 (Carga e Inspeção)**:
  * Carrega o dataset de compras.
  * Exibe total de clientes, total de produtos e resumo do histórico de compras de um cliente específico.
* **Atividade 2 (Busca por Similaridade)**:
  * Calcula a matriz/vetor de similaridade para um determinado cliente.
  * Retorna o ID do cliente com maior similaridade e a pontuação obtida.
* **Atividade 3 (Geração de Recomendação)**:
  * Gera e exibe o ranking dos top-$k$ produtos recomendados usando representação Densa e CSR.
  * Valida a consistência dos resultados produzidos por ambos os métodos.
* **Atividade 5 (Benchmark de Memória e Desempenho)**:
  * Mede o footprint de memória em Megabytes (MB) alocado pela Matriz Densa vs. Matriz CSR.
  * Exibe a porcentagem de economia de memória atingida ao utilizar a estrutura CSR.

---
