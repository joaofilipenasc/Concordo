#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <vector>
#include <memory>

#include "canaltexto.h"

using namespace std;

class Servidor	{
	private:
		int usuarioDonoId;
		string nome;
		string descricao;
		string codigoConvite;
		vector<CanalTexto> canais;
		vector<int> participantesIDs;
	
	public:
		Servidor();

		Servidor(int usuarioDonoId, string nome);

		int getUsuarioDonoId();

		void setUsuarioDonoId(int usuarioDonoId);

		string getNome();

		void setNome(string nome);

		string getDescricao();

		void setDescricao(string descricao);

		string getCodigoConvite();

    	void setCodigoConvite(string codigoConvite);

		vector<int> getParticipantesIDs();

		vector<string> getCanaisTexto();

		bool createCanal(shared_ptr<CanalTexto> canal);

		bool pushParticipante(int participanteID);

		vector<Mensagem> getMensagens(string nome);

		void sendMensagem(string nome, Mensagem mensagem);

		~Servidor();

};

#endif
