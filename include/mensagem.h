#ifndef MENSAGEM_H
#define MENSAGEM_H

class Mensagem  {
	private:
		std::string dataHora;
        int enviadaPor;
        std::string conteudo;
    
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