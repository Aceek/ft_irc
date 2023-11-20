
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
    if (this->_args.size() < 1 ) {
        return ERR_NEEDMOREPARAMS;
    }
	if (this->_trailor.empty()) {
		return ERR_NOTEXTTOSEND;
	}

    std::vector<std::string> receivers = ft_split(this->_args[0], ",");
	//!!! is it possible to send a message to ourselve ? if so check double output msg
	for (std::vector<std::string>::iterator it = receivers.begin();
		it != receivers.end(); ++it) {
			if (isValidChannelName(*it)) {
				this->_targetChannel = this->_server.getChannel(*it);
				if (!this->_targetChannel) {
					return ERR_NOSUCHCHANNEL;
				}
				if (!this->_targetChannel->isClientPresent(this->_client)) {
					return ERR_NOTONCHANNEL;
				}

				this->_server.getServerReply()->PRIVMSG(*this, *this->_targetChannel);
			} else {
    			this->_targetClient = this->_server.getClientByNickname(*it);
				if (!this->_targetClient) {
					return ERR_NOSUCHNICK;
				}

				//msg send back to sender ?
				this->_server.getServerReply()->PRIVMSG(*this, *this->_targetClient);
			}
	}
		
    return ERR_NONE;
}
