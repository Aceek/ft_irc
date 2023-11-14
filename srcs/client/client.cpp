/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:40:21 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/14 03:27:05 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client() : _clientFd(), _clientAdress(), _nickname() {}
Client::~Client() {}

Client::Client(int fd, const struct sockaddr_in &addr)
		: _clientFd(fd), _clientAdress(addr), _passRegister(false), _register(false) {
}

const struct sockaddr_in& Client::getClientAddress() const {
	return (this->_clientAdress);
}

void	Client::addToCommand(const char *buffer) {
	this->_command += buffer;
}

void	Client::clearCommand() {
	this->_command.clear();
}

bool	Client::verifyCommand() {
	
	if (this->_command.size() >= BUFFER_SIZE) {
		std::cerr << "Error command size : reseting command" << std::endl;
		this->_command.clear();
		return (false);
	// } else if (this->_command.find("\r\n") == std::string::npos) {
	} else if (this->_command.find("\n") == std::string::npos) {
		std::cerr << "error pas de caractere de fin" << std::endl;
		std::cerr << "Command :" << this->_command << std::endl;
		return (false);
	}

	return (true);
}