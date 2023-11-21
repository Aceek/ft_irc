/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:47:58 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/21 16:04:46 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::INVITE() {
/*   Parameters: <nickname> <channel>	*/
	if (this->_args.size() < 2) {
		return ERR_NEEDMOREPARAMS;
	}

	this->_targetChannel = this->_server.getChannel(this->_args[1]);
	if (!this->_targetChannel) {
		return ERR_NOSUCHCHANNEL;
	}
	if (!this->_targetChannel->isClientPresent(this->_client)) {
		return ERR_NOTONCHANNEL;
	}
	if (!checkInviteOnlyAndNotOperator(this->_targetChannel)) {
		return ERR_CHANOPRIVSNEEDED;
	}
	
	this->_targetClient = this->_server.getClientByNickname(this->_args[0]);
	if (!this->_targetClient) {
		return ERR_NOSUCHNICK;
	}
	if (this->_targetChannel->isClientPresent(*this->_targetClient)) {
		return ERR_USERONCHANNEL;
	}

	this->_targetChannel->inviteUser(*this->_targetClient);
	
	//RPL_INVITING 341???
	this->_server.getServerReply()->INVITE(*this, *this->_targetClient);
	this->_server.getServerReply()->INVITE(*this, *this->_targetChannel);

	return ERR_NONE;
}