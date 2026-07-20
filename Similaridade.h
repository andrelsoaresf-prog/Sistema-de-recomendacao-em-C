#ifndef _Similaridade_H_
#define _Similaridade_H_

#include "listacompras.h"

int similaridade(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras);
void testadorATV2(ListaCompras *listacompras, double **MatrizSimilaridade);
void clienteSimilar(ListaCompras *listacompras, double **MatrizSimilaridade, int IDcliente1);

#endif