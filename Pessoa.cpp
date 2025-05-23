#include "Pessoa.h"
// Construtor padrão
Pessoa::Pessoa() : nome(""), idade(0), viva(true) {}

// Construtor com nome e idade
Pessoa::Pessoa(std::string nome, int idade) : nome(nome), idade(idade), viva(true) {}

// Construtor com nome, idade e estado de vida
Pessoa::Pessoa(std::string nome, int idade, bool viva) : nome(nome), idade(idade), viva(viva) {}

// Getter para o nome
std::string Pessoa::getNome() const {
    return this->nome;
}

// Getter para a idade
int Pessoa::getIdade() const {
    return this->idade;
}

// Getter para o estado de vida
bool Pessoa::isViva() const {
    return this->viva;
}

// Setter para o nome
void Pessoa::setNome(std::string _nome) {
    if (_nome == "") {
        std::cout << "Nome não pode ser vazio" << std::endl;
    } else {
        this->nome = _nome;
        std::cout << this->nome << std::endl;
    }
}

// Setter para a idade
void Pessoa::setIdade(int _idade) {
    this->idade = _idade;
    std::cout << this->idade << std::endl;
}

// Setter para o estado de vida
void Pessoa::setViva(bool _viva) {
    this->viva = _viva;
}