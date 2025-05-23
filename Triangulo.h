// Triangulo.h
#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "Forma.h" // Inclui a classe base

class Triangulo : public Forma {
private:
    float base;
    float altura;

public:
    // Construtor para inicializar a base e a altura do triângulo
    Triangulo(float b, float h);

    // Sobrescreve a função virtual pura da classe base para calcular a área
    float calcularArea() override;

    // Sobrescreve a função virtual comum da classe base para desenhar
    void desenhar() const;
};

#endif // TRIANGULO_H