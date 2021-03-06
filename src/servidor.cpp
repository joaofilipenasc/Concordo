#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "../include/servidor.h"
#include "../include/canaltexto.h"
#include "../include/mensagem.h"

using namespace std;

Servidor::Servidor() {}

Servidor::Servidor(int usuarioDonoId, string nome) {
    this -> usuarioDonoId = usuarioDonoId;
    this -> nome = nome;
}

int Servidor::getUsuarioDonoId() {
  return usuarioDonoId;
}

void Servidor::setUsuarioDonoId(int usuarioDonoId) {
  this -> usuarioDonoId = usuarioDonoId;
}

string Servidor::getNome() {
  return nome;
}

void Servidor::setNome(string nome) {
  this -> nome = nome;
}

string Servidor::getDescricao() {
  return descricao;
}

void Servidor::setDescricao(string descricao) {
  this -> descricao = descricao;
}

string Servidor::getCodigoConvite() {
  return codigoConvite;
}

void Servidor::setCodigoConvite(string codigoConvite) {
  this -> codigoConvite = codigoConvite;
}

vector<int> Servidor::getParticipantesIDs(){
  return participantesIDs;
}

vector<string> Servidor::getCanaisTexto() {
  vector<string> listaCanaisTexto;
  return listaCanaisTexto;
}

bool Servidor::createCanal(shared_ptr<CanalTexto> canal) {
  if(canal != nullptr){
    canais.push_back(*canal);
    return true;
  } 
  else  {
    return false;
  }
}

bool Servidor::pushParticipante(int participanteID) {
  for (long unsigned int i = 0; i < participantesIDs.size(); i++) {
    if (participantesIDs[i] == participanteID) {
      return false;
    }
  }
  participantesIDs.push_back(participanteID);
  return true;
}

/*
vector<Mensagem> Servidor::getMensagens(string nomeCanal) {  
  

}

void Servidor::sendMensagem(string nomeCanal, Mensagem mensagem) {

  
}
*/

Servidor::~Servidor() {}
