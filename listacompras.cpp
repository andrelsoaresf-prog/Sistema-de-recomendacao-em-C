#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "listacompras.h"
#include "Similaridade.h"
#include "Recomendacao.h" 
#include "Testadores.h"
#include "CSR.h"
using namespace std;

int listacompras(char* nomeArquivo, int k){
    FILE *arquivo;
    Dados dados;
    ListaCompras listacompras;

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo csv.\n");
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
        listacompras.VetorNomeProduto.push_back(dados.NomeProduto);
    }
    fclose(arquivo);

    int contadorCliente = 0, contadorProduto = 0;

    for (int i = 0; i < listacompras.VetorCliente.size(); i++){
        string cliente = listacompras.VetorCliente[i];
        int produto = listacompras.VetorProduto[i];
        string NomeProduto = listacompras.VetorNomeProduto[i];

        if (listacompras.MapaCliente.find(cliente) == listacompras.MapaCliente.end()){
            listacompras.MapaCliente[cliente] = contadorCliente;
            contadorCliente++;
        }

        if (listacompras.MapaProduto.find(produto) == listacompras.MapaProduto.end()){
            listacompras.MapaProduto[produto] = contadorProduto;
            listacompras.NomesProdutosUnicos.push_back(NomeProduto);
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

    similaridade(&listacompras);

    return 0;
}

void mostrarProdutos(ListaCompras *listacompras, char* CodCliente){
    int indiceCliente;

    if (listacompras->MapaCliente.find(CodCliente) == listacompras->MapaCliente.end()){
        printf("Cliente %s não encontrado\n", CodCliente);
    } else{
        indiceCliente = listacompras->MapaCliente[CodCliente];

        printf("O cliente %s comprou:\n", CodCliente);

        for (int produto : listacompras->VetorLista[indiceCliente]){
            cout << "-" << listacompras->NomesProdutosUnicos[produto] << endl;
        }
    }
}