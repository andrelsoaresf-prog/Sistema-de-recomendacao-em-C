# Sistema de Recomendação de Produtos em C++

Sistema de recomendação de produtos desenvolvido em C++ como parte de um projeto acadêmico de Programação Estruturada.

O projeto implementa um sistema de recomendação baseado no histórico de compras dos clientes, utilizando diferentes estratégias para calcular a similaridade entre clientes e diferentes representações de matrizes, incluindo a estrutura esparsa **Compressed Sparse Row (CSR)**.

O sistema foi desenvolvido de forma modular e permite comparar:

* uma implementação padrão baseada em multiplicação de matrizes;
* uma implementação adaptada que explora a simetria da matriz de similaridade;
* uma implementação utilizando matrizes esparsas em CSR.

---

## 📌 Sumário

* [Sobre o projeto](#-sobre-o-projeto)
* [Objetivos](#-objetivos)
* [Funcionamento](#-funcionamento)
* [Módulos](#-módulos)
* [Cálculo da similaridade](#-cálculo-da-similaridade)
* [Estratégias de cálculo](#-estratégias-de-cálculo)
* [Estrutura CSR](#-estrutura-csr)
* [Sistema de recomendação](#-sistema-de-recomendação)
* [Estrutura do projeto](#-estrutura-do-projeto)
* [Requisitos](#-requisitos)
* [Compilação](#-compilação)
* [Execução](#-execução)
* [Modos de execução](#-modos-de-execução)
* [Testadores](#-testadores)
* [Exemplo de execução](#-exemplo-de-execução)
* [Relação com as atividades](#-relação-com-as-atividades)

---

## 🏬 Sobre o projeto

O sistema recebe como entrada um arquivo CSV contendo o histórico de compras de uma loja.

Cada registro contém informações como:

* data da compra;
* código do cliente;
* código do produto;
* nome do produto.

A partir desses dados, o sistema cria estruturas internas para representar os clientes, produtos e compras realizadas.

Com essas informações, é possível:

1. identificar os produtos comprados por um cliente;
2. calcular a similaridade entre clientes;
3. encontrar o cliente mais similar a determinado cliente;
4. gerar recomendações de produtos;
5. comparar diferentes estratégias para o cálculo da similaridade;
6. utilizar uma representação esparsa CSR para reduzir o armazenamento de zeros.

---

## 🎯 Objetivos

O projeto tem como principais objetivos:

* praticar estruturas de dados em C++;
* trabalhar com arquivos CSV;
* utilizar `vector`, `list` e `map`;
* representar relações entre clientes e produtos por meio de matrizes;
* implementar multiplicação de matrizes;
* explorar a simetria de uma matriz;
* trabalhar com matrizes esparsas;
* implementar a estrutura CSR;
* desenvolver um algoritmo de recomendação baseado em vizinhança;
* comparar diferentes formas de representação e processamento dos dados.

---

## ⚙️ Funcionamento

O processamento segue, de forma geral, as seguintes etapas:

```text
Arquivo CSV
     │
     ▼
ListaCompras
     │
     ├── Clientes
     ├── Produtos
     ├── Mapeamentos
     └── Histórico de compras
     │
     ▼
Escolha do algoritmo
     │
     ├── Modo 1 → Similaridade padrão
     ├── Modo 2 → Similaridade adaptada
     └── Modo 3 → Similaridade com CSR
     │
     ▼
Matriz de similaridade
     │
     ▼
Recomendação
     │
     ▼
Top-k produtos
```

---

# 🧩 Módulos

## `listacompras`

Responsável pela leitura do arquivo CSV e organização dos dados.

Entre as principais estruturas utilizadas estão:

* vetor de códigos dos clientes;
* mapa de código do cliente → índice interno;
* vetor de códigos dos produtos;
* mapa de código do produto → índice interno;
* vetor com os nomes dos produtos;
* lista de produtos comprados por cada cliente.

A leitura é realizada utilizando funções de manipulação de arquivos da linguagem C/C++.

---

## `Similaridade`

Responsável pelo cálculo da similaridade entre os clientes.

O módulo possui três possibilidades de processamento:

1. algoritmo padrão;
2. algoritmo adaptado;
3. algoritmo baseado em CSR.

Também é responsável por localizar o cliente mais similar a partir da matriz calculada.

---

## `Recomendacao`

Responsável pela geração do ranking de produtos.

O módulo:

1. identifica os vizinhos do cliente;
2. cria um vetor de ranqueamento para os produtos;
3. ignora produtos que o cliente já comprou;
4. atualiza o ranking utilizando a similaridade dos vizinhos;
5. ordena os produtos;
6. exibe os `k` produtos com melhor ranking.

---

## `CSR`

Responsável pela construção e manipulação das matrizes esparsas.

A implementação utiliza os três vetores tradicionais da representação CSR:

* `values`;
* `col_index`;
* `row_ptr`.

Também realiza o cálculo da matriz de interseção utilizando as linhas da matriz de compras.

---

## `Testadores`

Contém os testes referentes às atividades do projeto.

São disponibilizados testadores para:

* Atividade 1;
* Atividade 2;
* Atividade 3;
* Atividade 5.

A Atividade 4 é representada pelo algoritmo adaptado selecionado no **modo 2**.

---

# 📐 Cálculo da similaridade

O projeto utiliza a seguinte definição de similaridade:

[
S(i,j) =
1 -
\frac{|P_i \cap P_j|}
{|P_i|}
]

onde:

* (P_i) é o conjunto de produtos comprados pelo cliente `i`;
* (P_j) é o conjunto de produtos comprados pelo cliente `j`;
* (|P_i \cap P_j|) representa a quantidade de produtos em comum.

Essa definição é **assimétrica**, pois o denominador depende do cliente que está sendo analisado.

Por exemplo:

```text
S(A,B) pode ser diferente de S(B,A)
```

A implementação calcula inicialmente a quantidade de produtos em comum entre os clientes e, posteriormente, utiliza a quantidade de produtos do cliente de origem para calcular a similaridade.

---

# 🔢 Estratégias de cálculo

## Modo 1 — Algoritmo padrão

No primeiro modo, o sistema constrói a matriz de compras e sua transposta.

O cálculo da interseção é realizado por meio de:

[
I = A \times A^T
]

Esse método segue diretamente a abordagem tradicional de multiplicação de matrizes.

---

## Modo 2 — Algoritmo adaptado

O segundo modo evita a construção explícita da matriz transposta.

Como o produto:

[
A \times A^T
]

gera uma matriz de interseção simétrica, basta calcular uma das metades da matriz e copiar os valores para a posição correspondente.

Assim:

```text
I[i][j] = I[j][i]
```

O código percorre apenas a região necessária e aproveita essa propriedade para reduzir o número de operações.

---

## Modo 3 — Algoritmo com CSR

O terceiro modo utiliza uma representação esparsa da matriz de compras.

Em vez de armazenar todos os zeros da matriz, são armazenados somente os elementos não nulos.

A interseção entre dois clientes é calculada comparando diretamente suas listas de produtos dentro da estrutura CSR.

Não é necessário construir explicitamente a matriz transposta.

---

# 🧮 Estrutura CSR

CSR significa **Compressed Sparse Row**.

A representação utiliza três vetores:

### `values`

Armazena os valores diferentes de zero.

Neste projeto, como a matriz de compras representa se um produto foi comprado ou não, os valores armazenados normalmente são `1`.

### `col_index`

Armazena o índice da coluna correspondente a cada elemento presente em `values`.

### `row_ptr`

Indica onde começa e termina cada linha dentro dos vetores `values` e `col_index`.

Possui tamanho:

```text
número_de_linhas + 1
```

### Exemplo conceitual

Para uma matriz:

```text
0 1 0 0
1 0 1 0
0 0 0 0
0 1 0 1
```

uma representação CSR armazena somente os elementos diferentes de zero e suas respectivas posições.

Isso evita o armazenamento explícito dos zeros.

---

# 🤖 Sistema de recomendação

O sistema utiliza os clientes semelhantes como vizinhos para gerar recomendações.

Para um cliente-alvo:

```text
Cliente alvo
     │
     ▼
Identificação dos vizinhos
     │
     ▼
Produtos comprados pelos vizinhos
     │
     ▼
Remove produtos já comprados
     │
     ▼
Atualiza o ranking
     │
     ▼
Ordenação
     │
     ▼
Top-k recomendações
```

Inicialmente, cada produto recebe um valor de ranking.

Para cada vizinho, os produtos que ainda não foram comprados pelo cliente-alvo têm seu ranking atualizado utilizando a similaridade entre os dois clientes.

Ao final, os produtos são ordenados pelo ranking.

---

# 📁 Estrutura do projeto

```text
VersaoC/C++
│
├── .vscode/
│
├── .gitignore
│
├── CSR.cpp
├── CSR.h
│
├── listacompras.cpp
├── listacompras.h
│
├── Similaridade.cpp
├── Similaridade.h
│
├── Recomendacao.cpp
├── Recomendacao.h
│
├── Testadores.cpp
├── Testadores.h
│
├── main.cpp
└── main
```

### Descrição dos arquivos

| Arquivo              | Responsabilidade                |
| -------------------- | ------------------------------- |
| `main.cpp`           | Ponto de entrada do programa    |
| `listacompras.cpp/h` | Leitura e organização dos dados |
| `Similaridade.cpp/h` | Cálculo da similaridade         |
| `Recomendacao.cpp/h` | Geração das recomendações       |
| `CSR.cpp/h`          | Estruturas e operações CSR      |
| `Testadores.cpp/h`   | Testes das atividades           |

---

# 💻 Requisitos

Para compilar o projeto é necessário possuir:

* compilador C++ com suporte a C++11;
* `g++` ou compilador compatível;
* sistema operacional Linux, macOS ou Windows com ambiente compatível.

O projeto utiliza recursos disponíveis no padrão **C++11**.

---

# 🔨 Compilação

A compilação pode ser realizada diretamente pelo terminal:

```bash
g++ -std=c++11 -O3 main.cpp listacompras.cpp CSR.cpp Similaridade.cpp Recomendacao.cpp Testadores.cpp -o main
```

Após a compilação, será gerado o executável:

```text
main
```

---

# 🚀 Execução

O programa recebe dois argumentos:

```bash
./main <arquivo_csv> <k>
```

Onde:

* `<arquivo_csv>` é o caminho para o arquivo de dados;
* `<k>` é a quantidade de produtos que serão exibidos nas recomendações.

### Exemplo

```bash
./main dados/dados_venda_cluster_17.csv 10
```

O valor de `k` deve ser um número positivo.

---

# 🔀 Modos de execução

Depois de carregar o arquivo, o sistema solicita a escolha do algoritmo:

```text
1 para algoritmo padrão de similaridade
2 para algoritmo adaptado
3 para algoritmo com CSR
```

### Modo 1

Utiliza a abordagem tradicional:

```text
A × Aᵀ
```

### Modo 2

Utiliza o algoritmo adaptado, evitando a construção explícita da transposta e explorando a simetria da matriz de interseção.

### Modo 3

Utiliza a representação CSR para armazenar a matriz de compras e calcular a matriz de similaridade de forma esparsa.

---

# 🧪 Testadores

Após escolher o algoritmo, o programa apresenta um menu:

```text
Digite qual testador deseja verificar
(1, 2, 3, 5 ou -1 para sair):
```

## Atividade 1

Exibe os produtos comprados por três clientes definidos no testador.

Os clientes são identificados utilizando seus códigos originais.

---

## Atividade 2

Seleciona clientes utilizando seus índices internos e procura o cliente mais similar.

O resultado apresenta:

```text
O cliente mais similar com o Cliente X,
é o Cliente Y
(Similaridade: valor)
```

Esse teste utiliza a matriz densa e, portanto, deve ser executado nos modos 1 ou 2.

---

## Atividade 3

Gera recomendações para três clientes.

A recomendação pode utilizar:

* a implementação densa nos modos 1 e 2;
* a implementação CSR no modo 3.

O resultado apresenta o nome do produto e seu ranking.

Exemplo:

```text
Produto: NOME DO PRODUTO | Rank: 0.125
```

---

## Atividade 4

A otimização da multiplicação de matrizes é implementada no **modo 2**.

O algoritmo adaptado evita a construção da matriz transposta e utiliza a simetria do produto:

```text
A × Aᵀ
```

A implementação calcula somente a região necessária da matriz de interseção e replica os valores simétricos.

---

## Atividade 5

Estima o espaço ocupado pela matriz de similaridade nas diferentes representações.

Para a representação densa, considera o espaço necessário para armazenar a matriz completa.

Para CSR, considera:

```text
row_ptr
+
col_index
+
values
```

O resultado é exibido em Megabytes.

---

# 📊 Densa × CSR

A principal vantagem da representação CSR é evitar o armazenamento explícito dos elementos iguais a zero.

Em uma matriz de compras, a maior parte das combinações:

```text
cliente × produto
```

normalmente representa uma ausência de compra.

Portanto, armazenar toda a matriz densa pode consumir uma quantidade significativa de memória.

Com CSR, são armazenados somente os elementos não nulos e suas posições.

### Matriz densa

```text
[0 0 1 0 0]
[1 0 0 0 0]
[0 0 0 1 0]
[0 1 0 0 0]
```

### CSR

```text
values
col_index
row_ptr
```

Dessa maneira, a representação esparsa pode reduzir significativamente a quantidade de memória necessária para armazenar os dados.

---

# 📚 Relação com as atividades do projeto

| Atividade                        | Implementação                               |
| -------------------------------- | ------------------------------------------- |
| **A1 — ListaCompras**            | `listacompras.cpp/h`                        |
| **A2 — Similaridade inicial**    | `Similaridade.cpp/h` — modo 1               |
| **A3 — Recomendação**            | `Recomendacao.cpp/h`                        |
| **A4 — Multiplicação eficiente** | `Similaridade.cpp/h` — modo 2               |
| **A5 — Matrizes esparsas CSR**   | `CSR.cpp/h` + `Similaridade.cpp/h` — modo 3 |

---

# 🛠️ Tecnologias utilizadas

* **C++11**
* `vector`
* `list`
* `map`
* alocação dinâmica de memória
* manipulação de arquivos
* multiplicação de matrizes
* matrizes esparsas
* Compressed Sparse Row (CSR)
* algoritmos de ordenação

---

# 👨‍💻 Projeto acadêmico

Projeto desenvolvido para a disciplina de **Programação Estruturada**, com foco na implementação de estruturas de dados, algoritmos de matrizes, otimização e sistemas de recomendação.

---

## 📌 Observação

O projeto possui diferentes implementações do cálculo de similaridade para permitir a comparação entre uma abordagem matricial tradicional, uma abordagem otimizada pela simetria e uma abordagem baseada em matrizes esparsas CSR.
