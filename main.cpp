#include "listacompras.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    if (argc < 3){
        printf("Erro: Voce esqueceu de informar o arquivo .csv!");
        printf("digite: ./main dados/dados_venda_cluster_(1 a 20).csv 5");
        return 1;
    }

    listacompras(argv[1], atoi(argv[2]));
    return 0;
}