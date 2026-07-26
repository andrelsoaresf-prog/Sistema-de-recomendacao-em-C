#ifndef _CSR_H_
#define _CSR_H_

#include "listacompras.h"
#include "vector"
using namespace std;

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

CSR criarMatrizIntersecaoCSR(ListaCompras *listacompras, CSR MatrizCompras);
CSR criarMatrizComprasCSR(ListaCompras *listacompras);

#endif