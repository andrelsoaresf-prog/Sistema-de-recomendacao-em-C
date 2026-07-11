#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[50];
    int idade;
    char cidade[50]; 
} Pessoa;


int main(){
    FILE *arquivo;
    Pessoa pessoa;
    char cabeçalho[100];

    arquivo = fopen("dados_teste.csv", "r");
    if (arquivo == NULL){
        printf("deu ruim");
        return 1;
    }

    fgets(cabeçalho, sizeof(cabeçalho), arquivo);

    while (fscanf(arquivo, "%49[^,], %d, %49[^\n]\n",
        pessoa.nome, 
        &pessoa.idade, 
        pessoa.cidade) == 3)
    {
        printf("Nome: %-10s | idade: %d | cidade: %s\n", 
            pessoa.nome, pessoa.idade, pessoa.cidade);
    }

    fclose(arquivo);
    
    return 0;
}