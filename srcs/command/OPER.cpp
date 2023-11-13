/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:34 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 11:11:55 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::OPER() {
    /* Parameters: <user> <password> */
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string nickname = this->_args[0];
    std::string password = this->_args[1];

    ///!!! should we use nickname or username ???
	Client *client = this->_server.getClientByNickname(nickname);
    if (!client) {
        return ERR_NOSUCHNICK;
    }

    if (password != this->_server.getPassword()) {
        return ERR_PASSWDMISMATCH;
	}

	this->_server.grantOperatorStatus(client->getClientFd());

    this->_server.setMessageQueue(client->getClientFd(), "You are now an operator");

    return ERR_NONE;
}
