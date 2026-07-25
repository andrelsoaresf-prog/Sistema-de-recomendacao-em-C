#include "listacompras.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
    clock_t inicio, fim;
    inicio = clock();

    if (argc < 3){
        printf("Erro: Voce esqueceu de informar o arquivo .csv ou o k!\n");
        printf("digite: ./main dados/dados_venda_cluster_(1 a 20).csv k(numero positivo maior que 0)");
        return 1;
    }

    int k = atoi(argv[2]);

    listacompras(argv[1], k);

    fim = clock();
    double tempoDeExecucao = double(fim - inicio) / double(CLOCKS_PER_SEC);

    cout << "\nTempo de execução: " << tempoDeExecucao << endl;
    return 0;
}