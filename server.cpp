/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:25:53 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/11 03:49:59 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "client.hpp"


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
	while (true) {
		int ready = poll(this->_fds.data(), this->_fds.size(), -1);

		if (ready == -1) { // A FAIRE !! cas d'erreur de poll (alocation memoire trop courte, fd invalide cela doit etre non blocant)
			break;
		}

		for (long unsigned int i = 0; i < this->_fds.size(); i++) {
			if (_fds[i].revents & POLLIN) { // operation et pour savoir si le fd est en mode POLLIN
				if (_fds[i].fd == this->_serverFd) { // new client
					acceptClient();
				} else {
					processComand(_fds[i].fd);
				}
			}
		}
	}
	// Close socket function ?
	// freeSocket();
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

void	Server::processComand(const int &clientFd) {
	
	char	buffer[MAX_COMMAND_SIZE + 1] = "";
	Client	&client = this->_clients[clientFd];
	int		errorCode = 0;

	memset(buffer, 0, sizeof(buffer));

	int		bytesReceived = recv(clientFd, buffer, sizeof(buffer), 0);
	if (bytesReceived == -1) { // a faire
		std::cerr << "Error receiving message from client" << std::endl;
		return ;
	} else if (bytesReceived == 0) { // a faire connection ferme par le client
		std::cerr << "Error receiving message ... 0" << std::endl;
		return ;
	}
	client.addToCommand(buffer);
	if (client.verifyCommand()) {
		try {
			Command command(client.getClientCommand(), client, *this);
			command.printArgs();
			if ((errorCode = command.exec())) {
				sendMessage(client, getErrorMessage(errorCode));
			}
		} catch(const std::exception& e) {
			sendMessage(client, getErrorMessage(ERR_PASSNEEDED));
		}
		client.clearCommand();


	}
}

void Server::sendMessage(const Client &client, const std::string &message) const {
	std::string newMessage = message + "\n";
	int bytesSent = send(client.getClientFd(), newMessage.c_str(), newMessage.size(), 0);

	if (bytesSent == -1) {
		// gestion erreur a faire !
		std::cerr << "Error sending message to client" << std::endl;
	}
}

/* ************************************************************************** */

std::string Server::getErrorMessage(int errorCode) {
	// need add system add nickname of user .. 
    switch (errorCode) {
    case ERR_NONE:
        return "No error";
    case ERR_NONICKNAMEGIVEN:
        return "[Nick] 431: No nickname given";
    case ERR_ERRONEUSNICKNAME:
        return "[Nick] 432: Erroneous nickname";
    case ERR_NICKNAMEINUSE:
        return "[Nick] 433: Nickname is already in use";
    case ERR_NICKCOLLISION:
        return "[Nick] 436: Nickname collision KILL";
    case ERR_NEEDMOREPARAMS:
        return "[Command] 461: Not enough parameters";
    case ERR_REALNAME:
        return "[RealName] 1: Real Name bad format (max 25 char) + alphanumeric characters only";
    case ERR_PASSFORMAT:
        return "[Password] 2: Password bad format (max 25 char) + alphanumeric characters only";
    case ERR_PASSNEEDED:
        return "[Password] 3: Server password required to log in";
    case ERR_PASSWRONG:
        return "[Password] 4: Password does not match with server's password";
    case ERR_ALREADYREGISTRED:
        return "[Password] 462: You may not reregister (already done)";
    case ERR_NOSUCHCHANNEL:
        return "[Channel] 403: No such channel";
    case ERR_CHANOPRIVSNEEDED:
        return "[Channel] 482: You're not channel operator";
    case ERR_USERONCHANNEL:
        return "[Channel] 443: User already on channel";
    case ERR_BADCHANMASK:
        return "[Channel] 476: Bad channel mask";
    case ERR_BADCHANNELKEY:
        return "[Channel] 475: Bad channel key";
    case ERR_NOTONCHANNEL:
        return "[Channel] 442: You're not on that channel";
    case ERR_NOSUCHNICK:
        return "[User] 401: No such nick";
    default:
        return "Unknown error";
    }
}

const std::string	&Server::getPassword() const {
	return (this->_password);
}

Client *Server::getClientByNickname(std::string const &nickname) {
	for (std::map<const int, Client>::iterator it = this->_clients.begin();
		it != this->_clients.end(); ++it) {
			if (it->second.getNicknameOrUsername(true) == nickname) {
				return &it->second;
			}
	};
	
	return NULL;
}

const std::map<const int, Client> &Server::getClients() const {
	return (this->_clients);
}

Channel	*Server::getChannel(std::string const &channelName) {
	std::map<std::string, Channel>::iterator it = this->_channels.find(channelName);
		
	if (it->first == channelName) {
		return &it->second;
	}
	
	return NULL;
}

const ChannelMap &Server::getChannels() {
	return this->_channels;
}

/* ************************************************************************** */

void	Server::addChannel(std::string const &channelName) {
	this->_channels[channelName] = Channel(this);
}

void	Server::delChannel(std::string const &channelName) {
	std::map<std::string, Channel>::iterator it = this->_channels.find(channelName);
	
	if (it != this->_channels.end()) {
			this->_channels.erase(it);	
	}
}

void Server::printAllChannels(void) {
    std::cout << "List of Channels:" << std::endl;
	std::cout << std::endl;

    for (std::map<std::string, Channel>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it) {
        std::cout << "Channel Name: " << it->first << std::endl;
		if (!it->second.getKey().empty()) {
        	std::cout << "Key: " << it->second.getKey() << std::endl;
		}
		std::cout << std::endl;
	}
}
