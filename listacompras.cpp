#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "listacompras.h"
#include "Similaridade.h"
#include "Recomendacao.h" 
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


    int NumeroClientes = listacompras.MapaCliente.size();
    int NumeroProdutos = listacompras.MapaProduto.size();

    int **MatrizCompras = (int **) malloc(NumeroClientes * sizeof(int*));
    if(MatrizCompras == NULL){
        printf("erro de memória");
        return 1;
    }
    
    for (int i = 0; i < NumeroClientes; i++){
        MatrizCompras[i] = (int *) malloc(NumeroProdutos * sizeof(int));

        if (MatrizCompras[i] == NULL){
            printf("erro de memória");
            return 1;
        }
    }

    double **MatrizSimilaridade = (double **) malloc(NumeroClientes * sizeof(double*));
    if(MatrizSimilaridade == NULL){
        printf("erro de memória");
        return 1;
    }
    
    for (int i = 0; i < NumeroClientes; i++){
        MatrizSimilaridade[i] = (double *) malloc(NumeroClientes * sizeof(double));

        if (MatrizSimilaridade[i] == NULL){
            printf("erro de memória");
            return 1;
        }
    }
    int escolha;
    printf("\n1 para algoritmo padrão de similaridade\n2 para algoritmo adaptado"); scanf("%d", &escolha);
    if (escolha != 1 && escolha != 2){
        printf("\nInválido! Escolha novamente.");
        printf("\n1 para algoritmo padrão de similaridade\n2 para algoritmo adaptado"); scanf("%d", &escolha);
    }

    similaridade(&listacompras, MatrizSimilaridade, MatrizCompras, escolha);

    testadorATV1(&listacompras);
    testadorATV2(&listacompras, MatrizSimilaridade);
    testadorATV3(&listacompras, MatrizSimilaridade, MatrizCompras);

    for (int i = 0; i < NumeroClientes; i++) {
        free(MatrizCompras[i]);
        free(MatrizSimilaridade[i]);
    }
    free(MatrizCompras);
    MatrizCompras = NULL;

    free(MatrizSimilaridade);
    MatrizSimilaridade = NULL;

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
            cout << "-" << produto << endl;
        }
    }
}

void testadorATV1(ListaCompras *listacompras){
    char cliente1[] = "13574601";
    char cliente2[] = "33653401";
    char cliente3[] = "78299701";

    cout << "\n------------- ATIVIDADE 1 -------------" << endl;
    mostrarProdutos(listacompras, cliente1);
    mostrarProdutos(listacompras, cliente2);
    mostrarProdutos(listacompras, cliente3);
}