/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:38 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/27 21:08:30 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

void Command::PART() {
  /* Parameters: <channel>{,<channel>} [<reason>] */
  if (this->_args.size() < 1) {
    this->_server.getServerReply()->NEEDMOREPARAMS(*this, this->_client);
    return;
  }

  std::vector<std::string> channels = ft_split(this->_args[0], ",");
  for (std::vector<std::string>::const_iterator it = channels.begin();
       it != channels.end(); ++it) {
    this->_targetChannelName = *it;
    this->_targetChannel = this->_server.getChannel(this->_targetChannelName);
    if (!this->_targetChannel) {
      this->_server.getServerReply()->NOSUCHCHANNEL(*this, this->_client);
      return;
    }
    if (!this->_targetChannel->isClientPresent(&this->_client)) {
      this->_server.getServerReply()->NOTONCHANNEL(*this, this->_client);
      return;
    }

    this->_server.getServerReply()->PART(*this, this->_client);

    this->_targetChannel->delUser(&this->_client);

    if (this->_targetChannel->getCount() < 1) {
      this->_server.delChannel((*it));
    } else {
      this->_server.getServerReply()->PART(*this, *this->_targetChannel);
    }
  }
}
