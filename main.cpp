#include "listacompras.h"
#include <stdio.h>

int main(int argc, char* argv[]){

    if (argc < 2){
        printf("Erro: Voce esqueceu de informar o arquivo .csv!");
        printf("digite: ./main dados/dados_venda_cluster_(1 a 20).csv");
        return 1;
    }

    listacompras(argv[1]);
    return 0;
}