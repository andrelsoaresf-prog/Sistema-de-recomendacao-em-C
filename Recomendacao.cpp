#include "Recomendacao.h"
#include "Similaridade.h"
#include "Similaridade.h"
#include <algorithm>

bool compararPorRank(const Ranqueamento &a, const Ranqueamento &b){
    if (a.rank < b.rank)
        return true;
    else
        return false;
}

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
                R[produto].rank = R[produto].rank * MatrizSimilaridade[IDcliente][IDvizinho];
            }
        }
    }

    std::sort(R.begin(), R.end(), compararPorRank);

    for(int i = 0; i < listacompras->k; i++){
        cout << "produto: " << R[i].idproduto << "rank: " << R[i].rank << endl;
    }
}

void testadorATV3(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras){
    string Cliente1 = "YZ0VPF01";
    string Cliente2 = "9NZCFG01";
    string Cliente3 = "78299701";

    int IDcliente1 = listacompras->MapaCliente[Cliente1];
    int IDcliente2 = listacompras->MapaCliente[Cliente2];
    int IDcliente3 = listacompras->MapaCliente[Cliente3];

    cout << "\n--- RECOMENDAÇÕES CLIENTE 1 ---" << endl;
    recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente1);
    
    cout << "\n--- RECOMENDAÇÕES CLIENTE 2 ---" << endl;
    recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente2);
    
    cout << "\n--- RECOMENDAÇÕES CLIENTE 3 ---" << endl;
    recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente3);
}