#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "listacompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"
#include "CSR.h"
#include "Testadores.h"
using namespace std;

int similaridadePadrao(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras, int escolha){
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

    if (escolha == 1){
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

    else if (escolha == 2){
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

int similaridade(ListaCompras *listacompras, Matrizes *Matriz){
    int escolha;

    printf("\n1 para algoritmo padrão de similaridade\n2 para algoritmo adaptado\n3 para algoritmo com CSR\n");
    scanf("%d", &escolha);
    while (escolha != 1 && escolha != 2 && escolha != 3){
        printf("\nInválido! Escolha novamente.");
        printf("\n1 para algoritmo padrão de similaridade\n2 para algoritmo adaptado\n3 para algoritmo com CSR\n");
        scanf("%d", &escolha);
    }

    if (escolha == 1 || escolha == 2){
        int NumeroClientes = listacompras->MapaCliente.size();
        int NumeroProdutos = listacompras->MapaProduto.size();

        int **MatrizCompras = (int **) malloc(NumeroClientes * sizeof(int*));
        if(MatrizCompras == NULL){
            printf("erro de memória");
            return 1;
        }

        for (int i = 0; i < NumeroClientes; i++){
            MatrizCompras[i] = (int *) malloc(NumeroProdutos * sizeof(int));

            if (MatrizCompras[i] == NULL){
                printf("erro de memória");
                return 1;
            }
        }

        double **MatrizSimilaridade = (double **) malloc(NumeroClientes * sizeof(double*));
        if(MatrizSimilaridade == NULL){
            printf("erro de memória");
            return 1;
        }

        for (int i = 0; i < NumeroClientes; i++){
            MatrizSimilaridade[i] = (double *) malloc(NumeroClientes * sizeof(double));

            if (MatrizSimilaridade[i] == NULL){
                printf("erro de memória");
                return 1;
            }
        }

        similaridadePadrao(listacompras, MatrizSimilaridade, MatrizCompras, escolha);

        escolhertestador(listacompras, MatrizSimilaridade, MatrizCompras, Matriz, escolha);

        for (int i = 0; i < NumeroClientes; i++) {
            free(MatrizCompras[i]);
            free(MatrizSimilaridade[i]);
        }
        free(MatrizCompras);
        MatrizCompras = NULL;

        free(MatrizSimilaridade);
        MatrizSimilaridade = NULL;
    }

    if (escolha == 3){
        *Matriz = similiradadeCSR(listacompras);

        escolhertestador(listacompras, nullptr, nullptr, Matriz, escolha);
    }

    return 0;
}

Matrizes similiradadeCSR(ListaCompras *listacompras){
    CSR MatrizCompras = criarMatrizComprasCSR(listacompras);
    CSR MatrizIntersecao = criarMatrizIntersecaoCSR(listacompras, MatrizCompras);

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

    Matrizes matriz;
    matriz.MatrizCompras = MatrizCompras;
    matriz.MatrizIntersecao = MatrizIntersecao;
    matriz.MatrizSimilaridade = MatrizSimilaridade;

    return matriz;
}