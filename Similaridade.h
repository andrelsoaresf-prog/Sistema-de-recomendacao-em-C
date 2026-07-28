#ifndef _Similaridade_H_
#define _Similaridade_H_

#include "listacompras.h"
#include "CSR.h"

int similaridadePadrao(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras, int escolha);
void clienteSimilar(ListaCompras *listacompras, double **MatrizSimilaridade, int IDcliente1);
int similaridade(ListaCompras *listacompras);
Matrizes similiradadeCSR(ListaCompras *listacompras);

#endif