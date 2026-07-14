#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

typedef struct {
    char cabeçalho[256];
    char Data[20];
    char CodCliente[10];
    int CodProduto;
    char NomeProduto[100];
} Dados;

typedef struct {
    vector<int> vetorProduto;
    vector<string> vetorCliente;
} Vetor;

typedef struct {
    map<string, int> mapaCliente;
    map<int, int> mapaProduto;
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

    fgets(dados.cabeçalho, sizeof(dados.cabeçalho), arquivo);

    while (fscanf(arquivo, "%[^;]; %9[^;]; %d; %99[^\n]\n",
        dados.Data,
        dados.CodCliente,
        &dados.CodProduto,
        dados.NomeProduto) == 4)
    {
        vetor.vetorCliente.push_back(dados.CodCliente);
        vetor.vetorProduto.push_back(dados.CodProduto);
    }

    for (int i = 0; i < vetor.vetorCliente.size(); i++){
        string cliente = vetor.vetorCliente[i];

        if (mapa.mapaCliente.find(cliente) == mapa.mapaCliente.end()){
            mapa.mapaCliente[cliente] = mapa.mapaCliente.size();
        }
    }

    for (int i = 0; i < vetor.vetorProduto.size(); i++){
        int produto = vetor.vetorProduto[i];

        if (mapa.mapaProduto.find(produto) == mapa.mapaProduto.end()){
            mapa.mapaProduto[produto] = mapa.mapaProduto.size();
        }
    }

    for (auto& p : mapa.mapaProduto){
        cout << p.first << "->" << p.second << endl;
    }


    
    fclose(arquivo);
    return 0;
}