#ifndef _listacompras_H_
#define _listacompras_H_

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
    vector<string> VetorNomeProduto;
    map<string, int> MapaCliente;
    map<int, int> MapaProduto;
    map<string, int> MapaNomeProduto;
    vector<list<int>> VetorLista;
    int k;
} ListaCompras;

int listacompras(char* nomeArquivo, int k);
void mostrarProdutos(ListaCompras *listacompras, char* CodCliente);
void testadorATV1(ListaCompras *listacompras);

#endif