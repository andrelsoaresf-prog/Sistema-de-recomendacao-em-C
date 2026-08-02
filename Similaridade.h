#ifndef _Similaridade_H_
#define _Similaridade_H_

#include "CSR.h"
#include <tuple>
#include <vector>

using namespace std;

vector<vector<double>> similaridadePadrao(const vector<list<int>> &vetorlista, 
    const int &numeroclientes, const int &numeroprodutos, int modo);

vector<vector<double>> mallocParaVector(double** matrizMalloc, int linhas, int colunas);

tuple<vector<double>, vector<int>, vector<int>> similaridadeCSR(const vector<list<int>> &vetorlista, 
    const int &numeroclientes, const int &numeroprodutos);

void converterParaEstrutura(DadosCompras *vetor, const vector<list<int>> &vetorlista, 
    const int &numeroclientes, const int &numeroprodutos);

#endif