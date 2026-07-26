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

void similaridadeCSR(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras);
CSR criarMatrizComprasCSR(ListaCompras *listacompras);

#endif