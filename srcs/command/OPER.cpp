/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:34 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/14 04:49:31 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::OPER() {
    /* Parameters: <user> <password> */
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string const	&nickname = this->_args[0];
    std::string const	&password = this->_args[1];

    ///!!! should we use nickname or username ???
	Client *client = this->_server.getClientByNickname(nickname);
    if (!client) {
        return ERR_NOSUCHNICK;
    }
    if (password != this->_server.getPassword()) {
        return ERR_PASSWDMISMATCH;
	}

	this->_server.grantOperatorStatus(client->getClientFd());

	//to be rework with formated server response
	this->_server.setMessageQueue(client->getClientFd(), "You are now an operator");

    return ERR_NONE;
}
