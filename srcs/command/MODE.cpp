/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:18 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 23:54:52 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"
///!!!revoir parsing des modes et parametre???? : atm -> MODE +t +i -k =/= +ti -k
int Command::MODE() {
    /* Parameters: <channel> <+/-modes> [parameters] */
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string channelName = this->_args[0];
    Channel* channel = this->_server.getChannel(channelName);

    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }
    if (!channel->isOperator(this->_client)) {
        return ERR_CHANOPRIVSNEEDED;
    }

	for (std::vector<std::string>::const_iterator it = this->_args.begin() + 1;
		it != this->_args.end(); ++it) {
		char s = (*it)[0];
		char c = (*it)[1];
					std::cout << "s:" << s << std::endl;
					std::cout << "c:" << c << std::endl;

        switch (c) {
            case 'i':
				// Set/unset the channel on invitation only
                if (s == '+') {
					channel->setInviteOnly(true);
					std::cout << "coucou" << std::endl;
				} else if (s == '-') {
					channel->setInviteOnly(false);
				}
                break;
            case 't':
                // Set/unset restrictions on the TOPIC command for channel operators
				if (s == '+') {
					channel->setTopicRestricted(true);
				} else if (s == '-') {
					channel->setTopicRestricted(false);
				}
                break;
            case 'k':
                // Set/unset the channel key (password)
                if (s == '+') {
					if ((++it != this->_args.end())) {
						channel->setKey(*it);
					} else {
						return ERR_NEEDMOREPARAMS;
					}
				} else if (s == '-') {
					channel->setKey("");
				} 
                break;
            case 'o':
                // Give/take operator privilege from a user
				if ((++it != this->_args.end())) {
					Client *client = this->_server.getClientByNickname(*it);
					if (!client) {
						return ERR_NOSUCHNICK;
					}
					if (s == '+') {
						channel->addUser(*client, true);
					}  else if (s == '-') {
						channel->addUser(*client, false);
					}
				} else {
					return ERR_NEEDMOREPARAMS;
				}
                break;
            case 'l':
                // Set/unset the limit of users for the channel
                if (s == '+') {
					if (++it != this->_args.end()) {
						 channel->setUserLimit(atoi((*it).c_str()));
					}  else {
						return ERR_NEEDMOREPARAMS;
					}
				} else if (s == '-') {
					channel->setUserLimit(-1);
				}
                break;
            default:
                return ERR_UNKNOWNMODE;
		}
		
	//to be rework with formated server response
	std::string modeMessage = ":" + this->_client.getNicknameOrUsername(true) +
                              " " + this->_name +
                              " " + channelName +
                              " " + s + c;

    channel->sendMessageToAll(modeMessage);
    }
	
    return ERR_NONE;
}
