/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:18 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/15 06:44:34 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"
///!!!revoir parsing des modes et parametre???? : atm -> MODE +t +i -k =/= +ti -k
int Command::MODE() {
    /* Parameters: <channel> <+/-modes> [parameters] */
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string	const	&channelName = this->_args[0];
    Channel 			*channel = this->_server.getChannel(channelName);
    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }
    if (!channel->isOperator(this->_client)) {
        return ERR_CHANOPRIVSNEEDED;
    }

    for (std::vector<std::string>::const_iterator it = this->_args.begin() + 1; 
		it != this->_args.end(); ++it) {
        char s = (*it)[0];
        if (s != '+' && s != '-') {
            return ERR_UNKNOWNMODE;
        }

        char c = (*it)[1];
        switch (c) {
            case 'i':
                // Set/unset the channel on invitation only
                channel->setInviteOnly(s == '+');
                break;
            case 't':
                // Set/unset restrictions on the TOPIC command for channel operators
                channel->setTopicRestricted(s == '+');
                break;
			case 'k':
				// Set/unset the channel key (password)
				if (s == '+') {
					if (++it == this->_args.end()) {
						return ERR_NEEDMOREPARAMS;
					} 
					if (!isValidPassword(*it)) {
						return ERR_PASSFORMAT;
					}
					channel->setKey(*it);
				} else {
					channel->setKey("");
				}
				break;
			case 'o': {
				// Give/take operator privilege from a user
				if (++it == this->_args.end()) {
					return ERR_NEEDMOREPARAMS;
				}
				Client *client = this->_server.getClientByNickname(*it);
				if (!client) {
					return ERR_NOSUCHNICK;
				}
				channel->addUser(*client, s == '+');
				break;
			}
            case 'l':
                // Set/unset the limit of users for the channel
                if (++it == this->_args.end()) {
                    return ERR_NEEDMOREPARAMS;
                }
                channel->setUserLimit(s == '+' ? atoi(it->c_str()) : -1);
                break;
            default:
                return ERR_UNKNOWNMODE;
			}
			//to be rework with formated server response
			std::string modeMessage =	":" + this->_client.getNicknameOrUsername(true) +
										" " + this->_name +
										" " + channelName +
										" " + s + c;

		this->_server.sendMessageToChannel(*channel, modeMessage);
    }
	
    return ERR_NONE;
}
