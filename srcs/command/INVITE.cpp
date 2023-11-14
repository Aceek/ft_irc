/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:47:58 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/14 01:14:35 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

// static void sendInviteMessage(Command const &cmd, Channel const *channel, 
// 	std::string const &channelName, std::string const&nickname, Client const &client) {
//     std::string inviteMessage = ":" + cmd.getClient().getNicknameOrUsername(true) +
//                               	" " + cmd.getName() +
// 								" " + nickname +
//                               	" " + channelName;

//     channel->sendMessageToAll(inviteMessage);
	
// 	cmd.getServer().setMessageQueue(client.getClientFd(), inviteMessage);
// }

int Command::INVITE() {
/*   Parameters: <nickname> <channel>	*/
    if (this->getArgs().size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string channelName = this->_args[1];
    Channel *channel = this->_server.getChannel(channelName);
    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }
	if (!channel->isClientPresent(this->_client)) {
        return ERR_NOTONCHANNEL;
    }
    if (!channel->isOperator(getClient())) {
        return ERR_CHANOPRIVSNEEDED;
    }
	
    std::string nickname = this->_args[0];
	Client *client = this->_server.getClientByNickname(nickname);
	if (!client) {
    	return ERR_NOSUCHNICK;
    }
	if (channel->isClientPresent(*client)) {
        return ERR_USERONCHANNEL;
    }

	channel->inviteUser(*client);
	
	//to be rework with formated server response
    std::string inviteMessage = ":" + this->_client.getNicknameOrUsername(true) +
                              	" " + this->_name +
								" " + nickname +
                              	" " + channelName;

	this->_server.sendMessageToChannel(*channel, inviteMessage);
	this->_server.setMessageQueue(client->getClientFd(), inviteMessage);

    return ERR_NONE;
}