#include <string>
#include "usuario.h"

using namespace std;

Usuario::Usuario() {}

Usuario::Usuario(int id, string email, string senha, string nome) {
    this -> id = id;
    this -> email = email;
    this -> senha = senha;
    this -> nome = nome;
}

int Usuario::getId() {
    return id;
}

void Usuario::setId(int id) {
    this -> id = id;
}

string Usuario::getNome() {
    return nome;
}

void Usuario::setNome(string nome) {
    this -> nome = nome;
}

string Usuario::getEmail() {
    return email;
}

void Usuario::setEmail(string email) {
    this -> email = email;
}

string Usuario::getSenha() {
    return senha;
}

void Usuario::setSenha(string senha) {
    this -> senha = senha;
}

Usuario::~Usuario(){}