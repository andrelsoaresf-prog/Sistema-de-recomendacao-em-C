import csv
import resenha

def ler_lista_compras(caminho_csv):
    mapa_cliente = {}
    mapa_produto = {}
    nomes_produtos = []
    vetor_lista = []
    vetor_cliente = []
    vetor_produto = []

    with open(caminho_csv, newline="", encoding="utf-8") as f:
        arquivo = csv.reader(f)
        next(arquivo)  
 
        for linha in arquivo:
            _data, cod_cliente, cod_produto, nome_produto = linha

            cod_produto = int(cod_produto)
            nome_produto = nome_produto.strip()

            vetor_cliente.append(cod_cliente)
            vetor_produto.append(cod_produto)
 
            if cod_cliente not in mapa_cliente:
                mapa_cliente[cod_cliente] = len(mapa_cliente)
                vetor_lista.append([])
 
            if cod_produto not in mapa_produto:
                mapa_produto[cod_produto] = len(mapa_produto)
                nomes_produtos.append(nome_produto)
 

        for i in range(len(vetor_cliente)):
            id_cliente = mapa_cliente[vetor_cliente[i]]
            id_produto = mapa_produto[vetor_produto[i]]
            vetor_lista[id_cliente].append(id_produto)
 
    return mapa_cliente, mapa_produto, nomes_produtos, vetor_lista




def main():
    arquivo = "dados/dados_venda_cluster_17.csv"

    mapa_cliente, mapa_produto, nomes_produtos, vetor_lista = ler_lista_compras(arquivo)
    NumeroClientes = len(mapa_cliente)
    NumeroProdutos = len(mapa_produto)
    k = 5
    modo = 2
    




if __name__ == "__main__":
    main()