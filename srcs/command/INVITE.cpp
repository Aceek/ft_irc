/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:47:58 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 04:10:50 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::INVITE() {
/*   Parameters: <nickname> <channel>	*/
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string nickname = getArgs()[0];
    std::string channelName = getArgs()[1];

    Channel *channel = this->_server.getChannel(channelName);
    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }

    if (!channel->isOperator(getClient())) {
        return ERR_CHANOPRIVSNEEDED;
    }

	Client *client = this->_server.getClientByNickname(nickname);
	if (!client) {
    	return ERR_NOSUCHNICK;
    }

	if (channel->isClientPresent(*client)) {
        return ERR_USERONCHANNEL;
    }

	channel->inviteUser(*client);
	
    std::string inviteMessage =	":" + this->_client.getNicknameOrUsername(true) +
                        		" " + this->_name +
								" " + nickname +
								" " + channelName;
								
	channel->sendMessageToAll(inviteMessage);
	this->_server.sendMessage(*client, inviteMessage);

    return ERR_NONE;
}
