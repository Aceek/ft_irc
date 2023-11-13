/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:12 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 09:28:20 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

static bool isValidParams(Command const &cmd) {
    return cmd.getArgs().size() > 1;
}

static void sendKickMessage(Command const &cmd, Channel const *channel, 
	std::string const &channelName, std::string const&nickname) {
    std::string kickMessage = ":" + cmd.getClient().getNicknameOrUsername(true) +
                              	" " + cmd.getName() +
                              	" " + channelName;
								" " + nickname;
								
	if (!cmd.getTrailor().empty()) {
    	kickMessage += " :" + cmd.getTrailor();
	}

    channel->sendMessageToAll(kickMessage);
}

int Command::KICK() {
/*   Parameters: <channel> <user> [<comment>]	*/
    if (!isValidParams(*this)) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string channelName = this->_args[0];
    std::string nickname = this->_args[1];

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

	channel->delUser(*client);
    
	sendKickMessage(*this, channel, channelName, nickname);

    return ERR_NONE;
}
