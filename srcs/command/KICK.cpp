/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:12 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 04:10:12 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::KICK() {
/*   Parameters: <channel> <user> [<comment>]	*/
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string channelName = this->_args[0];
    std::string nickname = this->_args[1];
    std::string comment = this->_trailor;

    Channel *channel = this->_server.getChannel(channelName);
    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }

    if (!channel->isOperator(this->_client)) {
        return ERR_CHANOPRIVSNEEDED;
    }
	
	Client *client = this->_server.getClientByNickname(nickname);
	if (!client) {
    	return ERR_NOSUCHNICK;
    }
	
    if (!channel->isClientPresent(*client)) {
        return ERR_NOTONCHANNEL;
    }

    std::string kickMessage =	":" + this->_client.getNicknameOrUsername(true) +
								" " + this->_name +
								" " + channelName + 
								" " + nickname;

	if (!comment.empty()) {
    	kickMessage += " :" + comment;
	}
								
    channel->sendMessageToAll(kickMessage);
    
	channel->delUser(*client);

    return ERR_NONE;
}
