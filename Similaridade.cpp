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
}