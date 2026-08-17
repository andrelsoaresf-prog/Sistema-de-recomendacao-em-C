# 🛒 Sistema de Recomendação em C++ com Integração Python

Um sistema de recomendação de produtos para clientes de lojas de varejo, desenvolvido em **C++** e integrado ao **Python** via `pybind11`, como parte da disciplina de **Programação Estruturada** na UFPB.

O sistema recomenda produtos a um cliente com base no **Método da Vizinhança** (filtragem colaborativa baseada em usuário): clientes com histórico de compras parecido são considerados "vizinhos", e produtos que os vizinhos compraram (e o cliente ainda não) são ranqueados e recomendados.

---

## 📌 Como funciona

1. **Leitura da base de compras** (`listacompras.py`): lê um CSV de vendas e monta, para cada cliente, a lista de produtos que ele comprou.
2. **Matriz de Similaridade** (`Similaridade.cpp/h`): calcula o quão parecido cada par de clientes é, usando a **distância de Jaccard** sobre o histórico de compras. Disponível em três modos:
   - **Padrão** — multiplicação de matriz de compras pela transposta, do jeito tradicional.
   - **Otimizada** — mesma ideia, mas evitando recalcular a transposta e aproveitando a simetria do resultado (quase metade das multiplicações).
   - **CSR** (*Compressed Sparse Row*) — representação esparsa da matriz, guardando só os valores não nulos. Essencial para bases grandes, onde a matriz densa não caberia na memória.
3. **Recomendação** (`Recomendacao.cpp/h`): para um cliente, ranqueia os produtos comprados por seus vizinhos (ponderados pela similaridade) e retorna os `k` melhores.
4. **Integração Python** (`bindings.cpp`): expõe as funções de C++ ao Python como o módulo `Sistema_Recomendacao`, usando `pybind11`.

---

## 🗂️ Estrutura do Projeto

| Arquivo | Descrição |
| --- | --- |
| `CSR.cpp` / `CSR.h` | Estrutura de matriz esparsa (CSR) e construção da matriz de interseção de compras nesse formato. |
| `Similaridade.cpp` / `Similaridade.h` | Cálculo da matriz de similaridade entre clientes (modos padrão, otimizado e CSR). |
| `Recomendacao.cpp` / `Recomendacao.h` | Algoritmo de ranqueamento e seleção dos `k` produtos recomendados. |
| `bindings.cpp` | Ligação (binding) das funções C++ ao Python via `pybind11`, gerando o módulo `Sistema_Recomendacao`. |
| `setup.py` | Script de build da extensão Python (`Sistema_Recomendacao`). |
| `listacompras.py` | Lê a base de compras (CSV), monta as estruturas de dados e conduz o fluxo principal do programa. |
| `testadores.py` | Testadores interativos para as 3 atividades (consulta de compras, cliente mais similar, recomendação). |
| `dados/` | Base de compras em CSV (não versionada — ver `.gitignore`). |

---

## 📐 Fundamentação Teórica

**Distância de Jaccard** — mede a similaridade entre dois clientes `i` e `j` a partir da interseção dos produtos comprados:

```
s(i, j) = 1 - |Pᵢ ∩ Pⱼ| / |Pᵢ|
```

Note que essa medida é **assimétrica** (`s(i,j) ≠ s(j,i)`), o que é proposital: evita que um cliente que compra muito pareça "parecido" com todo mundo.

**Algoritmo de recomendação**, para recomendar `k` produtos a um cliente `c`:
1. Lista os vizinhos de `c` (clientes com similaridade calculada, exceto ele mesmo).
2. Inicializa um vetor de ranqueamento com valor 1 para cada produto.
3. Para cada vizinho `s` e cada produto que `s` comprou (e `c` não comprou), multiplica o ranqueamento do produto por `s(c, s)`.
4. Ordena os produtos pelo ranqueamento e retorna os `k` melhores.

---

## 🚀 Como Executar

### Pré-requisitos
- Python 3 com `pip`
- Compilador C++ com suporte a C++17 (`g++`/`clang++` no Linux/macOS, ou MSVC + *Build Tools* no Windows)
- Biblioteca `pybind11`

### Instalação
```bash
pip install pybind11 setuptools wheel
```

### Compilação do módulo C++ (`Sistema_Recomendacao`)
```bash
python3 setup.py build_ext --inplace
```
Isso gera o arquivo compilado do módulo (ex.: `Sistema_Recomendacao.cpython-313-x86_64-linux-gnu.so` no Linux, ou `Sistema_Recomendacao.cp313-win_amd64.pyd` no Windows) na raiz do projeto.

### Base de dados
Coloque os arquivos de compras dentro da pasta `dados/` (não incluída no repositório — ver `.gitignore`), no formato:
```
DATA_COMPRA,COD_CLIENTE,COD_PRODUTO,NOME_PRODUTO
```
O projeto espera arquivos nomeados `dados_venda_cluster_1.csv` até `dados_venda_cluster_20.csv`.

### Execução
```bash
python3 listacompras.py
```
O programa vai pedir:
1. **O número do cluster** (1 a 20) — qual arquivo CSV usar.
2. **O modo de cálculo da similaridade** — 1 (padrão), 2 (otimizada) ou 3 (CSR).
3. **Qual testador rodar**, em loop, até digitar `-1`:
   - `1` — mostra os produtos comprados por um cliente.
   - `2` — mostra o cliente mais similar a um cliente dado.
   - `3` — mostra os `k` produtos mais recomendados para um cliente.
   - `4` — mostra o tempo gasto para construir a matriz de similaridade.

---

## 👤 Autores

Andre Luis Soares Ferreira e Icaro Eduardo de Souza Lucena

Projeto desenvolvido para a disciplina de Programação Estruturada — UFPB.
