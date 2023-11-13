/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:47:58 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 11:12:01 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

static bool isValidParams(Command const &cmd) {
    return cmd.getArgs().size() > 1;
}

static void sendInviteMessage(Command const &cmd, Channel const *channel, 
	std::string const &channelName, std::string const&nickname, Client const &client) {
    std::string inviteMessage = ":" + cmd.getClient().getNicknameOrUsername(true) +
                              	" " + cmd.getName() +
								" " + nickname +
                              	" " + channelName;

    channel->sendMessageToAll(inviteMessage);
	
	cmd.getServer().setMessageQueue(client.getClientFd(), inviteMessage);
}

int Command::INVITE() {
/*   Parameters: <nickname> <channel>	*/
    if (!isValidParams(*this)) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string nickname = this->_args[0];
    std::string channelName = this->_args[1];

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
	
	//to be rework with formated server response
	sendInviteMessage(*this, channel, channelName, nickname, *client);

    return ERR_NONE;
}