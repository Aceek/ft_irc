/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:18 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/27 21:16:06 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

void Command::MODE() {
  /* Parameters: <channel> <+/-modes> [parameters] */
  if (this->_args.size() < 2) {
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
  if (!this->_targetChannel->isOperator(&this->_client)) {
    this->_server.getServerReply()->CHANOPRIVSNEEDED(*this, this->_client);
    return;
  }

  this->_modeSet = this->_args[1];
  if (!isValidMode(this->_modeSet)) {
    this->_server.getServerReply()->UMODEUNKNOWNFLAG(*this, this->_client);
    return;
  }
  if (!isRecognizedMode(this->_modeSet)) {
    this->_server.getServerReply()->UNKNOWNMODE(*this, this->_client);
    return;
  }

  for (std::vector<std::string>::const_iterator it = this->_args.begin() + 2;
       it != this->_args.end(); ++it) {
    this->_modeArgs.push_back(*it);
  }

  size_t i = 0;
  char s = this->_modeSet[0];
  for (std::string::const_iterator it = this->_modeSet.begin();
       it != this->_modeSet.end(); ++it) {
    switch (*it) {
      case '+':
        s = '+';
        break;
      case '-':
        s = '-';
        break;
      case 'i':
        // Set/unset the channel on invitation only
        this->_targetChannel->setInviteOnly(s == '+');
        break;
      case 't':
        // Set/unset restrictions on the TOPIC command for channel operators
        this->_targetChannel->setTopicRestricted(s == '+');
        break;
      case 'k':
        // Set/unset the channel key (password)
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
        // Give/take operator privilege from a user
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
        // Set/unset the limit of users for the channel
        if (s == '+') {
          if (i >= this->_modeArgs.size()) {
            this->_server.getServerReply()->NEEDMOREPARAMS(*this,
                                                           this->_client);
            return;
          }
          this->_targetChannel->setUserLimit(atoi(this->_modeArgs[i].c_str()));
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

  this->_server.getServerReply()->MODE(*this, this->_client);
  this->_server.getServerReply()->MODE(*this, *this->_targetChannel);
}
