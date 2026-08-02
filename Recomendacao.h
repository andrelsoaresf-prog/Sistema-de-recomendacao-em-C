#ifndef _Recomendacao_H_
#define _Recomendacao_H_

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include "CSR.h"

using namespace std;

typedef struct {
    int idproduto;
    double rank;
} Ranqueamento;

bool compararPorRank(const Ranqueamento &a, const Ranqueamento &b);


vector<int> recomendacaoPadrao(const vector<list<int>> &vetorLista, 
                  int numeroClientes, 
                  int numeroProdutos, 
                  const vector<vector<double>> &matrizSimilaridade, 
                  int IDcliente, 
                  int k);

vector<int> recomendacaoCSR(const vector<list<int>> &vetorLista, 
                  int numeroClientes, 
                  int numeroProdutos, 
                  const tuple<vector<double>, vector<int>, vector<int>> &ValoresTupla, 
                  int IDcliente, 
                  int k);


#endif