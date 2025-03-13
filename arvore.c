#include <stdio.h>

#define MAX_NOS 100
typedef struct No
{
    int dado;
    int esq;
    int dir;

    /* data */
} No;

No arvore[MAX_NOS];
int raiz = -1; // inicialmente está vazia, por isso -1
int proximoIndice = 0; //índice do próximo nó disponível

void inserir(int dado)
{
    if (raiz == -1)
    {
        raiz = proximoIndice;
        arvore[raiz].dado = dado;
        arvore[raiz].esq = -1;
        arvore[raiz].dir = -1;
        proximoIndice++;
        return;
    }else{
        int atual = raiz;
        while(1){
            if(dado < arvore[atual].dado){
                atual = 
                if(arvore[atual].esq == -1){
                    arvore[atual].esq = proximoIndice;
                    arvore[proximoIndice]
                }
            }
        }
    }

    if (proximoIndice >= MAX_NOS)
    {
        printf("Árvore cheia!\n");
        return;
    }
     

