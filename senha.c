#include <stdio.h>
#include <ctype.h>
#include <string.h>

//protótipo da função
//[tipo de retorno] [identificador]([parâmetros]){código da função return [valor]}
//void - sem retorno - não tipo
int verificar_forca_senha(char *senha);

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
        if (isupper(senha[i])) {
            tem_maiuscula = 1;
        } else if (islower(senha[i])) {
            tem_minuscula = 1;
        } else if (isdigit(senha[i])) {
            tem_numero = 1;
        } else if (ispunct(senha[i])) {
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


int main() {
    char senha[100];
    
    
    printf("Digite a senha: ");
    scanf(" %[^\n]", senha);
    

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
    }

    return 0;
}