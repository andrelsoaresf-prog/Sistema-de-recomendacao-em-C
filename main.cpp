#include "listacompras.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    if (argc < 3){
        printf("Erro: Voce esqueceu de informar o arquivo .csv ou o k!\n");
        printf("digite: ./main dados/dados_venda_cluster_(1 a 20).csv k(numero positivo maior que 0)");
        return 1;
    }

    int k = atoi(argv[2]);

    listacompras(argv[1], k);
    return 0;
}