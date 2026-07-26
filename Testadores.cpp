#include "Testadores.h"
#include "listacompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"

void testadorATV1(ListaCompras *listacompras){
    char cliente1[] = "13574601";
    char cliente2[] = "33653401";
    char cliente3[] = "78299701";

    cout << "\n------------- ATIVIDADE 1 -------------" << endl;
    mostrarProdutos(listacompras, cliente1);
    mostrarProdutos(listacompras, cliente2);
    mostrarProdutos(listacompras, cliente3);
}

void testadorATV2(ListaCompras *listacompras, double **MatrizSimilaridade){
    int IDcliente1 = 7;
    int IDcliente2 = 13;

    cout << "\n------------- ATIVIDADE 2 -------------" << endl;
    clienteSimilar(listacompras, MatrizSimilaridade, IDcliente1);
    clienteSimilar(listacompras, MatrizSimilaridade, IDcliente2);
}

void testadorATV3(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras){
    string Cliente1 = "13574601";
    string Cliente2 = "33653401";
    string Cliente3 = "78299701";
    int IDcliente1, IDcliente2, IDcliente3;

    cout << "\n------------- ATIVIDADE 3 -------------" << endl;

    if(listacompras->MapaCliente.find(Cliente1) == listacompras->MapaCliente.end()){
        cout << "Cliente " << Cliente1 << " não encontrado" << endl;
    } else {
        IDcliente1 = listacompras->MapaCliente[Cliente1];

        cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente1 << " (ID: " << IDcliente1 << ") ---" << endl;
        recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente1);
    }

    if(listacompras->MapaCliente.find(Cliente2) == listacompras->MapaCliente.end()){
        cout << "Cliente " << Cliente2 << " não encontrado" << endl;
    } else {
        IDcliente2 = listacompras->MapaCliente[Cliente2];

        cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente2 << " (ID: " << IDcliente2 << ") ---" << endl;
        recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente2);
    }

    if(listacompras->MapaCliente.find(Cliente3) == listacompras->MapaCliente.end()){
        cout << "Cliente " << Cliente3 << " não encontrado" << endl;
    } else {
        IDcliente3 = listacompras->MapaCliente[Cliente3];

        cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente3 << " (ID: " << IDcliente3 << ") ---" << endl;
        recomendacao(listacompras, MatrizSimilaridade, MatrizCompras, IDcliente3);
    }
}

void escolhertestador(ListaCompras *listacompras, double **MatrizSimilaridade, int **MatrizCompras){
    int testador;
    do {
        printf("\nDigite qual testador deseja verificar (1, 2, 3, 5 ou -1 para nenhum): ");
        scanf("%d", &testador);

        switch (testador) {
            case 1:
                testadorATV1(listacompras);
                break;
            case 2:
                testadorATV2(listacompras, MatrizSimilaridade);
                break;
            case 3:
                testadorATV3(listacompras, MatrizSimilaridade, MatrizCompras);
                break;
            case 5:
                testadorATV5(listacompras);
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

void testadorATV5(ListaCompras *listacompras){
    string Cliente1 = "13574601";
    int IDcliente1;

    cout << "\n------------- ATIVIDADE 5 -------------" << endl;

    if(listacompras->MapaCliente.find(Cliente1) == listacompras->MapaCliente.end()){
        cout << "Cliente " << Cliente1 << " não encontrado" << endl;
    } else {
        IDcliente1 = listacompras->MapaCliente[Cliente1];

        cout << "\n--- RECOMENDAÇÕES CLIENTE " << Cliente1 << " (ID: " << IDcliente1 << ") ---" << endl;
        recomendacaoCSR(listacompras, IDcliente1);
    }
}