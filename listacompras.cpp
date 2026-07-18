#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "listacompras.h"
using namespace std;

int listacompras(char* nomeArquivo){
    FILE *arquivo;
    Dados dados;
    Vetor vetor;
    Mapa mapa;
    char caminhocompleto[100];
    sprintf(caminhocompleto, "dados/%s", nomeArquivo);

    arquivo = fopen(caminhocompleto, "r");
    if (arquivo == NULL){
        printf("deu ruim");
        return 1;
    }

    fscanf(arquivo, "%*[^\n]\n");

    while (fscanf(arquivo, "%[^,],%9[^,],%d,%99[^\n]\n",
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

    vector<list<int>> ListaCompras(mapa.Cliente.size());

    for (int i = 0; i < vetor.Cliente.size(); i++) {

        string cliente = vetor.Cliente[i];
        int produto = vetor.Produto[i];

        int idCliente = mapa.Cliente[cliente];
        int idProduto = mapa.Produto[produto];

        ListaCompras[idCliente].push_back(idProduto);
    }

    for (int i = 0; i < ListaCompras.size(); i++) {
    cout << "Cliente ID " << i << " comprou os produtos: ";
    
    for (int idProduto : ListaCompras[i]) {
        cout << idProduto << " ";
    }
    
    cout << endl; 
    }
    
    fclose(arquivo);
    return 0;
}