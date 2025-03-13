#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Estrutura de um nó da árvore
typedef struct Node {
    int data;
    int left;
    int right;
} Node;

// Árvore binária implementada com vetor
Node tree[MAX_NODES];
int root = -1; // Inicialmente, a árvore está vazia
int nextIndex = 0; // Índice do próximo nó disponível

// Função para inserir um nó na árvore
void insertNode(int data) {
    if (nextIndex >= MAX_NODES) {
        printf("Árvore cheia!\n");
        return;
    }

    // Cria um novo nó
    Node newNode;
    newNode.data = data;
    newNode.left = -1;
    newNode.right = -1;

    // Se a árvore estiver vazia, o novo nó será a raiz
    if (root == -1) {
        root = nextIndex;
    } else {
        int current = root;
        int parent;
        while (1) {
            parent = current;
            if (data < tree[current].data) {
                current = tree[current].left;
                if (current == -1) {
                    tree[parent].left = nextIndex;
                    break;
                }
            } else {
                current = tree[current].right;
                if (current == -1) {
                    tree[parent].right = nextIndex;
                    break;
                }
            }
        }
    }

    tree[nextIndex] = newNode;
    nextIndex++;
}

// Função para imprimir a árvore em ordem (inorder traversal)
void printInOrder(int current) {
    if (current != -1) {
        printInOrder(tree[current].left);
        printf("%d ", tree[current].data);
        printInOrder(tree[current].right);
    }
}

int main() {
    // Insere alguns nós na árvore
    insertNode(50);
    insertNode(30);
    insertNode(20);
    insertNode(40);
    insertNode(70);
    insertNode(60);
    insertNode(80);

    // Imprime a árvore em ordem
    printf("Árvore em ordem: ");
    printInOrder(root);
    printf("\n");

    return 0;
}