#import resenha #TANTO ESSE IMPORT QUANTO OS INCLUDES DO PYBIND11 ESTÃO DANDO ERRO
import csv

arquivo = input()

listaDatas = []
listaCodCliente = []
listaCodProduto = []
listaNomes = []

with open(arquivo, 'r') as a:
    next(arquivo)

    for linha in arquivo:
        DATA_COMPRA, COD_CLIENTE, COD_PRODUTO, NOME_PRODUTO = linha.strip().split(',')

        listaDatas.append(DATA_COMPRA)
        listaCodCliente.append(COD_CLIENTE)
        listaCodProduto.append(int(COD_PRODUTO))
        listaNomes.append(NOME_PRODUTO)