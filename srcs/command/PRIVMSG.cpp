
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:51 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 04:07:58 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::PRIVMSG() {
/*	Parameters: <receiver>{,<receiver>} <text to be sent> */
    if ((this->_args.size() < 2 && this->_trailor.empty()) ||
		(this->_args.size() < 1 )) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string> receivers = ft_split(this->_args[0], ",");
    std::string message;
	if (this->_args.size() >= 2 && !this->_args[1].empty()) {
		message = this->_args[1];
	}
	if (!this->_trailor.empty()) {
		message += " " + this->_trailor;
	}
	if (message.empty()) {
		return ERR_NOTEXTTOSEND;
	}

	//!!! is it possible to send a message to ourselve ? if so check double output msg
	for (std::vector<std::string>::iterator it = receivers.begin();
		it != receivers.end(); ++it) {
			//to be rework with formated server response
			std::string privmsgMessage = ":" + this->_client.getNicknameOrUsername(true) +
								" " + this->_name +
								" " + *it +
								" :" + message;
			if ((*it)[0] == '#') {
				Channel	*channel = this->_server.getChannel(*it);
					if (!channel) {
						return ERR_NOSUCHCHANNEL;
					} else if (!channel->isClientPresent(this->_client)) {
						return ERR_CANNOTSENDTOCHAN;
					} else {
						this->_server.sendMessageToChannel(*channel, privmsgMessage);
						//!!! not sur if the message should be send back for each receiver
						this->_server.setMessageQueue(this->_client.getClientFd(), privmsgMessage);
					}
			} else {
    			Client *client = this->_server.getClientByNickname(*it);
    				if (!client) {
        				return ERR_NOSUCHNICK;
   					} else {
						this->_server.setMessageQueue(client->getClientFd(), privmsgMessage);
						//!!! not sur if the message should be send back for each receiver
						this->_server.setMessageQueue(this->_client.getClientFd(), privmsgMessage);
					}
			}
		}
		
    return ERR_NONE;
}
