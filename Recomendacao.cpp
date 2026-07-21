#include "Recomendacao.h"
#include "Similaridade.h"
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

void testadorATV3(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras){
    string Cliente1 = "13574601";
    string Cliente2 = "33653401";
    string Cliente3 = "78299701";
    int IDcliente1, IDcliente2, IDcliente3;

    cout << "\n------------- ATIVIDADE 3 -------------" << endl;

    if(listacompras->MapaCliente.find(Cliente1) == listacompras->MapaCliente.end()){
        cout << "Cliente " << Cliente1 << " não encontrado" << endl;
    } else {
        IDcliente1 = listacompras->MapaCliente[Cliente1];

        cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente1 << " (ID: " << IDcliente1 << ") ---" << endl;
        recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente1);
    }

    if(listacompras->MapaCliente.find(Cliente2) == listacompras->MapaCliente.end()){
        cout << "Cliente " << Cliente2 << " não encontrado" << endl;
    } else {
        IDcliente2 = listacompras->MapaCliente[Cliente2];

        cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente2 << " (ID: " << IDcliente2 << ") ---" << endl;
        recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente2);
    }

    if(listacompras->MapaCliente.find(Cliente3) == listacompras->MapaCliente.end()){
        cout << "Cliente " << Cliente3 << " não encontrado" << endl;
    } else {
        IDcliente3 = listacompras->MapaCliente[Cliente3];

        cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente3 << " (ID: " << IDcliente3 << ") ---" << endl;
        recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente3);
    }
}