#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "listacompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"
#include "CSR.h"



namespace py = pybind11;

PYBIND11_MODULE(resenha, m) {
    m.doc() = "Meu primeiro pacote";

    m.def("listacompras", &listacompras, "Funcao que cria o vetor de listas");

    m.def("similaridade", &similaridade, "Funcao que cria a matriz similaridade");

    m.def("recomendacao", &recomendacao, "Funcao que recomenda os k itens com o melhor rank");
}

