#include "Usuario.h"

Usuario::Usuario(std::string nome, int idade, std::string login, std::string senha) : Pessoa(nome, idade){
    this->login = login;
    this->senha = senha;
}
void Usuario::setLogin(std::string _login){
    this->login = _login;
}
void Usuario::setSenha(std::string _senha){
    this->senha = _senha;
}
std::string Usuario::getLogin(){
    return this->login;
}
std::string Usuario::getSenha(){
    return this->senha;
}