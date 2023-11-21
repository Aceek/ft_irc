/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/21 15:08:26 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int	Command::PASS() {

	if (this->_client.isPasswordSetUp()) {
		return (ERR_ALREADYREGISTRED);
	}
	if (this->_args.empty() || this->_args[0].empty()) {
		return (ERR_NEEDMOREPARAMS);
	}
	if (!isValidPassword()) {
		return (ERR_PASSFORMAT);
	}
	if (this->_args[0] == this->_server.getPassword()) {
		this->_client.setPassRegister();
	} else {
		return (ERR_PASSWRONG);
	}
	std::string passMessage = 	":" + this->_client.getPrefix() +
								" 001 " + this->_name;
	
	this->_server.setMessageQueue(this->_client.getClientFd(), passMessage);
	// this->_server.setMessageQueue(this->_client.getClientFd(), "Password match, Welcome to irc server");
	return (ERR_NONE);
}
