#include <stdio.h>
#include <string.h>
#include <iostream>
#include "listacompras.h"
#include "CSR.h"
using namespace std;

vector<list<int>> listacompras(const vector<string> clientes, const vector<int> produtos){
    ListaCompras lc;
    
    for (int i = 0; i < clientes.size(); i++){
        lc.VetorCliente.push_back(clientes[i]);
        lc.VetorProduto.push_back(produtos[i]);
    }

    int contadorCliente = 0, contadorProduto = 0;

    for (int i = 0; i < lc.VetorCliente.size(); i++){
        string cliente = lc.VetorCliente[i];
        int produto = lc.VetorProduto[i];

        if (lc.MapaCliente.find(cliente) == lc.MapaCliente.end()){
            lc.MapaCliente[cliente] = contadorCliente;
            contadorCliente++;
        }

        if (lc.MapaProduto.find(produto) == lc.MapaProduto.end()){
            lc.MapaProduto[produto] = contadorProduto;
            contadorProduto++;
        }
    }

    lc.VetorLista.resize(lc.MapaCliente.size());

    for (int i = 0; i < lc.VetorCliente.size(); i++) {
        string cliente = lc.VetorCliente[i];
        int produto = lc.VetorProduto[i];

        int idCliente = lc.MapaCliente[cliente];
        int idProduto = lc.MapaProduto[produto];

        lc.VetorLista[idCliente].push_back(idProduto);
    }

    vector<list<int>> vetorlistafinal = lc.VetorLista;
    return vetorlistafinal;
}