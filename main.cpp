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
        //printf("Data: %d | Código do cliente: %s | Código do produto: %d | Nome do produto: %s\n", 
            //dados.Data, dados.CodCliente, dados.CodProduto, dados.NomeProduto);
        vetorCliente.push_back(dados.CodCliente);
    }

    for (int i = 0; i < size(vetorCliente); i++){
        cout << "código do cliente: " << vetorCliente[i] << endl;
    }

    cout << "quantidade de clientes: " << size(vetorCliente) << endl;
    
    fclose(arquivo);
    return 0;
}