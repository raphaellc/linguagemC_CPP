#ifndef RETANGULO_H
#define RETANGULO_H
#include "Forma.h"
class Retangulo: public Forma {
    public:
        Retangulo();
        ~Retangulo();
        void desenha();
        float calcularArea() override;
};
#endif