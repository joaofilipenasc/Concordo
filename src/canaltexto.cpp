#include <string>
#include <vector>

#include "canaltexto.h"
#include "mensagem.h"

using namespace std;

CanalTexto::CanalTexto() {}

CanalTexto::CanalTexto(string nome, vector<Mensagem> mensagens) {}

string CanalTexto::getNome() {
    return nome;
}

void CanalTexto::setNome(string nome) {
    this -> nome = nome;
}

vector<Mensagem> CanalTexto::getMensagens() {
    return mensagens;
}

void CanalTexto::sendMensagem(string nome, Mensagem mensagem) {
    mensagens.push_back(mensagem);
}

CanalTexto::~CanalTexto() {}

