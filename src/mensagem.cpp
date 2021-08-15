#include <string>
#include <vector>

#include "mensagem.h"

using namespace std;

Mensagem::Mensagem() {}

Mensagem::Mensagem(string dataHora, int enviadaPor, string conteudo) {
    this -> dataHora = dataHora;
    this -> enviadaPor = enviadaPor;
    this -> conteudo = conteudo;
}

string Mensagem::getDataHora() {
  return dataHora;
}

void Mensagem::setDataHora(string dataHora) {
    this -> dataHora = dataHora;
}

int Mensagem::getEnviadaPor() {
    return enviadaPor;
}

void Mensagem::setEnviadaPor(int enviadaPor) {
    this -> enviadaPor = enviadaPor;
}

string Mensagem::getConteudo() {
    return conteudo;
}

void Mensagem::setConteudo(string conteudo) {
    this -> conteudo = conteudo;
}

Mensagem::~Mensagem() {}
