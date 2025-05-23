#include <iostream>
#include "Pessoa.h"
#include "Usuario.h"
#include <string>
using namespace std;

class OlaMundo {
    private:
        string nome;
        Pessoa * pess = nullptr;
        void comQuemEuFalo(Pessoa * _pessoa){
            this->nome = _pessoa->getNome();
            
        }
    public:
        //construtor
        OlaMundo(){
            pess = new Pessoa("Bruno", 42, true);
            Pessoa p; 
            p.setNome("Raphael");
            p.setIdade(42);
            comQuemEuFalo(pess);
            cout << "Olá mundo" << this->nome << endl;    
        }
        OlaMundo(Pessoa * pessoa){
            this->pess = pessoa;
            comQuemEuFalo(pessoa);
            cout << "Olá mundo" << this->nome << endl;    
        }
        //destrutor
        ~OlaMundo(){
            delete this->pess;
            cout << "Fim do programa" << endl;
        }
};

int main(){
    Pessoa * p1 = new Pessoa("Lapis",23);
    p1->setViva(true);
    Pessoa p;
    p.setNome("Raphael");
    p.setIdade(42);
    OlaMundo * om = new OlaMundo(&p);
    Usuario * pessoa_usuario = new Usuario("Raphael", 42, "rrr","12345");
    
    OlaMundo * om1 = new OlaMundo();
    p1->setNome("Arthur");
    p1->setIdade(20);
    OlaMundo* om2 = new OlaMundo(p1);

    
    delete om;
    delete om1;
    delete om2;
    delete p1;
    return 0;
}