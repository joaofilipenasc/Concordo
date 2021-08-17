#ifndef USUARIO_H
#define USUARIO_H

using namespace std;

class Usuario	{
	private:
		int id;
		string nome;
		string email;
		string senha;

	public:
		Usuario();

		Usuario(int id, string nome, string email, string senha);

		int getId();

		void setId(int id);

		string getNome();

		void setNome(string nome);

		string getEmail();

		void setEmail(string email);

		string getSenha();

		void setSenha(string senha);

		~Usuario();
};

#endif
