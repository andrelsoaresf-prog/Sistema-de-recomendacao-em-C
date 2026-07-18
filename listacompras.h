#ifndef _listacompras_H_
#define _lsitacompras_H_

#include <string.h>
#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

typedef struct {
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

int listacompras();

#endif