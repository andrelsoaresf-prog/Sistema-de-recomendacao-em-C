#include "listacompras.h"
#include <stdio.h>

int main(int argc, char* argv[]){

    if (argc < 2){
        printf("Erro: Voce esqueceu de informar o arquivo .csv!");
        return 1;
    }

    listacompras(argv[1]);
    return 0;
}