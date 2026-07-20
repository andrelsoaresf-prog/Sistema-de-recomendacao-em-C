#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "listacompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"
using namespace std;
#include <stdlib.h>

void similaridade(ListaCompras *listacompras, int IDcliente1, int *IDcliente2){
    int NumeroClientes = listacompras->MapaCliente.size();
    int NumeroProdutos = listacompras->MapaProduto.size();

    int **MatrizCompras = (int **) malloc(NumeroClientes * sizeof(int*));
    for (int i = 0; i < NumeroClientes; i++){
        MatrizCompras[i] = (int *) malloc(NumeroProdutos * sizeof(int));
    }

    for (int i = 0; i < NumeroClientes; i++) {
        for (int j = 0; j < NumeroProdutos; j++) {
            MatrizCompras[i][j] = 0;
        }
    }

    for(int idCliente = 0; idCliente < NumeroClientes; idCliente++){
        for (int idProduto : listacompras->VetorLista[idCliente]) {
            MatrizCompras[idCliente][idProduto] = 1;
        }
    }

    int **MatrizTransposta = (int **) malloc(NumeroProdutos * sizeof(int *));
    for (int i = 0; i < NumeroProdutos; i++){
        MatrizTransposta[i] = (int *) malloc(NumeroClientes * sizeof(int));
    }

    for (int i = 0; i < NumeroClientes; i++){
        for (int j = 0; j < NumeroProdutos; j++){
            MatrizTransposta[j][i] = MatrizCompras[i][j];
        }
    }
    
    int **MatrizIntersecao = (int **) malloc(NumeroClientes * sizeof(int*));
    for (int i = 0; i < NumeroClientes; i++){
        MatrizIntersecao[i] = (int *) malloc(NumeroClientes * sizeof(int));
    }

    for (int i = 0; i < NumeroClientes; i++){
        for (int j = 0; j < NumeroClientes; j++){
            MatrizIntersecao[i][j] = 0;
            for (int a = 0; a < NumeroProdutos; a++){
                MatrizIntersecao[i][j] = MatrizIntersecao[i][j] + MatrizCompras[i][a] * MatrizTransposta[a][j];
            }
        }
    }

    double **MatrizSimilaridade = (double **) malloc(NumeroClientes * sizeof(double*));
    for (int i = 0; i < NumeroClientes; i++){
        MatrizSimilaridade[i] = (double *) malloc(NumeroClientes * sizeof(double));
    }

    for (int i = 0; i < NumeroClientes; i++){
        for (int j = 0; j < NumeroClientes; j++){
        MatrizSimilaridade[i][j] = 1.0 - ((double)MatrizIntersecao[i][j] / MatrizIntersecao[i][i]);
        }
    }

    double menor = 1.0;
    for (int j = 0; j < NumeroClientes; j++){
        if (IDcliente1 != j){
            if (menor > MatrizSimilaridade[IDcliente1][j]){
                menor = MatrizSimilaridade[IDcliente1][j];
                *IDcliente2 = j;
            }
        }
    }

    recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente1);
}

void clienteSimilar(ListaCompras *listacompras, int IDcliente1){
    int IDcliente2 = -1;
    similaridade(listacompras, IDcliente1, &IDcliente2);

    printf("O cliente mais similar com o Cliente %d, é o Cliente %d\n", IDcliente1, IDcliente2);
}

void testadorATV2(ListaCompras *listacompras){
    int IDcliente1 = 4;
    int IDcliente2 = 0;

    clienteSimilar(listacompras, IDcliente1);
    clienteSimilar(listacompras, IDcliente2);
}