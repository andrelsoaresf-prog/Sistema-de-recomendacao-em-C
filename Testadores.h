#ifndef _Testadores_H_
#define _Testadores_H_

#include "listacompras.h"

void testadorATV1(ListaCompras *listacompras);
void testadorATV2(ListaCompras *listacompras, double **MatrizSimilaridade);
void testadorATV3(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras);
void testadorATV5(ListaCompras *listacompras);
void escolhertestador(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras);

#endif