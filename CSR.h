#ifndef _CSR_H_
#define _CSR_H_

#include <vector>
#include <list>

using namespace std;

typedef struct {
    vector<list<int>> VetorLista;
    int NumeroClientes;
    int NumeroProdutos;
} DadosCompras;

typedef struct {
    int numeroLinha;
    int numeroColuna;
    vector<double> values;
    vector<int> col_index;
    vector<int> row_ptr;
} CSR;

typedef struct {
    int cont;
    int soma;
    int p;
    int q;
    int fimI;
    int fimJ;
} Auxiliar;

CSR criarMatrizIntersecaoCSR(CSR MatrizCompras);
CSR criarMatrizComprasCSR(DadosCompras vetor);

#endif