#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "listacompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"
#include "CSR.h"
using namespace std;

int** criarMatrizCompras(Estrutura vetor){
    int NumeroClientes = vetor.NumeroClientes;
    int NumeroProdutos = vetor.NumeroProdutos;

    int **MatrizCompras = (int **) malloc(NumeroClientes * sizeof(int*));
    if(MatrizCompras == NULL){
        printf("erro de memória");
    }

    for (int i = 0; i < NumeroClientes; i++){
        MatrizCompras[i] = (int *) malloc(NumeroProdutos * sizeof(int));

        if (MatrizCompras[i] == NULL){
               printf("erro de memória");
        }
    }

    for (int i = 0; i < NumeroClientes; i++) {
        for (int j = 0; j < NumeroProdutos; j++) {
            MatrizCompras[i][j] = 0;
        }
    }

    for(int idCliente = 0; idCliente < NumeroClientes; idCliente++){
        for (int idProduto : vetor.VetorLista[idCliente]) {
            MatrizCompras[idCliente][idProduto] = 1;
        }
    }

    return MatrizCompras;
}

vector<vector<double>> similaridadePadrao(Estrutura vetor, int modo){
    int NumeroClientes = vetor.NumeroClientes;
    int NumeroProdutos = vetor.NumeroProdutos;

    int **MatrizCompras = criarMatrizCompras(vetor);

    double **MatrizSimilaridade = (double **) malloc(NumeroClientes * sizeof(double*));
    for (int i = 0; i < NumeroClientes; i++){
        MatrizSimilaridade[i] = (double *) malloc(NumeroClientes * sizeof(double));
    }

    int **MatrizIntersecao = (int **) malloc(NumeroClientes * sizeof(int*));
    for (int i = 0; i < NumeroClientes; i++){
        MatrizIntersecao[i] = (int *) malloc(NumeroClientes * sizeof(int));
    }

    if (modo == 1){
        int **MatrizTransposta = (int **) malloc(NumeroProdutos * sizeof(int *));

        for (int i = 0; i < NumeroProdutos; i++){
            MatrizTransposta[i] = (int *) malloc(NumeroClientes * sizeof(int));
        }

        for (int i = 0; i < NumeroClientes; i++){
            for (int j = 0; j < NumeroProdutos; j++){
                MatrizTransposta[j][i] = MatrizCompras[i][j];
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

        for (int i = 0; i < NumeroProdutos; i++){
            free(MatrizTransposta[i]);
        }
        free(MatrizTransposta);
        MatrizTransposta = NULL;
    }

    else if (modo == 2){
        for (int i = 0; i < NumeroClientes; i++){
            for (int j = i; j < NumeroClientes; j++){
                int soma = 0;
                for (int k = 0; k < NumeroProdutos; k++){
                    soma += MatrizCompras[i][k] * MatrizCompras[j][k];
                }
                MatrizIntersecao[i][j] = soma;
                MatrizIntersecao[j][i] = soma;
            }
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

    for (int i = 0; i < NumeroClientes; i++){
        free(MatrizCompras[i]);
    }
    free(MatrizCompras);
    MatrizCompras = NULL;

    vector<vector<double>> resultado = mallocParaVector(MatrizSimilaridade, NumeroClientes, NumeroClientes);

    for (int i = 0; i < NumeroClientes; i++) {
        free(MatrizSimilaridade[i]);
    }
    free(MatrizSimilaridade);
    MatrizSimilaridade = NULL;

    return resultado;
}

tuple<vector<double>, vector<int>, vector<int>> similaridadeCSR(const vector<list<int>>& vetor_lista){
    CSR MatrizCompras = criarMatrizComprasCSR(vetor_lista);
    CSR MatrizIntersecao = criarMatrizIntersecaoCSR(vetor_lista, MatrizCompras);

    CSR MatrizSimilaridade;
    MatrizSimilaridade.numeroLinha = MatrizIntersecao.numeroLinha;
    MatrizSimilaridade.numeroColuna = MatrizIntersecao.numeroColuna;

    MatrizSimilaridade.row_ptr = MatrizIntersecao.row_ptr;
    MatrizSimilaridade.col_index = MatrizIntersecao.col_index;

    for(int i = 0; i < MatrizIntersecao.numeroLinha; i++){
        double TotalProdutos = MatrizCompras.row_ptr[i+1] - MatrizCompras.row_ptr[i];

        int inicio = MatrizIntersecao.row_ptr[i];
        int fim = MatrizIntersecao.row_ptr[i + 1];

        for (int idx = inicio; idx < fim; idx++){
            double Interseção = MatrizIntersecao.values[idx];
            double Similaridade = 1 - Interseção/TotalProdutos;
            MatrizSimilaridade.values.push_back(Similaridade);
        }
    }

    return make_tuple(MatrizSimilaridade.values, MatrizSimilaridade.col_index, MatrizSimilaridade.row_ptr);
}

vector<vector<double>> mallocParaVector(double** matrizMalloc, int linhas, int colunas) {

    vector<vector<double>> resultado(linhas, vector<double>(colunas));

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            resultado[i][j] = matrizMalloc[i][j];
        }
    }

    return resultado;
}