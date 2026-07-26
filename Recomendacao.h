#ifndef _Recomendacao_H_
#define _Recomendacao_H_

#include <list>
#include <iostream>
#include "listacompras.h"
#include "CSR.h"
using namespace std;

typedef struct {
    int idproduto;
    double rank;
} Ranqueamento;

void recomendacao(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras, int IDcliente);
bool compararPorRank(const Ranqueamento &a, const Ranqueamento &b);
void recomendacaoCSR(ListaCompras *listacompras, Matrizes matriz,int IDcliente);


#endif