/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:09:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/28 23:46:18 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "srcs/channel/channel.hpp"

Channel::Channel(void)
    : _name(""),
      _topic(""),
      _key(""),
      _inviteOnly(false),
      _topicRestricted(false),
      _userLimit(-1),
      _modeStr(""),
      _modeArgs(""),
      _modeInfo(),
      _server(NULL) {}

Channel::Channel(std::string const &name, Server *server)
    : _name(name),
      _topic(""),
      _key(""),
      _inviteOnly(false),
      _topicRestricted(false),
      _userLimit(-1),
      _modeStr(""),
      _modeArgs(""),
      _modeInfo(),
      _server(server) {}

Channel::Channel(Channel const &rhs)
    : _name(rhs._name),
      _topic(rhs._topic),
      _key(rhs._key),
      _inviteOnly(rhs._inviteOnly),
      _topicRestricted(rhs._topicRestricted),
      _userLimit(rhs._userLimit),
      _modeStr(rhs._modeStr),
      _modeArgs(rhs._modeArgs),
      _modeInfo(rhs._modeInfo),
      _users(rhs._users),
      _invitedUsers(rhs._invitedUsers),
      _operators(rhs._operators),
      _server(rhs._server) {}

Channel &Channel::operator=(Channel const &rhs) {
  if (this == &rhs) {
    return *this;
  }

  this->_name = rhs._name;
  this->_topic = rhs._topic;
  this->_key = rhs._key;
  this->_inviteOnly = rhs._inviteOnly;
  this->_topicRestricted = rhs._topicRestricted;
  this->_userLimit = rhs._userLimit;
  this->_modeStr = rhs._modeStr;
  this->_modeArgs = rhs._modeArgs;
  this->_modeInfo = rhs._modeInfo;
  this->_users = rhs._users;
  this->_invitedUsers = rhs._invitedUsers;
  this->_operators = rhs._operators;
  this->_server = rhs._server;

  return *this;
}

Channel::~Channel(void) {}

/* ************************************************************************** */

void Channel::addUser(Client *client, bool asOperator) {
  if (asOperator || (this->_users.empty() && this->_operators.empty())) {
    if (this->_operators.insert(client).second) {
      this->_users.erase(client);
    }
  } else {
    if (this->_users.insert(client).second) {
      this->_operators.erase(client);
    }
  }
  this->_invitedUsers.erase(client);
  client->addChannel(this);
}

void Channel::delUser(Client *client) {
  this->_users.erase(client);
  this->_operators.erase(client);
  this->_invitedUsers.erase(client);
  client->delChannel(this);
}

void Channel::inviteUser(Client *client) {
  this->_invitedUsers.insert(client);
}

void Channel::updateModeInfo(const std::string &modeStr,
  const std::vector<std::string> &modeArgs) {
  if (this->_modeStr.empty() && !modeStr.empty() && modeStr[0] == '+') {
    this->_modeStr.push_back('+');
  }

  size_t argIndex = 0; 
  for (std::string::const_iterator it = modeStr.begin() + 1; it != modeStr.end(); ++it) {
    char mode = *it;
    if (mode == 'o') {
      continue;
    }
  
    std::size_t foundPos = this->_modeStr.find(mode);
    if (modeStr[0] == '+') {
      if (foundPos == std::string::npos) {
        this->_modeStr.push_back(mode);
      }
      if (hasModeArgs(mode) && argIndex < modeArgs.size()) {
        this->_modeInfo[mode] = modeArgs[argIndex++];
      }
    } else if (modeStr[0] == '-' && foundPos != std::string::npos) {
      this->_modeStr.erase(foundPos, 1);
      if (this->_modeInfo.find(mode) != this->_modeInfo.end()) {
        this->_modeInfo.erase(mode);
      }
    }
  }

  this->_modeArgs = joinWithSpace(this->_modeInfo);
  if (this->_modeStr.size() == 1) {
    this->_modeStr.clear();
  }
}