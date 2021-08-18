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
  
  auto servidorCanal = make_pair("","");
  map< int , pair<string, string> > usuariosLogados;

}

Sistema::~Sistema() {}

string Sistema::quit() {
  return "Saindo...";
}

//Funcionalidades 1
//Cria um novo usuário
string Sistema::create_user(const string email, const string senha, const string nome) {
  
  if(email.empty() && senha.empty() && nome.empty()) {
    return "Os campos não podem ser vazios.";
  }

  for(long unsigned int i = 0; i < usuarios.size(); i++) {
    if (usuarios[i].getEmail() == email) {
      return "Usuário já existe.";
    }
  }

  Usuario novoUsuario;
  novoUsuario.setId(usuarios.size() + 1);
  novoUsuario.setNome(nome);
  novoUsuario.setEmail(email);
  novoUsuario.setSenha(senha);

  usuarios.push_back(novoUsuario);

  return "Usuário criado!";
  
}

//Realiza o login do usuário
string Sistema::login(const string email, const string senha) {
  
  vector<Usuario>::iterator it = usuarios.begin();
  //Verifica se o usuário existe
  while(it != usuarios.end()) {
    if(it -> getEmail() == email) {
      if(it -> getSenha() == senha) {
        usuarioLogadoID = it -> getId();
        return "Logado como " + email;
      }
    }
    it++;
  }
  return "Email ou senha incorretos. Tente novamente!";

}

//Desconecta o usuário
string Sistema::disconnect(int id) {
  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }
  int idLogadoAnterior = id;
  id = 0;

  return "Desconectando usuário " + usuarios[idLogadoAnterior - 1].getEmail() + ".";

}

//Cria um servidor
string Sistema::create_server(int id, const string nome) {
  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  if(nome.empty()) {
    return "Não é possível criar um servidor sem nome.";
  }

  for(long unsigned int i = 0; i < servidores.size(); i++) {
    if(servidores[i].getNome() == nome) {
      return "Servidor com esse nome já existe.";
    }
  }

  Servidor newServidor(id, nome);
  servidores.push_back(newServidor);

  return "Servidor criado.";
  
}

//Modifica a descrição de um servidor
string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }
  //Verificar se existe servidor com o nome
  vector<Servidor>::iterator it;
  it = find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor) {
    return nome == servidor.getNome();
  });
  if(it == servidores.end()) {
    return "Servidor '" + nome + "' não existe.";
  }
  //Verifica se o usuário é o dono
  if(it->getUsuarioDonoId() != id) {
    return "Você não pode alterar a descrição de um servidor que não foi criado por você.";
  }

  it -> setDescricao(descricao);

  return "Descrição do servidor '" + nome + "' modificada com sucesso.";
  
}

//Altera o código de convite de um servidor
string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }
//Verificar se existe servidor com o nome
  vector<Servidor>::iterator it;
  it = find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor) {
    return nome == servidor.getNome();
  });
  if(it == servidores.end()) {
    return "Servidor '" + nome + "' não existe.";
  }
  //Verifica se o usuário é o dono
  if(it->getUsuarioDonoId() != id) {
    return "Você não pode alterar a descrição de um servidor que não foi criado por você.";
  }
  
  if(codigo.length() > 0) {
    it -> setCodigoConvite(codigo);
    return "Código de convite do servidor '" + nome +"' modificado!";
  }
  //Se não houver um código
  it -> setCodigoConvite("");

  return "Código de convite do servidor '" + nome +"' removido!";

}

//Lista todos os servidores
string Sistema::list_servers(int id) {
  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  if(servidores.empty()) {
    return "Não há servidores cadastrados.";
  }

  string listaServidores = "";
  for(long unsigned int i = 0; i < servidores.size(); i++) {
    listaServidores += servidores[i].getNome() + "\n";
  }

  return listaServidores;

}

//Deleta um servidor
string Sistema::remove_server(int id, const string nome) {
  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }
  //Verificar se existe servidor com o nome
  vector<Servidor>::iterator it;
  it = find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor) {
    return nome == servidor.getNome();
  });
  if(it == servidores.end()) {
    return "Servidor '" + nome + "' não existe.";
  }
  //Verifica se o usuário é o dono
  if(it->getUsuarioDonoId() != id) {
    return "Você não pode alterar a descrição de um servidor que não foi criado por você.";
  }

  servidores.erase(it);

  return "Servidor '" + nome + "' removido";

}

//Entrar em um servidor
string Sistema::enter_server(int id, string nome, string codigo) {
  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }
  //Verificar se existe servidor com o nome
  vector<Servidor>::iterator it;
  it = find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor) {
    return nome == servidor.getNome();
  });
  if(it == servidores.end()) {
    return "Servidor '" + nome + "' não existe.";
  }

  servidorCanal = make_pair(nome,"");
  it -> pushParticipante(id);

  return "Entrou no servidor com sucesso";

}

//Sair de um servidor
string Sistema::leave_server(int id, const string nome) {
  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }
  //Verificar se existe servidor com o nome
  if(nome.length() == 0) {
    return "O usuário não está conectado a nenhum servidor.";
  }

  string tmp = nome;
  servidorCanal.first = "";

  return "O usuário está aindo do servidor \'" + nome + "\'.";

}

//Listar os participantes de um servidor
string Sistema::list_participants(int id) {
  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }
  
  if(servidorCanal.first.empty()) {
    return "Não existe servidor conectado.";
  }

  Servidor findServidor;
  for (long unsigned int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == servidorCanal.first) {
      findServidor = servidores[i];
    };
  }

  string listaParticipantes = "";
  vector<int> listaIDs = findServidor.getParticipantesIDs();

  for (long unsigned int i = 0; i < usuarios.size(); i++) {
    for (long unsigned int j = 0; j < listaIDs.size(); j++) {
      if (usuarios[i].getId() == listaIDs[j]) listaParticipantes += usuarios[i].getNome() + "\n";
    }
  }

  return listaParticipantes;

}

//Funcionalidades 2
//Listar os canais do servidor
string Sistema::list_channels(int id) {
  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  if(servidorCanal.first.length() == 0) {
    return "O usuário não está conectado a um servidor no momento.";
  }

  //Obtém o servidor na lista pelo nome
  string nomeServidor = servidorCanal.first;
  auto itServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return nomeServidor == servidor.getNome();
  });

  vector<string> canaisTexto = itServidor -> getCanaisTexto();

  if(canaisTexto.empty()) {
    return "Nenhum canal no servidor foi encontrado.";
  }
  //Variável de retorno para concatenar os canais
  string canais;
  if (!canaisTexto.empty()) {
    canais += "#canais de texto\n";

    for (auto findCanal = canaisTexto.begin(); findCanal != canaisTexto.end(); findCanal++) {
      if (findCanal != canaisTexto.end()) canais += *findCanal + "\n";
    }
  }
  return canais;

}
//Criar um canal do servidor
string Sistema::create_channel(int id, const string nome) {

  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  if(servidorCanal.first.length() == 0) {
    return "O usuário não está conectado a um servidor no momento.";
  }

  if(nome.length() == 0) {
    return "O canal precisa ter um nome";
  }

  string nomeServidor = servidorCanal.first;

  auto itServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });

  vector<string> canaisTexto = itServidor -> getCanaisTexto();
  auto itCanal = find_if(canaisTexto.begin(), canaisTexto.end(), [nome](string nomeCanal) {
    return nomeCanal == nome;
  });

  if(itCanal != canaisTexto.end()) {
    return "Canal de texto \'" + nome + "\' já existe.";
  }

  vector<Mensagem> mensagens;
  shared_ptr<CanalTexto> novoCanal(new CanalTexto(nome, mensagens));
  bool canalCriado = itServidor -> createCanal(novoCanal);

  if(canalCriado) {
    return "Canal de texto \'" + nome + "\' criado.";
  }

  return "Houve um erro ao criar canal.";
  
}

//Entrar em um canal
string Sistema::enter_channel(int id, string nome) {
  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  if(servidorCanal.first.length() == 0) {
    return "O usuário não está conectado a um servidor no momento.";
  }

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
  
  if(id == 0) {
    return "Não existe usuário conectado.";
  }

  if(servidorCanal.first.length() == 0) {
    return "O usuário não está conectado a um servidor no momento.";
  }

  if(servidorCanal.second.length() == 0) {
    return "O usuário não está conectado a um canal no momento.";
  }

  string nomeCanal = servidorCanal.second;
  servidorCanal.second = "";

  return "O usuário está saindo do canal \'" + nomeCanal + "\'.";
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

