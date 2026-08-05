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

def testadorATV3(vetor_lista, nomes_produtos, mapa_clientes, numeroProdutos, MatrizSimilaridade, modo, k):
    cliente = str(input("Digite o código do cliente: "))
    numero_clientes = len(mapa_clientes)

    if cliente in mapa_clientes:
        IDcliente = mapa_clientes[cliente]

        if modo == 1 or modo == 2:
            Produtos_recomendados = resenha.recomendacao_Padrao(vetor_lista, numero_clientes, 
                                                            numeroProdutos, MatrizSimilaridade, IDcliente, k)
        elif modo == 3:
            Produtos_recomendados = resenha.recomendacao_CSR(vetor_lista, numero_clientes, 
                                                            numeroProdutos, MatrizSimilaridade, IDcliente, k)


        for i in range(k):
            IDproduto = Produtos_recomendados[i]
            print(nomes_produtos[IDproduto])

    else:
        print("cliente não encontrado")


        
