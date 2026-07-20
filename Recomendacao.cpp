#include "Recomendacao.h"
#include "Similaridade.h"
#include <algorithm>

bool compararPorRank(const Ranqueamento &a, const Ranqueamento &b){
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

    vector<Ranqueamento> R(NumeroProdutos);
    for(int i = 0; i < NumeroProdutos; i++){
        R[i].idproduto = i;
        R[i].rank = 1.0; 
    }

    for (int s = 0; s < ListaVizinhos.size(); s++){
        int IDvizinho = ListaVizinhos[s];

        for(int produto : listacompras->VetorLista[IDvizinho]){
            if (MatrizCompras[IDcliente][produto] == 0){
                R[produto].rank = R[produto].rank * MatrizSimilaridade[IDcliente][IDvizinho];
            }
        }
    }

    std::sort(R.begin(), R.end(), compararPorRank);

    for(int i = 0; i < listacompras->k; i++){
        int IDproduto = R[i].idproduto;
        string NomeProduto = listacompras->NomesProdutosUnicos[IDproduto];

        cout << "Produto: " << NomeProduto << " | Rank: " << R[i].rank << endl;
    }
}

int testadorATV3(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras){
    string Cliente1 = "YZ0VPF01";
    string Cliente2 = "9NZCFG01";
    string Cliente3 = "78299701";
    int IDcliente1;
    int IDcliente2;
    int IDcliente3;

    if(listacompras->MapaCliente.find(Cliente1) == listacompras->MapaCliente.end()
    || listacompras->MapaCliente.find(Cliente2) == listacompras->MapaCliente.end()
    || listacompras->MapaCliente.find(Cliente3) == listacompras->MapaCliente.end()){

        printf("\nClientes não encontrados\n");
        return 1;

    } else {
        int IDcliente1 = listacompras->MapaCliente[Cliente1];
        int IDcliente2 = listacompras->MapaCliente[Cliente2];
        int IDcliente3 = listacompras->MapaCliente[Cliente3];
    }

    cout << "\n------------- ATIVIDADE 3 -------------" << endl;
    cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente1 << " (ID: " << IDcliente1 << ") ---" << endl;
    recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente1);
    
    cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente2 << " (ID: " << IDcliente2 << ") ---" << endl;
    recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente2);
    
    cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente3 << " (ID: " << IDcliente3 << ") ---" << endl;
    recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente3);

    return 0;
}