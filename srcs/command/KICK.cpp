/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:12 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/27 21:05:48 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

void Command::KICK() {
  /* Parameters: <channel> <user> [<comment>] */
  if (this->_args.size() < 2) {
    this->_server.getServerReply()->NEEDMOREPARAMS(*this, this->_client);
    return;
  }

  this->_targetChannelName = this->_args[0];
  this->_targetChannel = this->_server.getChannel(this->_targetChannelName);
  if (!this->_targetChannel) {
    this->_server.getServerReply()->NOSUCHCHANNEL(*this, this->_client);
    return;
  }
  if (!this->_targetChannel->isClientPresent(&this->_client)) {
    this->_server.getServerReply()->NOTONCHANNEL(*this, this->_client);
    return;
  }
  if (!this->_targetChannel->isOperator(&this->_client)) {
    this->_server.getServerReply()->CHANOPRIVSNEEDED(*this, this->_client);
    return;
  }

  this->_nick = this->_args[1];
  this->_targetClient = this->_server.getClientByNickname(this->_nick);
  if (!this->_targetClient) {
    this->_server.getServerReply()->NOSUCHNICK(*this, this->_client);
    return;
  }
  if (!this->_targetChannel->isClientPresent(this->_targetClient)) {
    this->_server.getServerReply()->USERNOTINCHANNEL(*this, this->_client);
    return;
  }

  this->_server.getServerReply()->KICK(*this, this->_client);
  this->_server.getServerReply()->KICK(*this, *this->_targetChannel);

  this->_targetChannel->delUser(this->_targetClient);
}
