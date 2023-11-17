/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PONG.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:46 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/17 08:18:41 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::SENDFILE() {
/*	Parameters: <receiver>{,<receiver>} <filePath> */
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string>	receivers = ft_split(this->_args[0], ",");
    std::string					filePath = this->_args[1];

	//!!! is it possible to send a message to ourselve ? if so check double output msg
	for (std::vector<std::string>::iterator it = receivers.begin();
		it != receivers.end(); ++it) {
	
		Client *client = this->_server.getClientByNickname(*it);
		if (!client) {
			return ERR_NOSUCHNICK;
		}
		
		std::cout << filePath << std::endl;
		this->_server.sendFile(client->getClientFd(), filePath);
		std::cout << filePath << std::endl;
	}

	return ERR_NONE;
}
