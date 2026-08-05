import resenha

def testadorATV1(mapa_clientes, vetor_lista, nomes_produtos):
    cliente = str(input("Digite o código do cliente: "))

    if cliente in mapa_clientes:
        IDcliente = mapa_clientes[cliente]
        print(f"O cliente {cliente} comprou esses produtos: ")

        for IDproduto in vetor_lista[IDcliente]:

            produto = nomes_produtos[IDproduto]
            print("-", produto)

    else:
        print("cliente não encontrado")


def testadorATV2(mapa_clientes, MatrizSimilaridade):
    cliente = str(input("Digite o código do cliente: "))
    numero_clientes = len(mapa_clientes)
    menor = 1
    IDcliente_similar = 0

    if cliente in mapa_clientes:
        IDcliente = mapa_clientes[cliente]

        for i in range(numero_clientes):
            if IDcliente != i:
                if (menor > MatrizSimilaridade[IDcliente][i]):
                    menor = MatrizSimilaridade[IDcliente][i]
                    IDcliente_similar = i

        print(f"O cliente mais similar com {cliente} é o cliente com ID igual a {IDcliente_similar}")
        print(f"com uma similaridade de {menor}")

    else:
        print("cliente não encontrado")

