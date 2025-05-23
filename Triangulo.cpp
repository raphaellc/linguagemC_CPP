// Triangulo.cpp
#include "Triangulo.h"
#include <iostream>

// Implementação do construtor
Triangulo::Triangulo(float b, float h){
    this->base = b;
    this->altura = h;
    std::cout << "Triângulo com base " << b << " e altura " << h << " criado." << std::endl;
}

// Implementação da função para calcular a área do triângulo
float Triangulo::calcularArea() {
    return (base * altura) / 2.0;
}

// Implementação da função para "desenhar" o triângulo
void Triangulo::desenhar() const {
    std::cout << "Desenhando um Triângulo com base " << base
              << " e altura " << altura << std::endl;
}