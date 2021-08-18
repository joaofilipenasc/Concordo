#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <utility>
#include <time.h>

#include "../include/sistema.h"
#include "../include/usuario.h"
#include "../include/servidor.h"

using namespace std;

Sistema::Sistema() {

//Um map vazio
map< int , pair<string, string> > usuariosLogados; 

}

Sistema::~Sistema() {}

string Sistema::quit() {
  return "Saindo...";
}

//FUNCIONALIDADES 1

//Cria um novo usuário
string Sistema::create_user(const string email, const string senha, const string nome) {
  
  //Verificar se os campos solicitados estão vazios
  if(email.empty() && senha.empty() && nome.empty()) {
    return "Os campos não podem ser vazios.";
  }

  //Verificar se o usuário já está cadastrado no sistema
  for(long unsigned int i = 0; i < usuarios.size(); i++) {
    if (usuarios[i].getEmail() == email) {
      return "Usuário já existe.";
    }
  }

  //Criar um novo objeto da classe Usuário e seta as devidas atribuições
  Usuario novoUsuario;
  novoUsuario.setId(usuarios.size() + 1);
  novoUsuario.setNome(nome);
  novoUsuario.setEmail(email);
  novoUsuario.setSenha(senha);

  //Adicionar o usuário recém-criado à lista de usuários do sistema
  usuarios.push_back(novoUsuario);

  return "Usuário criado!";
  
}

//Entrar no sistema com e-mail e senha
string Sistema::login(const string email, const string senha) {
  
  //Verificar se o usuário está cadastrado no sistema a partir de um iterador
  vector<Usuario>::iterator itUsuario = usuarios.begin();
  while(itUsuario != usuarios.end()) {
    if(itUsuario -> getEmail() == email) {
      if(itUsuario -> getSenha() == senha) {
        usuarioLogadoID = itUsuario -> getId();
        return "Logado como " + email;
      }
    }
    itUsuario++;
  }
  return "Email ou senha incorretos. Tente novamente!";

}

//Desconecta o usuário
string Sistema::disconnect(int id) {
  
  //Verificar se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  //Utiliza a variável temporária idLogadoAnterior para atualizar o valor do id do usuário para 0 e desconectá-lo do sistema
  int idLogadoAnterior = id;
  id = 0;

  return "Desconectando usuário " + usuarios[idLogadoAnterior - 1].getEmail() + ".";

}

//Cria um servidor
string Sistema::create_server(int id, const string nome) {
  
  //Verificar se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  //Verificar se o usuário forneceu um nome com caracteres para o servidor
  if(nome.empty()) {
    return "Não é possível criar um servidor sem nome.";
  }

  //Verificar se o servidor já está cadastrado no sistema
  for(long unsigned int i = 0; i < servidores.size(); i++) {
    if(servidores[i].getNome() == nome) {
      return "Servidor com esse nome já existe.";
    }
  }

  //Cria um novo objeto da classe Servidor e seta as devidas atribuições
  Servidor novoServidor(id, nome);
  servidores.push_back(novoServidor);

  return "Servidor criado.";
  
}

//Modifica a descrição de um servidor
string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  
  //Verificar se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  //Inicialização do iterador que será usado para percorrer as listas de servidores do sistema
  vector<Servidor>::iterator itServidor;

  //Verificar se existe servidor com o nome fornecido pelo usuário
  itServidor = find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor) {
    return nome == servidor.getNome();
  });
  if(itServidor == servidores.end()) {
    return "Servidor '" + nome + "' não existe.";
  }

  //Verificar se o usuário é o dono do servidor
  if(itServidor -> getUsuarioDonoId() != id) {
    return "Você não pode alterar a descrição de um servidor que não foi criado por você.";
  }

  //Muda a descrição do servidor
  itServidor -> setDescricao(descricao);
  return "Descrição do servidor '" + nome + "' modificada com sucesso.";
  
}

//Altera o código de convite de um servidor
string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  
  //Verifica se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  //Inicialização do iterador que será usado para percorrer as listas de servidores do sistema
  vector<Servidor>::iterator itServidor;

  //Verificar se existe servidor com o nome
  itServidor = find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor) {
    return nome == servidor.getNome();
  });
  if(itServidor == servidores.end()) {
    return "Servidor '" + nome + "' não existe.";
  }

  //Verificar se o usuário é o dono do servidor
  if(itServidor -> getUsuarioDonoId() != id) {
    return "Você não pode alterar a descrição de um servidor que não foi criado por você.";
  }
  
  //Verificar se o cógido tem tamanho maior do que 0
  if(codigo.length() > 0) {
    itServidor -> setCodigoConvite(codigo);
    return "Código de convite do servidor '" + nome +"' modificado!";
  }

  //Se o usuário não fornecer código de string vazia, o código é removido
  itServidor -> setCodigoConvite("");
  return "Código de convite do servidor '" + nome +"' removido!";

}

//Lista todos os servidores
string Sistema::list_servers(int id) {
  
  //Verifica se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  //Verifica se a lista de servidores está vazia
  if(servidores.empty()) {
    return "Não há servidores cadastrados.";
  }

  //Inicializa uma string vazia que será preenchida pelo nome de cada servidor armazenado em servidores
  string listaServidores = "";
  for(long unsigned int i = 0; i < servidores.size(); i++) {
    listaServidores += servidores[i].getNome() + "\n";
  }

  return listaServidores;

}

//Deleta um servidor
string Sistema::remove_server(int id, const string nome) {
  
  //Verifica se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  //Verificar se existe servidor com o nome
  vector<Servidor>::iterator itServidor;
  itServidor = find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor) {
    return nome == servidor.getNome();
  });
  if(itServidor == servidores.end()) {
    return "Servidor '" + nome + "' não existe.";
  }

  //Verifica se o usuário é o dono do servidor
  if(itServidor -> getUsuarioDonoId() != id) {
    return "Você não pode alterar a descrição de um servidor que não foi criado por você.";
  }

  servidores.erase(itServidor);

  return "Servidor '" + nome + "' removido";

}

//Entrar em um servidor
string Sistema::enter_server(int id, string nome, string codigo) {
  
  //Verificar se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  //Verificar se existe servidor com o nome
  vector<Servidor>::iterator itServidor;
  itServidor = find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor) {
    return nome == servidor.getNome();
  });
  if(itServidor == servidores.end()) {
    return "Servidor '" + nome + "' não existe.";
  }

  //Armazenar o nome do servidor no primeiro par, que representa o servidor do par servidor-canal
  servidorCanal = make_pair(nome,"");
  itServidor -> pushParticipante(id);

  return "Entrou no servidor com sucesso";

}

//Sair de um servidor
string Sistema::leave_server(int id, const string nome) {
  
  //Verificar se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  //Verificar se existe servidor com o nome
  if(nome.length() == 0) {
    return "O usuário não está conectado a nenhum servidor.";
  }

  string temp = nome;
  servidorCanal.first = "";

  return "O usuário está saindo do servidor \'" + temp + "\'.";

}

//Listar os participantes de um servidor
string Sistema::list_participants(int id) {
  
  //Verificar se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }
  
  //Verificar se existe um servidor conectado
  if(servidorCanal.first.empty()) {
    return "Não existe servidor conectado.";
  }

  //Procurar o servidor pelo nome
  Servidor encontraServidor;
  for (long unsigned int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == servidorCanal.first) {
      encontraServidor = servidores[i];
    };
  }

  string listaParticipantes = "";

  //Exibir todos os usuários que estão no servidor como uma lista somente com o nome de cada um
  vector<int> listaIDs = encontraServidor.getParticipantesIDs();
  for(long unsigned int i = 0; i < usuarios.size(); i++) {
    listaParticipantes += usuarios[i].getNome() + "\n";
  }

  return listaParticipantes;

}

//FUNCIONALIDADES 2

//Listar os canais do servidor
string Sistema::list_channels(int id) {
  
  //Verificar se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  //Verificar se o usuário está logado em algum servidor
  if(servidorCanal.first.length() == 0) {
    return "O usuário não está conectado a um servidor no momento.";
  }

  //Encontrar o servidor pelo nome
  string nomeServidor = servidorCanal.first;

  auto itServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return nomeServidor == servidor.getNome();
  });

  vector<string> canaisTexto = itServidor -> getCanaisTexto();

  //Verificar se os canais estão vazios
  if(canaisTexto.empty()) {
    return "Nenhum canal no servidor foi encontrado.";
  }

  //Variável de retorno para concatenar os canais
  string canais;

  if(!canaisTexto.empty()) {
    canais += "#canais de texto\n";

    for(auto itCanal = canaisTexto.begin(); itCanal != canaisTexto.end(); itCanal++) {
      if(itCanal != canaisTexto.end()) {
        canais += *itCanal + "\n";
      }
    }
  }

  return canais;

}

//Criar um canal do servidor
string Sistema::create_channel(int id, const string nome) {

  //Verificar se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  //Verificar se o usuário está logado em algum servidor
  if(servidorCanal.first.length() == 0) {
    return "O usuário não está conectado a um servidor no momento.";
  }

  //Verificar se o canal é uma string não vazia
  if(nome.length() == 0) {
    return "O canal precisa ter um nome";
  }

  //Encontrar o servidor pelo nome
  string nomeServidor = servidorCanal.first;

  auto itServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });

  //Inicializar um vetor de string que armazena a variável que vai pegar todos os canais de texto
  vector<string> canaisTexto = itServidor -> getCanaisTexto();

  //Verificar se o canal já existe pelo nome
  auto itCanal = find_if(canaisTexto.begin(), canaisTexto.end(), [nome](string nomeCanal) {
    return nomeCanal == nome;
  });
  if(itCanal != canaisTexto.end()) {
    return "Canal de texto \'" + nome + "\' já existe.";
  }

  //Após todas as verificações anteriores, criar um objeto da classe CanalTexto que represente o novo canal recém-criado
  vector<Mensagem> mensagens;
  shared_ptr<CanalTexto> novoCanal(new CanalTexto(nome, mensagens));

  bool canalCriado = itServidor -> createCanal(novoCanal);

  if(canalCriado) {
    return "Canal de texto \'" + nome + "\' criado.";
  }

  return "Erro ao criar canal de texto.";
  
}

//Entrar em um canal
string Sistema::enter_channel(int id, string nome) {
  
  //Verificar se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  //Verificar se o usuário está logado em algum servidor
  if(servidorCanal.first.length() == 0) {
    return "O usuário não está conectado a um servidor no momento.";
  }

  //Verificar se o canal é uma string não vazia
  if(nome.length() == 0) {
    return "O canal precisa ter um nome para entrar";
  }

  string nomeServidor = servidorCanal.first;

  auto itServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });

  vector<string> findCanaisTexto = itServidor -> getCanaisTexto();
  auto itCanalTexto = find_if(findCanaisTexto.begin(), findCanaisTexto.end(), [nome](std::string nomeCanal) {
    return nomeCanal == nome;
  });

  if(itCanalTexto != findCanaisTexto.end()) {
    servidorCanal.second = nome;
    return "Entrou no canal \'" + nome + "\'.";
  } 
  else {
    servidorCanal.second = nome;

    return "Entrou no canal \'" + nome + "\'.";
  }

}

//Sair de um canal
string Sistema::leave_channel(int id) {
  
  //Verificar se o usuário está cadastrado no sistema com o seu id
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  //Verificar se o usuário está logado em algum servidor
  if(servidorCanal.first.length() == 0) {
    return "O usuário não está conectado a um servidor no momento.";
  }

  //Verificar se o canal é uma string não vazia
  if(servidorCanal.second.length() == 0) {
    return "O usuário não está conectado a um canal no momento.";
  }

  string temp = servidorCanal.second;
  servidorCanal.second = "";

  return "O usuário está saindo do canal \'" + temp + "\'.";

}

//Enviar uma mensagem para o canal
string Sistema::send_message(int id, const string mensagem) {
  /*
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  if(servidorCanal.first.length() == 0) {
    return "O usuário não está conectado a um servidor no momento.";
  }

  if(servidorCanal.second.length() == 0) {
    return "O usuário não está conectado a um canal no momento.";
  }

  if(mensagem.empty()) {
    return "A mensagem está vazia.";
  }

  string nomeServidor = servidorCanal.first;

  auto itServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });

  //Faz a captura e o armazenamento da hora atual
  char dataHora[100];
  time_t atual = time(nullptr);

  strftime(dataHora, 50, "%d/%m/%Y - %R", localtime(&atual));

  Mensagem novaMensagem(dataHora, id, mensagem);

  itServidor -> sendMensagem(servidorCanal.second, novaMensagem);

  return "A mensagem foi enviada com sucesso.";
  */
  return "Ainda não implementado.";
}

//Listar as mensagens do canal
string Sistema::list_messages(int id) {
/*  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  if(servidorCanal.first.length() == 0) {
    return "O usuário não está conectado a um servidor no momento.";
  }

  if(servidorCanal.second.length() == 0) {
    return "O usuário não está conectado a um canal no momento.";
  }

  string nomeServidor = servidorCanal.first;

  auto itServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });

  vector<Mensagem> listaMensagens = itServidor -> getMensagens(servidorCanal.second);

  if(listaMensagens.empty()) {
    return "Não há mensagens.";
  }

  string mensagens;
  for(auto itMensagem = listaMensagens.begin(); itMensagem != listaMensagens.end(); itMensagem++) {
    mensagens += usuarios[itMensagem -> getEnviadaPor() - 1].getNome() + " <" + itMensagem -> getDataHora() + ">: " + itMensagem -> getConteudo() + "\n";
  }  
  return mensagens;
  */
  return "Ainda não implementado.";
}

