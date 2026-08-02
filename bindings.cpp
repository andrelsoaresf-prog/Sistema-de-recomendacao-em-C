#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Similaridade.h"
#include "Recomendacao.h"
#include "CSR.h"

namespace py = pybind11;

PYBIND11_MODULE(resenha, m) {
    m.doc() = "Meu primeiro pacote";

    m.def("similaridade_CSR", &similaridadeCSR, "Funcao que cria a matriz similaridade no modo CSR");

    m.def("similaridade_Padrao", &similaridadePadrao, "Funcao que cria a matriz similaridade");

    m.def("recomendacao_Padrao", &recomendacaoPadrao, "Funcao que recomenda os k itens com o melhor rank");

    m.def("recomendacao_CSR", &recomendacaoCSR, "Funcao que que recomenda os k itens com melhor rank, mas no modo CSR");
}

