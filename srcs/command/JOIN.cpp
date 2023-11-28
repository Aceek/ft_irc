/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:07 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/28 03:56:41 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

void Command::JOIN() {
  /* Parameters: <channel>{,<channel>} [<key>{,<key>}] */
  if (this->_args.size() < 1) {
    this->_server.getServerReply()->NEEDMOREPARAMS(*this, this->_client);
    return;
  }

  std::vector<std::string> channels = ft_split(this->_args[0], ",");
  std::vector<std::string> keys = (this->_args.size() > 1)
                                      ? ft_split(this->_args[1], ",")
                                      : std::vector<std::string>();

  for (size_t i = 0; i < channels.size(); ++i) {
    this->_targetChannelName = channels[i];
    if (!isValidChannelName(this->_targetChannelName)) {
      this->_server.getServerReply()->BADCHANMASK(*this, this->_client);
      continue;  // Remplacez "return" par "continue" pour passer au canal
                 // suivant
    }

    std::string key = (i < keys.size()) ? keys[i] : "";
    this->_targetChannel = getOrCreateChannel(this->_targetChannelName, key);
    if (!isValidChannelKey(this->_targetChannel, key)) {
      this->_server.getServerReply()->BADCHANNELKEY(*this, this->_client);
      continue;
    }
    if (checkInviteOnlyAndNotInvited(this->_targetChannel)) {
      this->_server.getServerReply()->INVITEONLYCHAN(*this, this->_client);
      continue;
    }
    if (checkChannelFull(this->_targetChannel)) {
      this->_server.getServerReply()->CHANNELISFULL(*this, this->_client);
      continue;
    }

    addUserToChannel(this->_targetChannel);

    this->_server.getServerReply()->JOIN(*this, this->_client);
    this->_server.getServerReply()->JOIN(*this, *this->_targetChannel);

    if (!this->_targetChannel->getTopic().empty()) {
      this->_server.getServerReply()->RPL_TOPIC(*this, this->_client);
    }
	if (!this->_targetChannel->getModeArgs().empty()) {
      this->_server.getServerReply()->RPL_CHANNELMODEIS(*this, this->_client);
    }
    this->_server.getServerReply()->RPL_NAMREPLY(*this, this->_client);
    this->_server.getServerReply()->RPL_ENDOFNAMES(*this, this->_client);
  }
}
