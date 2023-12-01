
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:51 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 04:07:58 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

void Command::PRIVMSG() {
  /* Parameters: <receiver>{,<receiver>} <text to be sent> */
  if (this->_args.size() < 1) {
    this->_server.getServerReply()->NEEDMOREPARAMS(*this, this->_client);
    return;
  }
  if (this->_trailor.empty()) {
    this->_server.getServerReply()->NOTEXTTOSEND(*this, this->_client);
    return;
  }
  
  std::vector<std::string> receivers = ft_split(this->_args[0], ",");
  for (std::vector<std::string>::iterator it = receivers.begin();
       it != receivers.end(); ++it) {
    this->_targetChannelName = *it;
    if (isValidChannelName(this->_targetChannelName)) {
      this->_targetChannel = this->_server.getChannel(this->_targetChannelName);
      if (!this->_targetChannel) {
        this->_server.getServerReply()->NOSUCHCHANNEL(*this, this->_client);
        continue;
      }
      if (!this->_targetChannel->isClientPresent(&this->_client)) {
        this->_server.getServerReply()->NOTONCHANNEL(*this, this->_client);
        continue;
      }
      if (botMessageCheck(*this)) {
      	continue;
      }

      this->_server.getServerReply()->PRIVMSG(*this, *this->_targetChannel);
    } else {
      this->_nick = *it;
      this->_targetClient = this->_server.getClientByNickname(this->_nick);
      if (!this->_targetClient) {
        this->_server.getServerReply()->NOSUCHNICK(*this, this->_client);
        continue;
      }

      this->_server.getServerReply()->PRIVMSG(*this, *this->_targetClient);
    }
  }
}
