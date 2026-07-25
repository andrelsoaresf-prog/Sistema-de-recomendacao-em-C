#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "listacompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"
using namespace std;

int similaridadePadrao(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras){
    int NumeroClientes = listacompras->MapaCliente.size();
    int NumeroProdutos = listacompras->MapaProduto.size();

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
    if(MatrizTransposta == NULL){
        printf("erro de memória");
        return 1;
    }
    for (int i = 0; i < NumeroProdutos; i++){
        MatrizTransposta[i] = (int *) malloc(NumeroClientes * sizeof(int));

        if(MatrizTransposta[i] == NULL){
            printf("erro de memória");
            return 1;
        }
    }

    for (int i = 0; i < NumeroClientes; i++){
        for (int j = 0; j < NumeroProdutos; j++){
            MatrizTransposta[j][i] = MatrizCompras[i][j];
        }
    }
    
    int **MatrizIntersecao = (int **) malloc(NumeroClientes * sizeof(int*));
    if(MatrizIntersecao == NULL){
        printf("erro de memória");
        return 1;
    }
    for (int i = 0; i < NumeroClientes; i++){
        MatrizIntersecao[i] = (int *) malloc(NumeroClientes * sizeof(int));

        if(MatrizIntersecao[i] == NULL){
            printf("erro de memória");
            return 1;
        }
    }

    for (int i = 0; i < NumeroClientes; i++){
        for (int j = 0; j < NumeroClientes; j++){
            MatrizIntersecao[i][j] = 0;
            for (int a = 0; a < NumeroProdutos; a++){
                MatrizIntersecao[i][j] += MatrizCompras[i][a] * MatrizTransposta[a][j];
            }
        }
    }

    for (int i = 0; i < NumeroClientes; i++){
        for (int j = 0; j < NumeroClientes; j++){
                MatrizSimilaridade[i][j] = 1.0 - ((double)MatrizIntersecao[i][j] / MatrizIntersecao[i][i]);
        }
    }


    for (int i = 0; i < NumeroProdutos; i++){
        free(MatrizTransposta[i]);
    }
    free(MatrizTransposta);
    MatrizTransposta = NULL;

    for (int i = 0; i < NumeroClientes; i++){
        free(MatrizIntersecao[i]);
    }
    free(MatrizIntersecao);
    MatrizIntersecao = NULL;

    return 0;
}

void clienteSimilar(ListaCompras *listacompras, double **MatrizSimilaridade, int IDcliente1){
    int NumeroClientes = listacompras->MapaCliente.size();
    int IDcliente2 = -1;
    double menor = 1.0;

    for (int j = 0; j < NumeroClientes; j++){
        if (IDcliente1 != j){
            if (menor > MatrizSimilaridade[IDcliente1][j]){
                menor = MatrizSimilaridade[IDcliente1][j];
                IDcliente2 = j;
            }
        }
    }

    printf("O cliente mais similar com o Cliente %d, é o Cliente %d (Similaridade: %f)\n", IDcliente1, IDcliente2, menor);
}

void testadorATV2(ListaCompras *listacompras, double **MatrizSimilaridade){
    int IDcliente1 = 7;
    int IDcliente2 = 13;

    cout << "\n------------- ATIVIDADE 2 -------------" << endl;
    clienteSimilar(listacompras, MatrizSimilaridade, IDcliente1);
    clienteSimilar(listacompras, MatrizSimilaridade, IDcliente2);
}

int similaridadeAdaptada(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras){
    int NumeroClientes = listacompras->MapaCliente.size();
    int NumeroProdutos = listacompras->MapaProduto.size();

    for (int i = 0; i < NumeroClientes; i++){
        for (int j = 0; j < NumeroProdutos; j++){
            MatrizCompras[i][j] = 0;
        }
    }

    for (int idCliente = 0; idCliente < NumeroClientes; idCliente++){
        for (int idProduto : listacompras->VetorLista[idCliente]){
            MatrizCompras[idCliente][idProduto] = 1;
        }
    }

    int **MatrizIntersecao = (int **) malloc(NumeroClientes * sizeof(int*));
    if (MatrizIntersecao == NULL){
        printf("erro de memória");
        return 1;
    }

    for (int i = 0; i < NumeroClientes; i++){
        MatrizIntersecao[i] = (int *) malloc(NumeroClientes * sizeof(int));

        if (MatrizIntersecao[i] == NULL){
            printf("erro de memória");
            return 1;
        }
    }

    for (int i = 0; i < NumeroClientes; i++){
        for (int j = i; j < NumeroClientes; j++){
            int soma = 0;
            for (int k = 0; k < NumeroClientes; k++){
                soma = soma + MatrizCompras[i][k] + MatrizCompras[j][k];
            }
            MatrizIntersecao[i][j] = soma;
            MatrizIntersecao[j][i] = soma;
        }
    }

    for (int i = 0; i < NumeroClientes; i++){
        for (int j = 0; j < NumeroClientes; j++){
            MatrizSimilaridade[i][j] = 1.0 - ((double)MatrizIntersecao[i][j] / MatrizIntersecao[i][i]);
        }
    }

    for (int i = 0; i < NumeroClientes; i++){
        free(MatrizIntersecao[i]);
    }
    free(MatrizIntersecao);
    MatrizIntersecao = NULL;

    return 0;
}

int similaridade(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras, int escolha){

    if (escolha == 1){
        similaridadePadrao(listacompras, MatrizSimilaridade, MatrizCompras);
        return 0;
    }

    if (escolha == 2){
        similaridadeAdaptada(listacompras, MatrizSimilaridade, MatrizCompras);
        return 0;
    }

    else 
        printf("erro");
        return 1;
}