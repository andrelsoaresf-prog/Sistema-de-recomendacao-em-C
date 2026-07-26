#ifndef _Similaridade_H_
#define _Similaridade_H_

#include "listacompras.h"
#include "CSR.h"

int similaridadePadrao(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras);
void clienteSimilar(ListaCompras *listacompras, double **MatrizSimilaridade, int IDcliente1);
int similaridadeAdaptada(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras);
int similaridade(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras, Matrizes *Matriz);
Matrizes similiradadeCSR(ListaCompras *listacompras);

#endif