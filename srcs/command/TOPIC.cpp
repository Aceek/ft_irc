/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 04:07:30 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::TOPIC() {
    /* Parameters: <channel> [<topic>] */
    if (this->_args.size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string channelName = this->_args[0];
    Channel *channel = this->_server.getChannel(channelName);

    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }

    if (!channel->isClientPresent(this->_client)) {
        return ERR_NOTONCHANNEL;
    }

	if (channel->getTopicRestricted() && !channel->isOperator(this->_client)) {
		return ERR_CHANOPRIVSNEEDED;
	}

	if (this->_trailor.empty()) {
		if (channel->getTopic().empty()) {
			channel->RPL_NOTOPIC(this->_client);
		} else {
			channel->RPL_TOPIC(this->_client);
		}
	} else {
        std::string newTopic = this->_trailor;
        channel->setTopic(newTopic);

        std::string topicMessage = ":" + this->_client.getNicknameOrUsername(true) +
                                   " " + this->_name +
								   " " + channelName + 
								   " :" + newTopic;
       
	    channel->sendMessageToAll(topicMessage);
    }

    return ERR_NONE;
}
