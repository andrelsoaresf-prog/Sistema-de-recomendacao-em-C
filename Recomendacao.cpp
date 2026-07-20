#include "Recomendacao.h"
#include "Similaridade.h"
#include "Similaridade.h"
#include <algorithm>

void recomendacao(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras, int IDcliente){
    vector<int> listaSimilaridade;
    int NumeroCLientes = listacompras->MapaCliente.size();
    int NumeroProdutos = listacompras->MapaProduto.size();

    for (int j = 0; j < NumeroCLientes; j++){
        if (IDcliente != j){
            if(MatrizSimilaridade[IDcliente][j] < 1){
                listaSimilaridade.push_back(j);
            }
        }
    }

    vector<Ranqueamento> R(NumeroProdutos);
    for(int i = 0; i < NumeroProdutos; i++){
        R[i].idproduto = i;
        R[i].rank = 1;
    }

    for (int s = 0; s < listaSimilaridade.size(); s++){
        int IDvizinho = listaSimilaridade[s];

        for(int produto : listacompras->VetorLista[IDvizinho]){
            if (MatrizCompras[IDcliente][produto] == 0){
                R[produto].rank = R[produto].rank * MatrizSimilaridade[IDcliente][s];
            }
        }
    }

    std::sort(R.begin(), R.end(), compararPorRank);

    for(int i = 0; i < listacompras->k; i++){
        cout << "produto: " << R[i].idproduto << "rank: " << R[i].rank << endl;
    }
}

bool compararPorRank(const Ranqueamento &a, const Ranqueamento &b){
    if (a.rank < b.rank)
        return true;
    else
        return false;
}