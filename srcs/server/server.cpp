/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:25:53 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/21 15:09:27 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server(int port, std::string password) : _port(port), _password(password), _serverReply(new serverReply(*this)) {
	
	// Creer la socket et on la relie a un fd
	this->_serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverFd == -1) {
		delete(this->_serverReply);
		throw std::runtime_error("Error lors de creation de la socket server");
	}

	// Configurer l'adress du server
	this->_serverAdress.sin_family = AF_INET;
	this->_serverAdress.sin_addr.s_addr = INADDR_ANY;
	this->_serverAdress.sin_port = htons(this->_port);

	// Liason de la socket avec info server

	if (bind(_serverFd, (struct sockaddr *)&_serverAdress, sizeof(_serverAdress)) < 0) {
		close (this->_serverFd);
		delete(this->_serverReply);
		printServerInput(std::string(strerror(errno)));
		throw std::runtime_error("Error lors de la liaison de la socket");
	}

	// Passage en mode ecoute
	if (listen(this->_serverFd, SOMAXCONN) < 0) {
		close (this->_serverFd);
		delete(this->_serverReply);
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

void	Server::routinePOLLIN(std::vector<struct pollfd>::iterator &pollfdIt) {
		if (pollfdIt->fd == this->_serverFd) {
			acceptClient();
		} else {
			if (!processCommand(pollfdIt->fd)) {
				this->_clientsToRemove.push_back(pollfdIt->fd);
			}
		}

}

void	Server::routine() {
	while (!serverShutdown) {
		int ready = poll(this->_fds.data(), this->_fds.size(), -1);
		if (ready == -1) {
			printServerInput(std::string(strerror(errno)));
			break;
		}
		for (std::vector<struct pollfd>::iterator it = this->_fds.begin(); it != this->_fds.end(); ++it) {
			if (it->revents & (POLLERR | POLLHUP | POLLNVAL)) {
				this->_clientsToRemove.push_back(it->fd);
				continue ;
			} if (it->revents & POLLIN) {
				routinePOLLIN(it);
			} else if (it->revents & POLLOUT) {
				verifyMessageSend(it->fd);
			}
		}
		removeClients();
		addClientsToPoll();
	}
	closingFdClients();
	close(this->_serverFd);
	printServerInput(getServerMessage(SERVER_CLOSING));
}

void	Server::addClientsToPoll() {
	for (std::vector<int>::iterator it = this->_clientsToAdd.begin(); 
									it != this->_clientsToAdd.end(); it++) {
		addToPoll(*it, POLLIN | POLLOUT | POLLERR | POLLHUP | POLLNVAL);
	}
	this->_clientsToAdd.clear();
}

void	Server::removeClients() {
	for (size_t i = 0; i < this->_clientsToRemove.size(); i++) {
		removeClient(this->_clientsToRemove[i]);
	}
	this->_clientsToRemove.clear();
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

	std::map<int, std::deque<std::string> >::iterator itMsg
		= this->_messageQueue.find(clientFd);
	if (itMsg != this->_messageQueue.end()) {
		this->_messageQueue.erase(clientFd);
	}

	if (close (clientFd) == -1) {
		perror("Error closing client socket");
	}

	// ajouter gestion message de retrait server A FAIRE ?
	printServerInput(getServerMessage(SERVER_DELCLIENT));
}	

int	Server::acceptClient() {
	struct sockaddr_in	clientAdress;
	socklen_t			clientAdressSize = sizeof(clientAdress);
	
	int clientFd = accept(this->_serverFd, (struct sockaddr *)&clientAdress, &clientAdressSize);

	
	if (clientFd == -1) {
		printServerInput(getServerMessage(ERR_SERVER_ACCEPTCLIENT));
	}
	
	Client newClient(clientFd, clientAdress);
	this->_clients[clientFd] = newClient;
	
	// Ajoutez le descripteur de fichier associé au client à _fds pour le suivi avec poll()
	this->_clientsToAdd.push_back(clientFd);
	printServerInput(getServerMessage(SERVER_NEWCLIENT));

	return (clientFd);
}

Server::Server() {};
Server::~Server() {
	close(this->_serverFd);
	delete(this->_serverReply);
};

void Server::tryCommand(Client &client, const int clientFd) {
	std::string clientCommand = client.getClientCommand();
	size_t newlinePos = clientCommand.find('\n');

	while (newlinePos != std::string::npos) {
		std::string currentCommand = clientCommand.substr(0, newlinePos);
		try {
			Command command(currentCommand, client, *this);
			command.exec();
		} catch(const std::exception& e) {
			setMessageQueue(clientFd, getErrorMessage(ERR_PASSNEEDED));
		}
		clientCommand = clientCommand.substr(newlinePos + 1);
		newlinePos = clientCommand.find('\n');
	}
	client.clearCommand();
}



bool	Server::processCommand(const int &clientFd) {
	
	char	buffer[MAX_COMMAND_SIZE + 1] = "";
	Client	&client = this->_clients[clientFd];

	memset(buffer, 0, sizeof(buffer));

	int		bytesReceived = recv(clientFd, buffer, sizeof(buffer), 0);
	if (bytesReceived == -1 || bytesReceived == 0) { // a faire
		return (false);
	}
	buffer[bytesReceived] = '\0';
	client.addToCommand(buffer);
	if (client.verifyCommand(*this)) {
		tryCommand(client, clientFd);
	}
	return (true);
}

void Server::sendMessage(const int clientFd, const std::string &message) const {
	std::string newMessage = message + "\n";
	int bytesSent = send(clientFd, newMessage.c_str(), newMessage.size(), 0);

	if (bytesSent == -1) {
		// gestion erreur a faire !
		printServerInput(getServerMessage(ERR_SERVER_SENDING));
	}
}

void Server::sendFile(const int clientFd, const std::string &filePath) {
	std::ifstream fileStream(filePath.c_str(), std::ios::binary);
	if (!fileStream.is_open()) {
		printServerInput(getServerMessage(ERR_SERVER_SENDING));
		return;
	}

	// Determine the file size
	fileStream.seekg(0, std::ios::end);
	int fileSize = fileStream.tellg();
	fileStream.seekg(0, std::ios::beg);

	const int chunkSize = MAX_COMMAND_SIZE;
	char buffer[MAX_COMMAND_SIZE];

	while (fileSize > 0) {
		int bytesRead = fileStream.readsome(buffer, std::min(fileSize, chunkSize));
		int bytesSent = send(clientFd, buffer, static_cast<size_t>(bytesRead), 0);

		if (bytesSent == -1) {
			printServerInput(getServerMessage(ERR_SERVER_SENDING));
			break;
		}

		fileSize -= bytesRead;
	}

	fileStream.close();
}

void Server::verifyMessageSend(const int clientFd) {
	
	std::deque<std::string>& messages = this->_messageQueue[clientFd];
	for (std::deque<std::string>::iterator msgIt = messages.begin();
	msgIt != this->_messageQueue[clientFd].end(); msgIt++) {
		sendMessage(clientFd, *msgIt);
	}
	messages.clear();
}