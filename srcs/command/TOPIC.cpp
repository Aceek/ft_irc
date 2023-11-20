/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/20 15:13:18 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::TOPIC() {
    /* Parameters: <channel> [<topic>] */
    if (this->_args.size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string	const	&channelName = this->_args[0];
    Channel				*channel = this->_server.getChannel(channelName);
    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }
    if (!channel->isClientPresent(this->_client)) {
        return ERR_NOTONCHANNEL;
    }
	if (!checkTopicRestriction(channel)) {
		return ERR_CHANOPRIVSNEEDED;
	}

	if (this->_trailor.empty()) {
		// this->_server.RPL_TOPIC(*channel, this->_client);
	} else {
        std::string	const	&newTopic = this->_trailor;
        channel->setTopic(newTopic);

		//to be rework with formated server response
		std::string topicMessage = ":" + this->_client.getNicknameOrUsername(true) +
                                   " " + this->_name +
								   " " + channelName + 
								   " :" + newTopic;
       
		this->_server.sendMessageToChannel(*channel, topicMessage);
    }

    return ERR_NONE;
}
