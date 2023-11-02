/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:40:21 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/02 08:40:13 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client() : _clientFd(), _clientAdress(), _username() {}
Client::~Client() {}



Client::Client(int fd, const struct sockaddr_in &addr)
		: _clientFd(fd), _clientAdress(addr),  _username(), _command() {
}

int	Client::getClientFd() const {
	return (this->_clientFd);
}

const struct sockaddr_in& Client::getClientAddress() const {
	return (this->_clientAdress);
}

void	Client::addToCommand(const char *buffer) {
	this->_command += buffer;
}

const std::string	&Client::getClientCommand() const {
	return (this->_command);
}

void	Client::printCommand() {
	std::cout << this->_command << std::endl;
	this->_command.clear();
}

bool	Client::handleCommand() {
	
	if (this->_command.size() >= BUFFER_SIZE) {
		std::cerr << "Error command size : reseting command" << std::endl;
		this->_command.clear();
		return (false);
	} else if (this->_command.find("\r\n") == std::string::npos) {
		std::cerr << "error pas de caractere de fin" << std::endl;
		return (false);
	}

	std::istringstream	iss(this->_command);
	std::string			prefix, command, params;
	if (this->_command[0] == ':') {
		iss >> prefix; // extract prefix
		prefix = prefix.substr(1);
	}
	iss >> command; // extract command
	std::getline(iss, params); // extract params

	std::cout << "Prefix: " << prefix << std::endl;
    std::cout << "Command: " << command << std::endl;
    std::cout << "Params: " << params << std::endl;
	
	return (true);
}