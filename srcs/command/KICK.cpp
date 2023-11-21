/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:12 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/21 15:05:38 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::KICK() {
/*   Parameters: <channel> <user> [<comment>]	*/
	if (this->_args.size() < 2) {
		return ERR_NEEDMOREPARAMS;
	}

	this->_targetChannel = this->_server.getChannel(this->_args[0]);
	if (!this->_targetChannel) {
		return ERR_NOSUCHCHANNEL;
	}
	if (!this->_targetChannel->isOperator(this->_client)) {
		return ERR_CHANOPRIVSNEEDED;
	}
   
	this->_targetClient = this->_server.getClientByNickname(this->_args[1]);
	if (!this->_targetClient) {
		return ERR_NOSUCHNICK;
	}
	if (!this->_targetChannel->isClientPresent(*this->_targetClient)) {
		return ERR_NOTONCHANNEL;
	}

	this->_server.getServerReply()->KICK(*this, *this->_targetChannel);
	
	this->_targetChannel->delUser(*this->_targetClient);

	return ERR_NONE;
}
