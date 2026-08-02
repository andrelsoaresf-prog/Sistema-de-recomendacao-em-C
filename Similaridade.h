#ifndef _Similaridade_H_
#define _Similaridade_H_

#include "listacompras.h"
#include "CSR.h"
#include "tuple"

vector<vector<double>> similaridadePadrao(Estrutura vetor, int modo);
vector<vector<double>> mallocParaVector(double** matrizMalloc, int linhas, int colunas);
tuple<vector<double>, vector<int>, vector<int>> similaridadeCSR(const vector<list<int>>& vetor_lista);

#endif