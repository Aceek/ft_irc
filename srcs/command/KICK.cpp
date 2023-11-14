/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:12 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/14 01:10:14 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::KICK() {
/*   Parameters: <channel> <user> [<comment>]	*/
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string channelName = this->_args[0];
    Channel *channel = this->_server.getChannel(channelName);
    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }
    if (!channel->isOperator(this->_client)) {
        return ERR_CHANOPRIVSNEEDED;
    }
   
    std::string nickname = this->_args[1];
	Client *client = this->_server.getClientByNickname(nickname);
	if (!client) {
    	return ERR_NOSUCHNICK;
    }
    if (!channel->isClientPresent(*client)) {
        return ERR_NOTONCHANNEL;
    }

	channel->delUser(*client);
    
	//to be rework with formated server response
	std::string kickMessage = 	":" + this->_client.getNicknameOrUsername(true) +
                              	" " + this->_name +
                              	" " + channelName;
								" " + nickname;							
	if (!this->_trailor.empty()) {
    	kickMessage += " :" + this->_trailor;
	}

	this->_server.sendMessageToChannel(*channel, kickMessage);

    return ERR_NONE;
}
