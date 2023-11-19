/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:40:21 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/19 17:13:13 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client() : _clientFd(), _clientAdress(), _nickname(), _command("") {}
Client::~Client() {
}

Client::Client(int fd, const struct sockaddr_in &addr)
    : _clientFd(fd), _clientAdress(addr), _nickname(""), _command(""),
      _username(""), _realName(""), _hostname("localhost"),
      _passRegister(false), _register(false) {}

const struct sockaddr_in& Client::getClientAddress() const {
	return (this->_clientAdress);
}

void	Client::addToCommand(const std::string &buffer) {
	this->_command += buffer;
}

void	Client::clearCommand() {
	this->_command.clear();
}

bool	Client::verifyCommand(Server &server) {
	
	// } else if (this->_command.find("\n") == std::string::npos) {
	if (this->_command.find("\r\n") == std::string::npos) {
		return (false);
	} else if (this->_command.empty() || this->_command.size() > BUFFER_SIZE) {
		server.printServerInput(server.getServerMessage(ERR_COMMAND_SIZE));
		server.setMessageQueue(this->_clientFd, server.getErrorMessage(ERR_COMMAND_SIZE));
		this->_command.clear();
		return (false);
	}

	return (true);
}
