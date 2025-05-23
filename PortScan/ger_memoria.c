#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

int main(){
    char vetor[10] = "teste";
    
    printf("%s", vetor+3*sizeof(char));

    char * caracteres = NULL;

    caracteres = (char *)calloc(10, sizeof(char));
    size_t tamanho_real = _msize(caracteres);
    printf("\n Tamanho de caracteres %d", tamanho_real);
    
    int *numeros= NULL;
    numeros = (int *)malloc(10*sizeof(int));
    
    for (int i = 0; i < 10; i++){ 
        numeros[i] = rand() % 100;
        printf(" \n vetor de inteiros %d",numeros[i]);
    }
    
    caracteres = realloc(caracteres, 5*sizeof(char));
    tamanho_real = _msize(caracteres);
    caracteres[0] = 'a';
    caracteres[1] = 'b';
    caracteres[2] = 'c';
    printf("\n numero de caracteres %d", strlen(caracteres));
    printf("\n Tamanho de caracteres %d", tamanho_real);
    free(caracteres);
    free(numeros);
    caracteres = NULL;
    numeros = NULL;
    
    return 0;
}