/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:40:21 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/09 18:16:41 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client() : _clientFd(), _clientAdress(), _nickname() {}
Client::~Client() {}



Client::Client(int fd, const struct sockaddr_in &addr)
		: _clientFd(fd), _clientAdress(addr), _passRegister(false), _register(false) {
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

const std::string	&Client::getNicknameOrUsername(bool useNickname) const {
	if (useNickname) {
		return (this->_nickname);
	} else {
		return (this->_username);
	}
}

void	Client::setNickname(std::string const &nickname) {
	this->_nickname = nickname;
}

void	Client::setUsername(std::string const &username) {
	this->_username = username;
}

void	Client::setRealName(std::string const &realName) {
	this->_realName = realName;
}

void	Client::setPassRegister() {
	this->_passRegister = true;
}

void	Client::setRegister() {
	this->_register = true;
}

bool	Client::isPasswordSetUp() const {
	return (this->_passRegister);
}

bool	Client::isRegister() const {
	return (this->_register);
}


void	Client::printCommand() {
	std::cout << this->_command << std::endl;
}

void	Client::clearCommand() {
	this->_command.clear();
}

bool	Client::verifyCommand() {
	
	if (this->_command.size() >= BUFFER_SIZE) {
		std::cerr << "Error command size : reseting command" << std::endl;
		this->_command.clear();
		return (false);
	} else if (this->_command.find("\r\n") == std::string::npos) {
		std::cerr << "error pas de caractere de fin" << std::endl;
		return (false);
	}

	return (true);
}