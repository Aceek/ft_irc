/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:25:53 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/27 19:07:52 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/server/server.hpp"

Server::Server(int port, std::string password)
    : _port(port), _password(password), _serverReply(new serverReply(*this)) {
  // Creer la socket et on la relie a un fd
  this->_serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->_serverFd == -1) {
    delete (this->_serverReply);
    throw std::runtime_error("Error lors de creation de la socket server");
  }

  // Configurer l'adress du server
  this->_serverAdress.sin_family = AF_INET;
  this->_serverAdress.sin_addr.s_addr = INADDR_ANY;
  this->_serverAdress.sin_port = htons(this->_port);

  // Liason de la socket avec info server

  if (bind(_serverFd, (struct sockaddr *)&_serverAdress,
           sizeof(_serverAdress)) < 0) {
    close(this->_serverFd);
    delete (this->_serverReply);
    this->_serverReply->displayServerMessage(ERR_BIND);
    throw std::runtime_error("Error lors de la liaison de la socket");
  }

  // Passage en mode ecoute
  if (listen(this->_serverFd, SOMAXCONN) < 0) {
    close(this->_serverFd);
    delete (this->_serverReply);
    throw std::runtime_error("Error lors de la mise en ecoute de la socket");
  }
  addToPoll(this->_serverFd, POLLIN);
}

void Server::routine() {
  while (!serverShutdown) {
    int ready = poll(this->_fds.data(), this->_fds.size(), -1);
    if (ready == -1) {
      this->_serverReply->displayServerMessage(ERR_POLL);
      break;
    }
    for (std::vector<struct pollfd>::iterator it = this->_fds.begin();
         it != this->_fds.end(); ++it) {
      if (it->revents & (POLLERR | POLLHUP | POLLNVAL)) {
        this->_clientsToRemove.push_back(it->fd);
        continue;
      }
      if (it->revents & POLLIN) {
        routinePOLLIN(it);
      }
      if (it->revents & POLLOUT) {
        this->_serverReply->verifyMessageSend(it->fd);
      }
    }
    removeClients();
    addClientsToPoll();
  }
}

void Server::routinePOLLIN(
    const std::vector<struct pollfd>::iterator &pollfdIt) {
  if (pollfdIt->fd == this->_serverFd) {
    acceptClient();
  } else {
    if (!processCommand(pollfdIt->fd)) {
      this->_clientsToRemove.push_back(pollfdIt->fd);
    }
  }
}

int Server::acceptClient() {
  struct sockaddr_in clientAdress;
  socklen_t clientAdressSize = sizeof(clientAdress);

  int clientFd = accept(this->_serverFd, (struct sockaddr *)&clientAdress,
                        &clientAdressSize);

  if (clientFd == -1) {
    this->_serverReply->displayServerMessage(ERR_SERVER_ACCEPTCLIENT);
  }

  Client newClient(clientFd, clientAdress);
  this->_clients[clientFd] = newClient;

  // Ajoutez le descripteur de fichier associé au client à _fds pour le suivi
  // avec poll()
  this->_clientsToAdd.push_back(clientFd);
  this->_serverReply->displayServerMessage(SERVER_NEWCLIENT);

  return (clientFd);
}

void Server::tryCommand(Client *client) {
  std::string clientCommand = client->getClientCommand();
  size_t newlinePos = clientCommand.find('\n');

  while (newlinePos != std::string::npos) {
    std::string currentCommand = clientCommand.substr(0, newlinePos);
    Command command(currentCommand, *client, *this);
    command.exec();
    clientCommand = clientCommand.substr(newlinePos + 1);
    newlinePos = clientCommand.find('\n');
  }
  client->clearCommand();
}

bool Server::processCommand(const int &clientFd) {
  char buffer[MAX_COMMAND_SIZE + 1] = "";
  Client &client = this->_clients[clientFd];

  memset(buffer, 0, sizeof(buffer));

  int bytesReceived = recv(clientFd, buffer, sizeof(buffer), 0);
  if (bytesReceived == -1 || bytesReceived == 0) {  // a faire
    return (false);
  }
  buffer[bytesReceived] = '\0';
  client.addToCommand(buffer);
  if (client.verifyCommand()) {
    tryCommand(&client);
  }
  return (true);
}

Server::~Server() {
  deconectionClients();
  closingFdClients();
  close(this->_serverFd);
  delete (this->_serverReply);
  this->_serverReply->displayServerMessage(SERVER_CLOSING);
}
