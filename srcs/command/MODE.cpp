/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:18 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/12/02 02:36:43 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

void Command::MODE() {
  /* Parameters: <channel> <+/-modes> [parameters] */
  if (this->_args.size() < 1) {
    this->_server.getServerReply()->NEEDMOREPARAMS(*this, this->_client);
    return;
  }

  /* User mode not supported */
  if (this->_server.getClientByNickname(this->_args[0])) {
    return;
  }

  this->_targetChannelName = this->_args[0];
  this->_targetChannel = this->_server.getChannel(this->_targetChannelName);
  if (!this->_targetChannel) {
    this->_server.getServerReply()->NOSUCHCHANNEL(*this, this->_client);
    return;
  }
  if (this->_args.size() == 1) {
    this->_server.getServerReply()->RPL_CHANNELMODEIS(*this, this->_client);
    return;
  }
  if (!this->_targetChannel->isOperator(&this->_client)) {
    this->_server.getServerReply()->CHANOPRIVSNEEDED(*this, this->_client);
    return;
  }

  this->_modeStr = this->_args[1];
  /* Ban list not supported */
  if (this->_modeStr == "b") {
	this->_server.getServerReply()->RPL_ENDOFBANLIST(*this, this->_client);
	return;
  }
  if (!isValidMode(this->_modeStr)) {
    this->_server.getServerReply()->UMODEUNKNOWNFLAG(*this, this->_client);
    return;
  }
  if (!isRecognizedMode(this->_modeStr)) {
    this->_server.getServerReply()->UNKNOWNMODE(*this, this->_client);
    return;
  }

  for (std::vector<std::string>::const_iterator it = this->_args.begin() + 2;
       it != this->_args.end(); ++it) {
    this->_modeArgs.push_back(*it);
  }

  size_t i = 0;
  char s = this->_modeStr[0];
  for (std::string::const_iterator it = this->_modeStr.begin() + 1;
       it != this->_modeStr.end(); ++it) {
    switch (*it) {
      case 'i':
        /* Set/unset the channel on invitation only */
        this->_targetChannel->setInviteOnly(s == '+');
        break;
      case 't':
        /*  Set/unset restrictions on the TOPIC command for channel operators */
        this->_targetChannel->setTopicRestricted(s == '+');
        break;
      case 'k':
        /* Set/unset the channel key (password) */
        if (s == '+') {
          if (i >= this->_modeArgs.size()) {
            this->_server.getServerReply()->NEEDMOREPARAMS(*this,
                                                           this->_client);
            return;
          }
          this->_targetChannel->setKey(this->_modeArgs[i]);
          ++i;
        } else {
          this->_targetChannel->setKey("");
        }
        break;
      case 'o': {
        /* Give/take operator privilege from a user */
        if (i >= this->_modeArgs.size()) {
          this->_server.getServerReply()->NEEDMOREPARAMS(*this, this->_client);
          return;
        }
        this->_nick = this->_modeArgs[i];
        this->_targetClient = this->_server.getClientByNickname(this->_nick);
        ++i;
        if (!this->_targetClient) {
          this->_server.getServerReply()->NOSUCHNICK(*this, this->_client);
          return;
        }
        this->_targetChannel->addUser(this->_targetClient, s == '+');
        break;
      }
      case 'l':
        /* Set/unset the limit of users for the channel */
        if (s == '+') {
          if (i >= this->_modeArgs.size()) {
            this->_server.getServerReply()->NEEDMOREPARAMS(*this,
                                                           this->_client);
            return;
          }
          int userLimit = convertToInt(this->_modeArgs[i]);
          if (userLimit == -1) {
			this->_modeArgs[i] = "none";
		  }
          this->_targetChannel->setUserLimit(userLimit);
          ++i;
        } else {
          this->_targetChannel->setUserLimit(-1);
        }
        break;
      default:
        this->_server.getServerReply()->UNKNOWNMODE(*this, this->_client);
        return;
    }
  }

  this->_targetChannel->updateModeInfo(this->_modeStr, this->_modeArgs);

  this->_server.getServerReply()->MODE(*this, this->_client);
  this->_server.getServerReply()->MODE(*this, *this->_targetChannel);
}
