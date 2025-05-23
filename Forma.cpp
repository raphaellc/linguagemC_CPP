#include "Forma.h"
Forma::Forma() {
    this->base = 0;
    this->altura = 0;
}
Forma::Forma(float base, float altura) {
    this->base = base;
    this->altura = altura;
}

void Forma::setAltura(float altura) {
    this->altura = altura;
}

void Forma::setBase(float base) {
    this->base = base;
}

float Forma::getAltura() {
    return this->altura;
}

float Forma::getBase() {
    return this->base;
}
float Forma::calcularArea(){
    return this->base * this->altura;

}



