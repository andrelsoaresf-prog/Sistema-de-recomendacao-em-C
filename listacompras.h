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
    vector<int> VetorProduto;
    vector<string> VetorCliente;
    map<string, int> MapaCliente;
    map<int, int> MapaProduto;
    vector<list<int>> VetorLista;
} ListaCompras;

int listacompras(char* nomeArquivo);
void mostrarProdutos(ListaCompras *listacompras, char* CodCliente);
void testador(ListaCompras *listacompras);

#endif