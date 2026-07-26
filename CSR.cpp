#include "CSR.h"

CSR criarMatrizComprasCSR(ListaCompras *listacompras){
    CSR MatrizCompras;
    MatrizCompras.numeroLinha = listacompras->MapaCliente.size();
    MatrizCompras.numeroColuna = listacompras->MapaProduto.size();

    int acumulador = 0;
    MatrizCompras.row_ptr.push_back(acumulador);

    for(int idCliente = 0; idCliente < MatrizCompras.numeroLinha; idCliente++){
        for (int idProduto : listacompras->VetorLista[idCliente]) {
            MatrizCompras.values.push_back(1);
            MatrizCompras.col_index.push_back(idProduto);
            acumulador++;
        }
        MatrizCompras.row_ptr.push_back(acumulador);
    }

    return MatrizCompras;
}

void similaridadeCSR(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras){

}