import Sistema_Recomendacao

def testadorATV1(mapa_clientes, vetor_lista, nomes_produtos):
    cliente = str(input("Digite o código do cliente: "))

    if cliente in mapa_clientes:
        IDcliente = mapa_clientes[cliente]
        print(f"\nO cliente {cliente} comprou esses produtos: \n")

        for IDproduto in vetor_lista[IDcliente]:

            produto = nomes_produtos[IDproduto]
            print("-", produto)

    else:
        print("cliente não encontrado")


def testadorATV2(mapa_clientes, MatrizSimilaridade, modo):
    cliente = str(input("Digite o código do cliente: "))
    
    if cliente in mapa_clientes:
        IDcliente = mapa_clientes[cliente]
        menor = 1.0
        IDcliente_similar = 0

        if modo == 1 or modo == 2:
            numero_clientes = len(mapa_clientes)

            for i in range(numero_clientes):
                if IDcliente != i:
                    if menor > MatrizSimilaridade[IDcliente][i]:
                        menor = MatrizSimilaridade[IDcliente][i]
                        IDcliente_similar = i

        elif modo == 3:
            values, col_index, row_ptr = MatrizSimilaridade

            inicio = row_ptr[IDcliente]
            fim = row_ptr[IDcliente + 1]

            for idx in range(inicio, fim):
                coluna = col_index[idx]
                sim = values[idx]

                if coluna != IDcliente:
                    if menor > sim:
                        menor = sim
                        IDcliente_similar = coluna

        print(f"\nO cliente mais similar com {cliente} é o cliente com ID igual a {IDcliente_similar}")
        print(f"com uma similaridade de {menor}\n")

    else:
        print("cliente não encontrado")

def testadorATV3(vetor_lista, nomes_produtos, mapa_clientes, numeroProdutos, MatrizSimilaridade, modo):
    cliente = str(input("Digite o código do cliente: "))
    numero_clientes = len(mapa_clientes)
    k = int(input("Digite quantos produtos quer mostrar: "))

    if cliente in mapa_clientes:
        IDcliente = mapa_clientes[cliente]

        if modo == 1 or modo == 2:
            Produtos_recomendados = Sistema_Recomendacao.recomendacao_Padrao(vetor_lista, numero_clientes, 
                                                            numeroProdutos, MatrizSimilaridade, IDcliente, k)
        elif modo == 3:
            Produtos_recomendados = Sistema_Recomendacao.recomendacao_CSR(vetor_lista, numero_clientes, 
                                                            numeroProdutos, MatrizSimilaridade, IDcliente, k)


        print(f"\nOs {k} produtos mais recomendados são :")
        for IDproduto in Produtos_recomendados:
            print(nomes_produtos[IDproduto])

    else:
        print("cliente não encontrado")
