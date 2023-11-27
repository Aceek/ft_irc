/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:47:58 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/27 21:04:47 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

void Command::INVITE() {
  /* Parameters: <nickname> <channel> */
  if (this->_args.size() < 2) {
    this->_server.getServerReply()->NEEDMOREPARAMS(*this, this->_client);
    return;
  }

  this->_targetChannelName = this->_args[1];
  this->_targetChannel = this->_server.getChannel(this->_targetChannelName);
  if (!this->_targetChannel) {
    this->_server.getServerReply()->NOSUCHCHANNEL(*this, this->_client);
    return;
  }
  if (!this->_targetChannel->isClientPresent(&this->_client)) {
    this->_server.getServerReply()->NOTONCHANNEL(*this, this->_client);
    return;
  }
  if (checkInviteOnlyAndNotOperator(this->_targetChannel)) {
    this->_server.getServerReply()->CHANOPRIVSNEEDED(*this, this->_client);
    return;
  }

  this->_nick = this->_args[0];
  this->_targetClient = this->_server.getClientByNickname(this->_nick);
  if (!this->_targetClient) {
    this->_server.getServerReply()->NOSUCHNICK(*this, this->_client);
    return;
  }
  if (this->_targetChannel->isClientPresent(this->_targetClient)) {
    this->_server.getServerReply()->USERONCHANNEL(*this, this->_client);
    return;
  }

  this->_targetChannel->inviteUser(this->_targetClient);

  this->_server.getServerReply()->RPL_INVITING(*this, this->_client);
  this->_server.getServerReply()->INVITE(*this, *this->_targetClient);
}
