#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

typedef struct {
    char cabecalho[256];
    char Data[20];
    char CodCliente[10];
    int CodProduto;
    char NomeProduto[100];
} Dados;

typedef struct {
    vector<int> Produto;
    vector<string> Cliente;
} Vetor;

typedef struct {
    map<string, int> Cliente;
    map<int, int> Produto;
} Mapa;

int main(){
    FILE *arquivo;
    Dados dados;
    Vetor vetor;
    Mapa mapa;

    arquivo = fopen("dados/dados_venda_cluster_0.csv", "r");
    if (arquivo == NULL){
        printf("deu ruim");
        return 1;
    }

    fgets(dados.cabecalho, sizeof(dados.cabecalho), arquivo);

    while (fscanf(arquivo, "%[^;];%9[^;];%d;%99[^\n]\n",
        dados.Data,
        dados.CodCliente,
        &dados.CodProduto,
        dados.NomeProduto) == 4)
    {
        vetor.Cliente.push_back(dados.CodCliente);
        vetor.Produto.push_back(dados.CodProduto);
    }

    int contador = 0;

    for (int i = 0; i < vetor.Cliente.size(); i++){
        string cliente = vetor.Cliente[i];

        if (mapa.Cliente.find(cliente) == mapa.Cliente.end()){
            mapa.Cliente[cliente] = contador;
            contador++;
        }
    }

    contador = 0;

    for (int i = 0; i < vetor.Produto.size(); i++){
        int produto = vetor.Produto[i];

        if (mapa.Produto.find(produto) == mapa.Produto.end()){
            mapa.Produto[produto] = contador;
            contador++;
        }
    }

    vector<list<int>> listaCompras(mapa.Cliente.size());

    for (int i = 0; i < vetor.Cliente.size(); i++) {

        string cliente = vetor.Cliente[i];
        int produto = vetor.Produto[i];

        int idCliente = mapa.Cliente[cliente];
        int idProduto = mapa.Produto[produto];

        listaCompras[idCliente].push_back(idProduto);
    }

    for (int i = 0; i < listaCompras.size(); i++) {
    cout << "Cliente ID " << i << " comprou os produtos: ";
    
    for (int idProduto : listaCompras[i]) {
        cout << idProduto << " ";
    }
    
    cout << endl; 
    }

    cout << "tem: " << mapa.Cliente.size() << " clientes" << endl;
    cout << "tem: " << mapa.Produto.size() << " produtos" << endl;
    
    fclose(arquivo);
    return 0;
}