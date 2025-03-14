#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/rand.h>

#define NUM_PALAVRAS 6  // Número de palavras na senha
#define DICEWARE_LIST_SIZE 10  // Tamanho da lista de palavras (substitua por uma maior se quiser)

// Lista de palavras para Diceware (pode ser expandida ou carregada de um arquivo)
const char *diceware_list[DICEWARE_LIST_SIZE] = {
    "gato", "vento", "rio", "montanha", "fogo",
    "neve", "tempo", "cavalo", "lua", "estrela"
};

// Gera um número aleatório seguro dentro de um intervalo
int numero_aleatorio_seguro(int max) {
    unsigned char buffer[4];
    unsigned int num;

    if (RAND_bytes(buffer, sizeof(buffer)) != 1) {
        printf("Erro ao gerar número aleatório seguro.\n");
        exit(EXIT_FAILURE);
    }

    num = (buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24)) % max;
    return num;
}

// Gera uma senha usando Diceware
void gerar_senha_diceware(char *senha_final, int tamanho_max) {
    senha_final[0] = '\0';  // Inicializa a string vazia

    for (int i = 0; i < NUM_PALAVRAS; i++) {
        int indice = numero_aleatorio_seguro(DICEWARE_LIST_SIZE);

        // Adiciona a palavra à senha
        strcat(senha_final, diceware_list[indice]);

        // Adiciona um separador aleatório, exceto na última palavra
        if (i < NUM_PALAVRAS - 1) {
            char separador[2] = { "!@#$%^&*-"[numero_aleatorio_seguro(8)], '\0' };
            strcat(senha_final, separador);
        }
    }
}

int main() {
    char senha[100];  // Buffer para armazenar a senha

    // Inicializa OpenSSL RAND
    if (RAND_status() != 1) {
        printf("Erro: OpenSSL RNG não está inicializado corretamente.\n");
        return 1;
    }

    // Gera a senha Diceware
    gerar_senha_diceware(senha, sizeof(senha));

    // Exibe a senha gerada
    printf("Senha Diceware gerada: %s\n", senha);

    return 0;
}
