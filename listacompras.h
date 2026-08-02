#ifndef _listacompras_H_
#define _listacompras_H_

#include <string.h>
#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

typedef struct {
    vector<int> VetorProduto;
    vector<string> VetorCliente;
    vector<string> VetorNomeProduto;
    map<string, int> MapaCliente;
    map<int, int> MapaProduto;
    vector<list<int>> VetorLista;
    vector<string> NomesProdutosUnicos;
    int k;
} ListaCompras;

vector<list<int>> listacompras(const vector<string> clientes, const vector<int> produtos);


#endif