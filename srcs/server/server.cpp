/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:25:53 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/13 06:19:56 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server(int port, std::string password) : _port(port), _password(password) {
	
	// Creer la socket et on la relie a un fd
	this->_serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverFd == -1) {
		throw std::runtime_error("Error lors de creation de la socket server");
	}

	// Configurer l'adress du server
	this->_serverAdress.sin_family = AF_INET;
	this->_serverAdress.sin_addr.s_addr = INADDR_ANY;
	this->_serverAdress.sin_port = htons(this->_port);

	// Liason de la socket avec info server

	if (bind(_serverFd, (struct sockaddr *)&_serverAdress, sizeof(_serverAdress)) < 0) {
		throw std::runtime_error("Error lors de la liaison de la socket");
	}

	// Passage en mode ecoute
	if (listen(this->_serverFd, SOMAXCONN) < 0) {
		throw std::runtime_error("Error lors de la mise en ecoute de la socket");
	}
	addToPoll(this->_serverFd, POLLIN);
}

void	Server::addToPoll(int fd, short events) {
	// Push info about fd / event / revent into vector struct fds;
	struct pollfd tmpFd;
	tmpFd.events = events;
	tmpFd.fd = fd;
	tmpFd.revents = 0;
	this->_fds.push_back(tmpFd);
}

void	Server::routine() {
	while (!serverShutdown) {
		int ready = poll(this->_fds.data(), this->_fds.size(), -1);

		if (ready == -1) {
			break;
		}
		for (unsigned int i = 0; i < this->_fds.size(); i++) {
			if (_fds[i].revents & POLLIN) {
				if (_fds[i].fd == this->_serverFd) {
					acceptClient();
				} else {
					if (!processCommand(_fds[i].fd)) {
						this->_clientsToRemove.push_back(_fds[i].fd);
					}
				}
			}
		}
		removeClients();
	}
	close(this->_serverFd);
	std::cout << "Closing Server ..." << std::endl;
}

void	Server::removeClients() {
	for (size_t i = 0; i < this->_clientsToRemove.size(); i++) {
		removeClient(this->_clientsToRemove[i]);
	}
	
}

void Server::removeClient(const int clientFd) {
	

	// Suppression client dans pollfd 
	std::vector<pollfd>::iterator itPoll = this->_fds.begin();
	while (itPoll != _fds.end())
	{
		if (itPoll->fd == clientFd) {
			itPoll = this->_fds.erase(itPoll);
		} else {
			itPoll++;
		}
	}
	
	// Suppression client dans map client
	ClientMap::iterator itClient = this->_clients.find(clientFd);
	if (itClient != this->_clients.end()) {
		this->_clients.erase(clientFd);
	}

	if (close (clientFd) == -1) {
		std::cerr << "Error closing fdclient" << std::endl;
	}

	// ajouter gestion message de retrait server A FAIRE ?
	std::cout << "Client supprimé du server" << std::endl;
}	

int	Server::acceptClient() {
	struct sockaddr_in	clientAdress;
	socklen_t			clientAdressSize = sizeof(clientAdress);
	
	int clientFd = accept(this->_serverFd, (struct sockaddr *)&clientAdress, &clientAdressSize);
	
	if (clientFd == -1) {
		std::cout << "Erreur acceptation du client" << std::endl; // A FAIRE gestion erreur correct
	}
	
	Client newClient(clientFd, clientAdress);
	this->_clients[clientFd] = newClient;
	
	// Ajoutez le descripteur de fichier associé au client à _fds pour le suivi avec poll()
	addToPoll(clientFd, POLLIN);
	std::cout << "new client on server" << std::endl;
	
	return (clientFd);
}

Server::Server() {};
Server::~Server() {
	close(this->_serverFd);
};

bool	Server::processCommand(const int &clientFd) {
	
	char	buffer[MAX_COMMAND_SIZE + 1] = "";
	Client	&client = this->_clients[clientFd];
	int		errorCode = 0;

	memset(buffer, 0, sizeof(buffer));

	int		bytesReceived = recv(clientFd, buffer, sizeof(buffer), 0);
	if (bytesReceived == -1 || bytesReceived == 0) { // a faire
		std::cerr << "Error: receving message from client. Deconection" << std::endl;
		return (false);
	}
	client.addToCommand(buffer);
	if (client.verifyCommand()) {
		try {
			Command command(client.getClientCommand(), client, *this);
			//test print args
			command.printArgs();
			if ((errorCode = command.exec())) {
				sendMessage(client, getErrorMessage(errorCode));
			}
		} catch(const std::exception& e) {
			sendMessage(client, getErrorMessage(ERR_PASSNEEDED));
		}
		client.clearCommand();
	}
	return (true);
}

void Server::sendMessage(const Client &client, const std::string &message) const {
	std::string newMessage = message + "\n";
	int bytesSent = send(client.getClientFd(), newMessage.c_str(), newMessage.size(), 0);

	if (bytesSent == -1) {
		// gestion erreur a faire !
		std::cerr << "Error sending message to client" << std::endl;
	}
}

