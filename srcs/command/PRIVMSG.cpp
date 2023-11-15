
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
			std::string const	&receiver = *it;
			//to be rework with formated server response
			std::string privmsgMessage =	":" + this->_client.getNicknameOrUsername(true) +
											" " + this->_name +
											" " + receiver +
											" :" + message;
			
			if (isValidChannelName(receiver)) {
				Channel	*channel = this->_server.getChannel(receiver);
				if (!channel) {
					return ERR_NOSUCHCHANNEL;
				}
				if (!channel->isClientPresent(this->_client)) {
					return ERR_NOTONCHANNEL;
				}
				
				this->_server.sendMessageToChannel(*channel, privmsgMessage);
			} else {
    			Client *client = this->_server.getClientByNickname(receiver);
				if (!client) {
					return ERR_NOSUCHNICK;
				}
				
				const int	senderFd = this->_client.getClientFd();
				const int	receiverFd = client->getClientFd();
				if (receiverFd != senderFd) {
					this->_server.setMessageQueue(senderFd, privmsgMessage);
				}
				this->_server.setMessageQueue(receiverFd, privmsgMessage);
			}
	}
		
    return ERR_NONE;
}
