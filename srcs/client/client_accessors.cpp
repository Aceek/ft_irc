/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_accessors.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:25:35 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/12/04 03:42:09 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/client/client.hpp"

int Client::getClientFd() const { return (this->_clientFd); }

const std::string &Client::getClientCommand() const { return (this->_command); }

const std::string &Client::getNicknameOrUsername(bool useNickname) const {
  if (useNickname) {
    return (this->_nickname);
  } else {
    return (this->_username);
  }
}

const std::time_t &Client::getLastActivityTime() const {
  return (this->_lastActivityTime);
}

const struct sockaddr_in &Client::getClientAddress() const {
  return (this->_clientAdress);
}

void Client::setLastActivityTime() {
  this->_lastActivityTime = std::time(NULL);
}

void Client::setNickname(std::string const &nickname) {
  this->_nickname = nickname;
}

void Client::setUsername(std::string const &username) {
  this->_username = username;
}

void Client::setRealName(std::string const &realName) {
  this->_realName = realName;
}

void Client::setPassRegister() { this->_passRegister = true; }

void Client::setUserRegister() { this->_userRegister = true; }

void Client::setNickRegister() { this->_nickRegister = true; }

std::string Client::getPrefix(void) const {
  std::string prefix = this->_nickname;
  if (!this->_username.empty()) prefix += "!" + this->_username;

  return prefix + "@" + this->_hostname;
}

std::string const &Client::getHostname(void) const { return this->_hostname; }

std::set<Channel *> const &Client::getChannels(void) const {
  return this->_channels;
}
