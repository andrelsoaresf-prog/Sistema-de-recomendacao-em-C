#include "Testadores.h"
#include "listacompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"

void testadorATV1(ListaCompras *listacompras){
    char cliente1[] = "9OL9MJ01";
    char cliente2[] = "99DAS601";
    char cliente3[] = "9O3O4Z01";

    cout << "\n------------- ATIVIDADE 1 -------------" << endl;
    mostrarProdutos(listacompras, cliente1);
    mostrarProdutos(listacompras, cliente2);
    mostrarProdutos(listacompras, cliente3);
}

void testadorATV2(ListaCompras *listacompras, double **MatrizSimilaridade){
    if (MatrizSimilaridade == NULL){
        cout << "\nTestador 2 requer o modo 1 ou 2 (matriz densa). Rode novamente escolhendo um desses modos." << endl;
        return;
    }

    int IDcliente1 = 7;
    int IDcliente2 = 13;

    cout << "\n------------- ATIVIDADE 2 -------------" << endl;
    clienteSimilar(listacompras, MatrizSimilaridade, IDcliente1);
    clienteSimilar(listacompras, MatrizSimilaridade, IDcliente2);
}

void testadorATV3(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras, Matrizes *matriz, int modo){
    string Cliente1 = "9OL9MJ01";
    string Cliente2 = "99DAS601";
    string Cliente3 = "9O3O4Z01";
    int IDcliente1, IDcliente2, IDcliente3;

    cout << "\n------------- ATIVIDADE 3 -------------" << endl;

    if(listacompras->MapaCliente.find(Cliente1) == listacompras->MapaCliente.end()){
        cout << "Cliente " << Cliente1 << " não encontrado" << endl;
    } else {
        IDcliente1 = listacompras->MapaCliente[Cliente1];

        cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente1 << " (ID: " << IDcliente1 << ") ---" << endl;
        if (modo == 3){
            recomendacaoCSR(listacompras, matriz, IDcliente1);
        }
        else{
           recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente1);
        }
    }

    if(listacompras->MapaCliente.find(Cliente2) == listacompras->MapaCliente.end()){
        cout << "Cliente " << Cliente2 << " não encontrado" << endl;
    } else {
        IDcliente2 = listacompras->MapaCliente[Cliente2];

        cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente2 << " (ID: " << IDcliente2 << ") ---" << endl;
        if (modo == 3){
            recomendacaoCSR(listacompras, matriz, IDcliente2);
        }
        else{
           recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente2);
        }
    }

    if(listacompras->MapaCliente.find(Cliente3) == listacompras->MapaCliente.end()){
        cout << "Cliente " << Cliente3 << " não encontrado" << endl;
    } else {
        IDcliente3 = listacompras->MapaCliente[Cliente3];

        cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente3 << " (ID: " << IDcliente3 << ") ---" << endl;
        if (modo == 3){
            recomendacaoCSR(listacompras, matriz, IDcliente3);
        }
        else{
           recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente3);
        }
    }
}

void escolhertestador(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras, Matrizes *matriz, int modo){
    int testador;
    do {
        printf("\nDigite qual testador deseja verificar (1, 2, 3, 5 ou -1 para sair): ");
        scanf("%d", &testador);

        switch (testador) {
            case 1:
                testadorATV1(listacompras);
                break;
            case 2:
                testadorATV2(listacompras, MatrizSimilaridade);
                break;
            case 3:
                testadorATV3(listacompras, MatrizSimilaridade, MatrizCompras, matriz, modo);
                break;
            case 5:
                testadorATV5(listacompras, MatrizSimilaridade, matriz, modo);
                break;
            case -1:
                printf("Saindo do menu de testes...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (testador != -1);
}

void testadorATV5(ListaCompras *listacompras, double **MatrizSimilaridade, Matrizes *matriz, int modo){
    size_t tamanho = 0;
    int NumeroClientes = listacompras->MapaCliente.size();

    if (modo == 1 || modo == 2){
        tamanho = (size_t)NumeroClientes * sizeof(double *)
                + (size_t)NumeroClientes * (size_t)NumeroClientes * sizeof(double);
    }

    else if (modo == 3){
        CSR &similaridade = matriz->MatrizSimilaridade;
        tamanho = similaridade.row_ptr.size()   * sizeof(int)
                + similaridade.col_index.size() * sizeof(int)
                + similaridade.values.size()    * sizeof(double);
    }
    if (tamanho > 1048576){
        tamanho = tamanho/(1024*1024);
    }

    cout << "\nMemória utilizada pela MatrizSimilaridade (modo " << modo << "): "
         << tamanho << " Megabytes" << endl;
}