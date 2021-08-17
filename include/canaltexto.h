#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include "mensagem.h"

using namespace std;

class CanalTexto	{
	private:
		string nome;
		vector<Mensagem> mensagens;  
	
	public:
		CanalTexto();

		CanalTexto(string nome, vector<Mensagem> mensagens);

		string getNome();

    	void setNome(string nome);

		vector<Mensagem> getMensagens();

		void sendMensagem(string nome, Mensagem mensagem);

		~CanalTexto();
};

#endif
