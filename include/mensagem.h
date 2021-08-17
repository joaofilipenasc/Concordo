#ifndef MENSAGEM_H
#define MENSAGEM_H

using namespace std;

class Mensagem  {
	private:
		string dataHora;
        int enviadaPor;
        string conteudo;
    
    public:
        Mensagem();

        Mensagem(string dataHora, int enviadaPor, string conteudo);

        string getDataHora();

        void setDataHora(string dataHora);

        int getEnviadaPor();

        void setEnviadaPor(int enviadaPor);      
        
        string getConteudo();

        void setConteudo(string conteudo);

        ~Mensagem();

};

#endif