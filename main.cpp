#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

typedef struct {
    int Data;
    char CodCliente[10];
    int CodProduto;
    char NomeProduto[100];
} Dados;

int main(){
    FILE *arquivo;
    Dados dados;
    char cabeçalho[256];
    vector<string> vetorCliente;
    vector<int> vetorProduto;
    map<string, int> mapaCliente;
    map<int, int> mapaProduto;

    arquivo = fopen("dados/dados_venda_cluster_0.csv", "r");
    if (arquivo == NULL){
        printf("deu ruim");
        return 1;
    }

    fgets(cabeçalho, sizeof(cabeçalho), arquivo);

    while (fscanf(arquivo, "%d; %9[^;]; %d; %99[^\n]\n",
        &dados.Data,
        dados.CodCliente,
        &dados.CodProduto,
        dados.NomeProduto) == 4)
    {
        vetorCliente.push_back(dados.CodCliente);
        vetorProduto.push_back(dados.CodProduto);
    }

    for (int i = 0; i < vetorCliente.size(); i++){
        string cliente = vetorCliente[i];

        if (mapaCliente.find(cliente) == mapaCliente.end()){
            mapaCliente[cliente] = mapaCliente.size();
        }
    }

    for (int i = 0; i < vetorProduto.size(); i++){
        int produto = vetorProduto[i];

        if (mapaProduto.find(produto) == mapaProduto.end()){
            mapaProduto[produto] = mapaProduto.size();
        }
    }

    for (auto& p : mapaProduto){
        cout << p.first << "->" << p.second << endl;
    }


    
    fclose(arquivo);
    return 0;
}