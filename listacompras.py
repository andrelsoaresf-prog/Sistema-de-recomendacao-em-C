import csv
import resenha
import testadores as tt

def escolher_similaridade(vetor_lista, NumeroClientes, NumeroProdutos):
    modo = int(input("Digite o modo para criação da Matriz Similaridade (1 - padrão, 2 - otimizada, 3 - CSR): "))
    while(modo != 1 and modo != 2 and modo != 3):
        print("valor inválido")
        modo = int(input("Digite o modo para criação da Matriz Similaridade (1 - padrão, 2 - otimizada, 3 - CSR): "))

    if modo == 1 or modo == 2:
        MatrizSimilaridade = resenha.similaridade_Padrao(vetor_lista, NumeroClientes, NumeroProdutos, modo)

    elif modo == 3:
        MatrizSimilaridade = resenha.similaridade_CSR(vetor_lista, NumeroClientes, NumeroProdutos)

    return MatrizSimilaridade, modo

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

    MatrizSimilaridade, modo = escolher_similaridade(vetor_lista, NumeroClientes, NumeroProdutos)

    #cliente teste do csv 17 "42593401"

    sair = 1
    while sair == 1:
        escolha = int(input("\nDigite qual testador quer usar (1,2,3, -1 para sair): "))
        if escolha == -1:
            break
        if escolha != 1 and escolha != 2 and escolha != 3:
            print("valor inválido")
            escolha = int(input("Digite qual testador quer usar (1,2,3, -1 para sair): "))

        if escolha == 1:
            tt.testadorATV1(mapa_cliente ,vetor_lista, nomes_produtos)

        if escolha == 2:
            tt.testadorATV2(mapa_cliente, MatrizSimilaridade)

        if escolha == 3:
            tt.testadorATV3(vetor_lista, nomes_produtos, mapa_cliente, NumeroProdutos, MatrizSimilaridade, modo)




if __name__ == "__main__":
    main()