#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para gerar um caractere aleatório de um conjunto
char gerar_caractere_aleatorio(char *conjunto) {
    int tamanho_conjunto = strlen(conjunto);
    int indice_aleatorio = rand() % tamanho_conjunto;
    return conjunto[indice_aleatorio];
}

// Função para gerar uma senha aleatória
void gerar_senha(char *senha, int comprimento) {
    char minusculas= "abcdefghijklmnopqrstuvwxyz";
    char maiusculas= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char numeros= "0123456789";
    char especiais= "!@#$%^&*()_-+={}|;:'\",<.>/?";

    // Garante pelo menos um caractere de cada tipo
    senha[0] = gerar_caractere_aleatorio(minusculas);
    senha[1] = gerar_caractere_aleatorio(maiusculas);
    senha[2] = gerar_caractere_aleatorio(numeros);
    senha[3] = gerar_caractere_aleatorio(especiais);

    // Gera os caracteres restantes aleatoriamente
    for (int i = 4; i < comprimento; i++) {
        int tipo_caractere = rand() % 4;
        switch (tipo_caractere) {
            case 0:
                senha[i] = gerar_caractere_aleatorio(minusculas);
                break;
            case 1:
                senha[i] = gerar_caractere_aleatorio(maiusculas);
                break;
            case 2:
                senha[i] = gerar_caractere_aleatorio(numeros);
                break;
            case 3:
                senha[i] = gerar_caractere_aleatorio(especiais);
                break;
        }
    }

    senha[comprimento] = '\0'; // Adiciona o caractere nulo ao final
}

int main() {
    char senha[100];
    int comprimento;

    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL));

    printf("Digite o comprimento da senha desejada: ");
    scanf("%d", &comprimento);

    gerar_senha(senha, comprimento);
    printf("Senha gerada: %s\n", senha);

    return 0;
}