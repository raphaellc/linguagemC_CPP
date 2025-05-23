#ifndef USUARIO_H
#define USUARIO_H

#include "Pessoa.h"
class Usuario : public Pessoa{
    private:
        std::string login;
        std::string senha;
    public:
        Usuario(std::string nome, int idade, std::string login, std::string senha);
        void setLogin(std::string _login);
        void setSenha(std::string _senha);
        std::string getLogin();
        std::string getSenha();
};
#endif // USUARIO_H