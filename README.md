# 🛒 Sistema de Recomendação

Sistema de recomendação de produtos desenvolvido em **C++**, com integração ao **Python através do pybind11**.

O projeto foi desenvolvido para a disciplina de **Programação Estruturada — UFPB** e tem como objetivo estudar a construção de um sistema de recomendação baseado no histórico de compras dos clientes.

A ideia é simples: **clientes com hábitos de compra semelhantes podem ajudar a recomendar produtos uns aos outros.**

---

## 🚀 Como funciona?

O sistema recebe uma base de compras em CSV e passa pelas seguintes etapas:

```text
📄 Base de compras
        ↓
🧾 Lista de compras por cliente
        ↓
📊 Cálculo de similaridade
        ↓
👥 Identificação dos vizinhos
        ↓
🛍️ Ranking de produtos
        ↓
⭐ Recomendações
```

Para o cálculo da similaridade, foram implementadas **três abordagens**:

| Modo | Descrição                                           |
| ---- | --------------------------------------------------- |
| `1`  | Multiplicação de matrizes tradicional               |
| `2`  | Algoritmo otimizado utilizando a simetria da matriz |
| `3`  | Representação esparsa utilizando **CSR**            |

---

## 🧠 Sistema de recomendação

Para gerar uma recomendação, o sistema:

1. encontra os clientes semelhantes ao cliente escolhido;
2. verifica os produtos comprados por esses clientes;
3. ignora produtos que o cliente já comprou;
4. calcula um ranking baseado na similaridade;
5. retorna os `k` produtos mais bem ranqueados.

A similaridade utilizada pelo projeto segue a fórmula definida na atividade:

```text
s(i,j) = 1 - |Pi ∩ Pj| / |Pi|
```

Essa medida é assimétrica, ou seja:

```text
s(i,j) ≠ s(j,i)
```

---

## ⚡ Otimizações

Além da implementação tradicional, o projeto possui duas abordagens voltadas para desempenho.

### 🔹 Algoritmo otimizado

Evita a construção explícita da matriz transposta e aproveita a simetria do produto:

```text
A × Aᵀ
```

Assim, parte dos cálculos pode ser evitada.

### 🔹 CSR — Compressed Sparse Row

A matriz de compras possui muitos valores `0`.

Em vez de armazenar toda a matriz, a implementação CSR armazena apenas os elementos necessários através de:

```text
values
col_index
row_ptr
```

Isso reduz o espaço utilizado e permite trabalhar melhor com bases maiores.

---

## 🐍 Integração C++ + Python

A versão final do projeto utiliza **pybind11** para conectar o código C++ ao Python.

```text
Python
  │
  ▼
bindings.cpp
  │
  ▼
C++
  ├── Similaridade
  ├── Recomendação
  └── CSR
```

Dessa forma, as partes mais pesadas do processamento continuam sendo executadas em C++, enquanto o Python controla a execução e os testes.

---

## 📁 Estrutura do projeto

```text
📦 Sistema-de-recomendacao-em-C
│
├── 📂 dados/
│
├── 📄 CSR.cpp
├── 📄 CSR.h
│
├── 📄 Similaridade.cpp
├── 📄 Similaridade.h
│
├── 📄 Recomendacao.cpp
├── 📄 Recomendacao.h
│
├── 📄 bindings.cpp
├── 📄 setup.py
│
├── 📄 listacompras.py
├── 📄 testadores.py
│
└── 📄 README.md
```

### Principais arquivos

* **`CSR.cpp/h`** — implementação da matriz esparsa CSR.
* **`Similaridade.cpp/h`** — cálculo da similaridade entre clientes.
* **`Recomendacao.cpp/h`** — geração e ordenação das recomendações.
* **`bindings.cpp`** — integração entre C++ e Python.
* **`setup.py`** — configuração da compilação do módulo Python.
* **`listacompras.py`** — leitura da base e execução do sistema.
* **`testadores.py`** — testes das funcionalidades do projeto.

---

## 🛠️ Tecnologias

* 🟦 **C++**
* 🐍 **Python**
* 🔗 **pybind11**
* 📦 **STL**
* 🧮 Multiplicação de matrizes
* 🗜️ Matrizes esparsas — CSR
* 🤖 Sistema de recomendação baseado em vizinhança

---

## ▶️ Como executar

### 1. Instalar as dependências

```bash
pip install pybind11 setuptools wheel
```

### 2. Compilar o módulo C++

```bash
python3 setup.py build_ext --inplace
```

### 3. Executar

```bash
python3 listacompras.py
```

O programa irá solicitar:

```text
1. Cluster da base de dados
2. Algoritmo de similaridade
3. Testador desejado
```

### Testadores

```text
1 → Produtos comprados por um cliente
2 → Cliente mais similar
3 → Recomendações
4 → Tempo de execução
-1 → Sair
```

---

## 📚 Sobre o projeto

Este projeto foi desenvolvido como atividade acadêmica da disciplina de **Programação Estruturada — UFPB**, com o objetivo de aplicar conceitos de:

* estruturas de dados;
* manipulação de arquivos;
* matrizes;
* algoritmos de ordenação;
* otimização;
* estruturas esparsas;
* integração entre linguagens.

---

## 👨‍💻 Autores

**Andre Luis Soares Ferreira**,
**Icaro Eduardo de Souza Lucena**

🎓 UFPB — Programação Estruturada
