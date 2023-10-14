/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:25:53 by ilinhard          #+#    #+#             */
/*   Updated: 2023/10/14 17:21:24 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "client.hpp"


Server::Server(int port) : _port(port) {
	
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
	while (true) {
		int ready = poll(this->_fds.data(), this->_fds.size(), -1);

		if (ready == -1) { // A FAIRE !! cas d'erreur de poll (alocation memoire trop courte, fd invalide cela doit etre non blocant)
			break;
		}

		for (long unsigned int i = 0; i < this->_fds.size(); i++) {
			if (_fds[i].revents & POLLIN) { // operation et pour savoir si le fd est en mode POLLIN
				if (_fds[i].fd == this->_serverFd) { // new client
					acceptClient();
				}
			}
		}
		

		
	}
	// Close socket function ?
	// freeSocket();
}

void	Server::acceptClient() {
	struct sockaddr_in	clientAdress;
	socklen_t			clientAdressSize = sizeof(clientAdress);
	
	int clientFd = accept(this->_serverFd, (struct sockaddr *)&clientAdress, &clientAdressSize);
	
	if (clientFd == -1) {
		std::cout << "Erreur acceptation du client" << std::endl; // A FAIRE gestion erreur correct
	}
	
	Client newClient(clientFd, clientAdress);
	this->_clients.push_back(newClient);
	
	// Ajoutez le descripteur de fichier associé au client à _fds pour le suivi avec poll()
	addToPoll(clientFd, POLLIN);
	std::cout << "new client on server" << std::endl;
	
}

Server::Server() {};
Server::~Server() {
	close(this->_serverFd);
};