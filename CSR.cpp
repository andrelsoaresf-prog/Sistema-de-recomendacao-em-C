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

CSR criarMatrizIntersecaoCSR(ListaCompras *listacompras, CSR MatrizCompras){
    CSR MatrizIntersecao;
    Auxiliar aux;
    aux.cont = 0;
    MatrizIntersecao.row_ptr.push_back(0);
    MatrizIntersecao.numeroLinha = MatrizCompras.numeroLinha;
    MatrizIntersecao.numeroColuna = MatrizCompras.numeroLinha;

    for(int i = 0; i < MatrizCompras.numeroLinha; i++){
        if(MatrizCompras.row_ptr[i] == MatrizCompras.row_ptr[i + 1]){
            MatrizIntersecao.row_ptr.push_back(aux.cont);;
            continue;
        }
        for (int j = 0; j < MatrizCompras.numeroLinha; j++){
            aux.soma = 0;
            aux.p = MatrizCompras.row_ptr[i];
            aux.q = MatrizCompras.row_ptr[j];
            aux.fimI = MatrizCompras.row_ptr[i + 1];
            aux.fimJ = MatrizCompras.row_ptr[j + 1];
            while(aux.p < aux.fimI && aux.q < aux.fimJ){
                if(MatrizCompras.col_index[aux.p] == MatrizCompras.col_index[aux.q]){
                    aux.soma += MatrizCompras.values[aux.p] * MatrizCompras.values[aux.q];
                    aux.p++;
                    aux.q++;

                } else if (MatrizCompras.col_index[aux.p] < MatrizCompras.col_index[aux.q]){
                    aux.p++;
                } else if (MatrizCompras.col_index[aux.p] > MatrizCompras.col_index[aux.q]){
                    aux.q++;
                }
            }
            if(aux.soma != 0){
                MatrizIntersecao.values.push_back(aux.soma);
                MatrizIntersecao.col_index.push_back(j);
                aux.cont++;
            }
        }
        MatrizIntersecao.row_ptr.push_back(aux.cont);
    }

    return MatrizIntersecao;
}