#include <stdio.h>
#include <string.h>


int main(){
    char nome[100] = "Raphael";
    int idade;

    scanf("%s %d", &nome, &idade);
    printf("Salve! %s %s com idade = %d anos \n", "Olá Mundo!", nome, idade);
    if (idade < 0 || idade > 150)
        printf("idade inválida \n");
    else if(idade >= 18)
        printf("%s É maior de idade \n ", nome);    
    else
        printf("%s É menor de idade \n ", nome);
    
    for(int i = 0; i < strlen(nome); i++){
        printf("%c \n", nome[i]);   
    }
        
    return 0;
}


