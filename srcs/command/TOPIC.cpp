/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/20 16:43:48 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::TOPIC() {
    /* Parameters: <channel> [<topic>] */
    if (this->_args.size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    this->_targetChannel = this->_server.getChannel(this->_args[0]);
    if (!this->_targetChannel) {
        return ERR_NOSUCHCHANNEL;
    }
    if (!this->_targetChannel->isClientPresent(this->_client)) {
        return ERR_NOTONCHANNEL;
    }
	if (!checkTopicRestriction(this->_targetChannel)) {
		return ERR_CHANOPRIVSNEEDED;
	}

	if (this->_trailor.empty()) {
		// this->_server.RPL_TOPIC(*channel, this->_client);
	} else {
        this->_targetChannel->setTopic(this->_trailor);

		//to be rework with formated server response
		//should we send RPL_TOPIC ?
		this->_server.getServerReply()->TOPIC(*this, *this->_targetChannel);
	}

    return ERR_NONE;
}
