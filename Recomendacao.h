#ifndef _Recomendacao_H_
#define _Recomendacao_H_

#include <list>
#include <iostream>
#include "listacompras.h"
using namespace std;

typedef struct {
    int indice;
    double rank;
} Ranqueamento;

typedef struct {
    list<int> lista;
} Lista;

void recomendacao(ListaCompras *listacompras, double **MatrizSimilaridade, int IDcliente);



#endif