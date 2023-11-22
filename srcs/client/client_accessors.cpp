/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_accessors.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:25:35 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/22 16:08:09 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

int	Client::getClientFd() const {
	return (this->_clientFd);
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

void	Client::setUserRegister() {
	this->_userRegister = true;
}

void	Client::setNickRegister() {
	this->_nickRegister = true;
}

std::string Client::getPrefix(void) const {
	std::string prefix = this->_nickname;
	if (!this->_username.empty())
		prefix += "!" + this->_username;
	
	return prefix + "@" + this->_hostname;
}

std::set<Channel *>	const &Client::getChannels(void) const {
	return this->_channels;
}
