#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "listacompras.h"
#include "Similaridade.h"
using namespace std;

int listacompras(char* nomeArquivo, int k){
    FILE *arquivo;
    Dados dados;
    ListaCompras listacompras;

    arquivo = fopen(nomeArquivo, "r");
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
        listacompras.VetorCliente.push_back(dados.CodCliente);
        listacompras.VetorProduto.push_back(dados.CodProduto);
    }

    int contadorCliente = 0, contadorProduto = 0;

    for (int i = 0; i < listacompras.VetorCliente.size(); i++){
        string cliente = listacompras.VetorCliente[i];
        int produto = listacompras.VetorProduto[i];

        if (listacompras.MapaCliente.find(cliente) == listacompras.MapaCliente.end()){
            listacompras.MapaCliente[cliente] = contadorCliente;
            contadorCliente++;
        }

        if (listacompras.MapaProduto.find(produto) == listacompras.MapaProduto.end()){
            listacompras.MapaProduto[produto] = contadorProduto;
            contadorProduto++;
        }
    }

    listacompras.VetorLista.resize(listacompras.MapaCliente.size());

    for (int i = 0; i < listacompras.VetorCliente.size(); i++) {

        string cliente = listacompras.VetorCliente[i];
        int produto = listacompras.VetorProduto[i];

        int idCliente = listacompras.MapaCliente[cliente];
        int idProduto = listacompras.MapaProduto[produto];

        listacompras.VetorLista[idCliente].push_back(idProduto);
    }

    listacompras.k = k;

    testadorATV2(&listacompras);
    fclose(arquivo);
    return 0;
}

void mostrarProdutos(ListaCompras *listacompras, char* CodCliente){
    int indiceCliente;

    if (listacompras->MapaCliente.find(CodCliente) == listacompras->MapaCliente.end()){
        printf("Cliente não encontrado\n");
    } else{
        indiceCliente = listacompras->MapaCliente[CodCliente];

        printf("O cliente %s comprou:\n", CodCliente);

        for (int produto : listacompras->VetorLista[indiceCliente]){
            cout << "-" << produto << endl;
        }
    }
}

void testadorATV1(ListaCompras *listacompras){
    char cliente1[] = "YZ0VPF01";
    char cliente2[] = "9NZCFG01";
    char cliente3[] = "78299701";

    mostrarProdutos(listacompras, cliente1);
    mostrarProdutos(listacompras, cliente2);
    mostrarProdutos(listacompras, cliente3);
}