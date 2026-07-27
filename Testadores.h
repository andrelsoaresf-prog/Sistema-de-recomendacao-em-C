#ifndef _Testadores_H_
#define _Testadores_H_

#include "listacompras.h"
#include "CSR.h"

void testadorATV1(ListaCompras *listacompras);
void testadorATV2(ListaCompras *listacompras, double **MatrizSimilaridade);
void testadorATV3(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras);
void testadorATV5(ListaCompras *listacompras, Matrizes *matriz);
void escolhertestador(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras, Matrizes *matriz, int modo);
#endif