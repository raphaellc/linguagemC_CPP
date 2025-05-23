#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <iostream>

class Pessoa {
protected:
    std::string nome;
    int idade;
    bool viva;

public:
    int atr_publico;

    // Construtores
    Pessoa();
    Pessoa(std::string nome, int idade);
    Pessoa(std::string nome, int idade, bool viva);

    // Métodos de acesso (getters)
    std::string getNome() const;
    int getIdade() const;
    bool isViva() const;

    // Métodos de modificação (setters)
    void setNome(std::string _nome);
    void setIdade(int _idade);
    void setViva(bool _viva);
};

#endif // PESSOA_H