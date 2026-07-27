#include "Recomendacao.h"
#include "Similaridade.h"
#include "CSR.h"
#include <algorithm>

bool compararPorRank(const Ranqueamento &a, const Ranqueamento &b){
    if (a.rank == b.rank){
        return a.idproduto < b.idproduto;
    }
    return a.rank < b.rank;
}

void recomendacao(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras, int IDcliente){
    vector<int> ListaVizinhos;
    int NumeroCLientes = listacompras->MapaCliente.size();
    int NumeroProdutos = listacompras->MapaProduto.size();

    for (int j = 0; j < NumeroCLientes; j++){
        if (IDcliente != j){
            if(MatrizSimilaridade[IDcliente][j] < 1.0){
                ListaVizinhos.push_back(j);
            }
        }
    }

    vector<Ranqueamento> VetorR(NumeroProdutos);
    for(int i = 0; i < NumeroProdutos; i++){
        VetorR[i].idproduto = i;
        VetorR[i].rank = 1.0; 
    }

    for (int produto = 0; produto < NumeroProdutos; produto++){
        if (MatrizCompras[IDcliente][produto] == 1){
            VetorR[produto].rank = 10;
        }
    }


    for (int s = 0; s < ListaVizinhos.size(); s++){
        int IDvizinho = ListaVizinhos[s];

        for(int produto : listacompras->VetorLista[IDvizinho]){
            if (MatrizCompras[IDcliente][produto] == 0){
                VetorR[produto].rank = VetorR[produto].rank * MatrizSimilaridade[IDcliente][IDvizinho];
            }
        }
    }

    std::sort(VetorR.begin(), VetorR.end(), compararPorRank);

    for(int i = 0; i < listacompras->k; i++){
        int IDproduto = VetorR[i].idproduto;
        string NomeProduto = listacompras->NomesProdutosUnicos[IDproduto];

        cout << "Produto: " << NomeProduto << " | Rank: " << VetorR[i].rank << endl;
    }
}

void recomendacaoCSR(ListaCompras *listacompras, Matrizes *matriz, int IDcliente){
    Matrizes *Matriz = matriz;
    vector<int> ListaVizinhos;
    vector<double> ListaSimilaridadeVizinhos;

    int NumeroCLientes = Matriz->MatrizCompras.numeroLinha;
    int NumeroProdutos = Matriz->MatrizCompras.numeroColuna;

    int inicioSimilaridade = Matriz->MatrizSimilaridade.row_ptr[IDcliente];
    int fimSimilaridade = Matriz->MatrizSimilaridade.row_ptr[IDcliente + 1];

    for (int idx = inicioSimilaridade; idx < fimSimilaridade; idx++){
        int IDvizinho = Matriz->MatrizSimilaridade.col_index[idx];
        double valorSimilaridade = Matriz->MatrizSimilaridade.values[idx];

        if (IDcliente != IDvizinho && valorSimilaridade < 1){
            ListaVizinhos.push_back(IDvizinho);
            ListaSimilaridadeVizinhos.push_back(valorSimilaridade);
        }
    }

    vector<Ranqueamento> VetorR(NumeroProdutos);
    for(int i = 0; i < NumeroProdutos; i++){
        VetorR[i].idproduto = i;
        VetorR[i].rank = 1.0; 
    }

    int inicioCompra = Matriz->MatrizCompras.row_ptr[IDcliente];
    int fimCompra = Matriz->MatrizCompras.row_ptr[IDcliente + 1];

    for (int idx = inicioCompra; idx < fimCompra; idx ++){
        int IDprodutojacomprado = Matriz->MatrizCompras.col_index[idx];
        VetorR[IDprodutojacomprado].rank = 10;
    }

    for (int s = 0; s < ListaVizinhos.size(); s++){
        int IDvizinho = ListaVizinhos[s];
        double SimilaridadeVizinho = ListaSimilaridadeVizinhos[s];

        for (int produto : listacompras->VetorLista[IDvizinho]){
            if (VetorR[produto].rank != 10){
                VetorR[produto].rank = VetorR[produto].rank * SimilaridadeVizinho;
            }
        }
    }

    std::sort(VetorR.begin(), VetorR.end(), compararPorRank);

    for(int i = 0; i < listacompras->k; i++){
        int IDproduto = VetorR[i].idproduto;
        string NomeProduto = listacompras->NomesProdutosUnicos[IDproduto];

        cout << "Produto: " << NomeProduto << " | Rank: " << VetorR[i].rank << endl;
    }
}