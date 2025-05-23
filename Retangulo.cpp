#include "Retangulo.h"
#include <iostream>
using namespace std;

Retangulo::Retangulo(){
    this->base = 0.0f;
    this->altura = 0.0f;
}
Retangulo::~Retangulo(){}
void Retangulo::desenha(){
    cout << "Base = " << this->base << endl;
    cout << "Altura = " << this->altura << endl;
}
float Retangulo::calcularArea(){
    return this->base * this->altura;
}
