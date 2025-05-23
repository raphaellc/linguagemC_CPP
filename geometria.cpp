#include <iostream>
#include "Forma.h"
#include "Retangulo.h"

using namespace std;

int main() {
    Forma * forma = new Forma(10.0, 5.0);
    Retangulo * retangulo = new Retangulo();
    Forma * forma2 = new Retangulo();
    forma2->setAltura(6.0);
    forma2->setBase(8.0);
    cout << "Área da Forma: " << endl;
    cout << forma->calcularArea() << endl;
    retangulo->setAltura(2.0);
    retangulo->setBase(4.0);    
    cout << "Área do Retângulo: " << endl;
    cout << retangulo->calcularArea() << endl;

    cout << "😊 do Retângulo: " << endl;
    cout << forma2->calcularArea() << endl;

        
    return 0;
}