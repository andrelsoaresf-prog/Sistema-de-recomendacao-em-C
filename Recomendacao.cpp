#include "Recomendacao.h"
#include "CSR.h"
#include <algorithm>
#include <tuple> 

bool compararPorRank(const Ranqueamento &a, const Ranqueamento &b){
    if (a.rank == b.rank){
        return a.idproduto < b.idproduto;
    }
    return a.rank > b.rank; 
}

vector<int> recomendacaoPadrao(const vector<list<int>> &vetorLista, 
                  int numeroClientes, 
                  int numeroProdutos, 
                  const vector<vector<double>> &matrizSimilaridade, 
                  int IDcliente, 
                  int k){

    vector<int> ListaVizinhos;
    for (int j = 0; j < numeroClientes; j++){
        if (IDcliente != j){
            if (matrizSimilaridade[IDcliente][j] < 1.0){
                ListaVizinhos.push_back(j);
            }
        }
    }

    vector<Ranqueamento> VetorR(numeroProdutos);
    for (int i = 0; i < numeroProdutos; i++){
        VetorR[i].idproduto = i;
        VetorR[i].rank = 1.0; 
    }

    for (int produto : vetorLista[IDcliente]) {
        if (produto >= 0 && produto < numeroProdutos) {
            VetorR[produto].rank = 10.0;
        }
    }

    for (size_t s = 0; s < ListaVizinhos.size(); s++){
        int IDvizinho = ListaVizinhos[s];
        double sim = matrizSimilaridade[IDcliente][IDvizinho];

        for (int produto : vetorLista[IDvizinho]){
            if (VetorR[produto].rank != 10.0){
                VetorR[produto].rank *= sim;
            }
        }
    }

    std::sort(VetorR.begin(), VetorR.end(), compararPorRank);

    int tamanhoReal = std::min(k, numeroProdutos);
    vector<int> ProdutosRecomendados(tamanhoReal);

    for (int i = 0; i < tamanhoReal; i++){
        ProdutosRecomendados[i] = VetorR[i].idproduto;
    }

    return ProdutosRecomendados;
}

vector<int> recomendacaoCSR(const vector<list<int>> &vetorLista, 
                  int numeroClientes, 
                  int numeroProdutos, 
                  const tuple<vector<double>, vector<int>, vector<int>> &ValoresTupla, 
                  int IDcliente, 
                  int k){

    vector<int> ListaVizinhos;
    vector<double> ListaSimilaridadeVizinhos;

    CSR MatrizSimilaridade;
    MatrizSimilaridade.values = get<0>(ValoresTupla);
    MatrizSimilaridade.col_index = get<1>(ValoresTupla);
    MatrizSimilaridade.row_ptr = get<2>(ValoresTupla);

    int inicioSimilaridade = MatrizSimilaridade.row_ptr[IDcliente];
    int fimSimilaridade = MatrizSimilaridade.row_ptr[IDcliente + 1];

    for (int idx = inicioSimilaridade; idx < fimSimilaridade; idx++){
        int IDvizinho = MatrizSimilaridade.col_index[idx];
        double valorSimilaridade = MatrizSimilaridade.values[idx];

        if (IDcliente != IDvizinho && valorSimilaridade < 1.0){
            ListaVizinhos.push_back(IDvizinho);
            ListaSimilaridadeVizinhos.push_back(valorSimilaridade);
        }
    }

    vector<Ranqueamento> VetorR(numeroProdutos);
    for(int i = 0; i < numeroProdutos; i++){
        VetorR[i].idproduto = i;
        VetorR[i].rank = 1.0; 
    }
    
    DadosCompras vetor;
    vetor.VetorLista = vetorLista;
    vetor.NumeroClientes = numeroClientes;
    vetor.NumeroProdutos = numeroProdutos;

    CSR MatrizCompras = criarMatrizComprasCSR(vetor);

    int inicioCompra = MatrizCompras.row_ptr[IDcliente];
    int fimCompra = MatrizCompras.row_ptr[IDcliente + 1];

    for (int idx = inicioCompra; idx < fimCompra; idx++){
        int IDprodutojacomprado = MatrizCompras.col_index[idx];
        VetorR[IDprodutojacomprado].rank = 10.0;
    }

    for (size_t s = 0; s < ListaVizinhos.size(); s++){
        int IDvizinho = ListaVizinhos[s];
        double SimilaridadeVizinho = ListaSimilaridadeVizinhos[s];

        for (int produto : vetorLista[IDvizinho]){
            if (VetorR[produto].rank != 10.0){
                VetorR[produto].rank *= SimilaridadeVizinho;
            }
        }
    }

    std::sort(VetorR.begin(), VetorR.end(), compararPorRank);

    int tamanhoReal = std::min(k, numeroProdutos);
    vector<int> ProdutosRecomendados(tamanhoReal);

    for (int i = 0; i < tamanhoReal; i++){
        ProdutosRecomendados[i] = VetorR[i].idproduto;
    }

    return ProdutosRecomendados;
}