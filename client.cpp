/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:40:21 by ilinhard          #+#    #+#             */
/*   Updated: 2023/10/24 05:48:57 by ilinhard         ###   ########.fr       */
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

bool	Client::addToCommand(const char *buffer) {
	this->_command += buffer;
	if (_command.size() >= BUFFER_SIZE) {
		this->_command.clear();
		return (false);
	}
	return (true);
}

const std::string	&Client::getClientCommand() const {
	return (this->_command);
}

void	Client::printCommand() {
	std::cout << this->_command << std::endl;
	this->_command.clear();
}