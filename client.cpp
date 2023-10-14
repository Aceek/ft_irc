/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:40:21 by ilinhard          #+#    #+#             */
/*   Updated: 2023/10/14 17:25:52 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client() : _clientFd(), _clientAdress(), _username() {}
Client::~Client() {}



Client::Client(int fd, const struct sockaddr_in &addr)
		: _clientFd(fd), _clientAdress(addr),  _username() {
}

int	Client::getClientFd() const {
	return (this->_clientFd);
}

const struct sockaddr_in& Client::getClientAddress() const {
	return (this->_clientAdress);
}
