#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *gerar_senha(int tamanho) {
    const char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
    char *senha = malloc(tamanho + 1);

    if (senha == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        return NULL;
    }

    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    for (int i = 0; i < tamanho; i++) {
        senha[i] = caracteres[rand() % (sizeof(caracteres) - 1)];
    }

    senha[tamanho] = '\0'; // Adiciona o terminador de string
    return senha;
}

int main() {
    int tamanho = 12;
    char *senha = gerar_senha(tamanho);

    if (senha != NULL) {
        printf("Senha gerada: %s\n", senha);
        free(senha); // Libera a memória alocada
    }

    return 0;
}