#include "listacompras.h"
#include "Similaridade.h"
#include <stdlib.h>

void similaridade(ListaCompras *listacompras){
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
            for (int a = 0; a < NumeroClientes; a++){
                MatrizIntersecao[i][j] += MatrizCompras[i][a] * MatrizTransposta[a][j];
            }
        }
    }

    int **MatrizSimilaridade = (int **) malloc(NumeroClientes * sizeof(int*));
    for (int i = 0; i < NumeroClientes; i++){
        MatrizSimilaridade[i] = (int *) malloc(NumeroClientes * sizeof(int));
    }

    for (int i = 0; i < NumeroClientes; i++){
        for (int j = 0; j < NumeroClientes; j++){
            MatrizSimilaridade[i][j] = 1 - MatrizIntersecao[i][j]/NumeroProdutos;
        }
    }
}