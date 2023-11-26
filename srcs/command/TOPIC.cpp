/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/26 04:01:13 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::TOPIC() {
	/* Parameters: <channel> [<topic>] */
	if (this->_args.size() < 1) {
		this->_server.getServerReply()->NEEDMOREPARAMS(*this, this->_client);
		return ERR_NEEDMOREPARAMS;
	}

	this->_targetChannelName = this->_args[0];
	this->_targetChannel = this->_server.getChannel(this->_targetChannelName);
	if (!this->_targetChannel) {
		this->_server.getServerReply()->NOSUCHCHANNEL(*this, this->_client);
		return ERR_NOSUCHCHANNEL;
	}
	if (!this->_targetChannel->isClientPresent(this->_client)) {
		this->_server.getServerReply()->NOTONCHANNEL(*this, this->_client);
		return ERR_NOTONCHANNEL;
	}
	if (!checkTopicRestriction(this->_targetChannel)) {
		this->_server.getServerReply()->CHANOPRIVSNEEDED(*this, this->_client);
		return ERR_CHANOPRIVSNEEDED;
	}

	if (this->_trailor.empty()) {
		if (!this->_targetChannel->getTopic().empty()) {
			this->_server.getServerReply()->RPL_TOPIC(*this, this->_client);
		} else {
			this->_server.getServerReply()->RPL_NOTOPIC(*this, this->_client);
		}
	} else {
		if (this->_trailor[0] == ':' && this->_trailor[1] == '\0') {
			this->_topic = "";
		} else {
			this->_topic = this->_trailor;
		}
		this->_targetChannel->setTopic(this->_topic);

		this->_server.getServerReply()->TOPIC(*this, this->_client);
		this->_server.getServerReply()->TOPIC(*this, *this->_targetChannel);
	}

	return ERR_NONE;
}
