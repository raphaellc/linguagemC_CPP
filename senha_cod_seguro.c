#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Tamanho máximo da senha
#define TAMANHO_MAX_SENHA 10

//protótipos das funções

int verificar_forca_senha(char *senha);
void ler_string_segura(char *str, int tamanho);


// Função para verificar a força da senha
int verificar_forca_senha(char *senha) {
    int comprimento = strlen(senha);
    int tem_maiuscula = 0, tem_minuscula = 0, tem_numero = 0, tem_especial = 0;
    int forca = 0;
    int i;

    // Verifica o comprimento
    if (comprimento < 8) {
        return 1; // Fraca
    }

    // Verifica a presença de diferentes tipos de caracteres
    for (i = 0; i < comprimento; i++) {
        if (isupper((unsigned char) senha[i])) {
            tem_maiuscula = 1;
        } else if (islower((unsigned char)senha[i])) {
            tem_minuscula = 1;
        } else if (isdigit((unsigned char) senha[i])) {
            tem_numero = 1;
        } else if (ispunct((unsigned char) senha[i])) {
            tem_especial = 1;    
        }
    }
    
    // Determina a força da senha
    if (tem_maiuscula && tem_minuscula && tem_numero && tem_especial) {
        return 4; // Forte
    } else if ((tem_maiuscula || tem_minuscula) && tem_numero && tem_especial) {
        return 3; // Média
    } else {
        return 2; // Fraca
    }
}

// Função para ler uma string de forma segura
void ler_string_segura(char *str, int tamanho) {
    if (fgets(str, tamanho, stdin) == NULL) {
        // Tratamento de erro: falha na leitura
        printf("Erro ao ler a entrada.\n");
        exit(EXIT_FAILURE);
    }

    // Remove a nova linha (\n) se presente
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    } else {
        // Limpa o buffer de entrada se a entrada for maior que o buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int main() {
    char senha[TAMANHO_MAX_SENHA + 1];

    printf("Digite a senha: ");
    ler_string_segura(senha, sizeof(senha));
    printf("\n %s \n", senha);
    // Verifica se a senha está vazia
    if (strlen(senha) == 0) {
        printf("Erro: A senha não pode ser vazia.\n");
        return EXIT_FAILURE;
    }

    // Verifica se a senha excede o tamanho máximo permitido
    if (strlen(senha) >= sizeof(senha)) {
        printf("Erro: A senha excede o tamanho máximo permitido.\n");
        return EXIT_FAILURE;
    }

    int forca = verificar_forca_senha(senha);

    switch (forca) {
        case 1:
            printf("Senha muito fraca!\n");
            break;
        case 2:
            printf("Senha fraca!\n");
            break;
        case 3:
            printf("Senha média.\n");
            break;
        case 4:
            printf("Senha forte!\n");
            break;
        default:
            printf("Erro: Força da senha desconhecida.\n");
            break;
    }

    return 0;
}