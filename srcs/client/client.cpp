/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:40:21 by ilinhard          #+#    #+#             */
/*   Updated: 2023/12/04 05:12:17 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/client/client.hpp"

Client::Client() : _clientFd(), _clientAdress(), _nickname(), _command("") {
  setLastActivityTime();
}
Client::~Client() {}

Client::Client(int fd, const struct sockaddr_in &addr)
    : _clientFd(fd),
      _clientAdress(addr),
      _nickname(""),
      _command(""),
      _username(""),
      _realName(""),
      _hostname("localhost"),
      _passRegister(false),
      _userRegister(false),
      _nickRegister(false) {
  setLastActivityTime();
}

void Client::addToCommand(const std::string &buffer) {
  this->_command += buffer;
}

void Client::clearCommand() { this->_command.clear(); }

bool Client::verifyCommand() {
  if (this->_command.find("\n") == std::string::npos) {
    return (false);
  } else if (this->_command.empty() || this->_command.size() > BUFFER_SIZE) {
    this->_command.clear();
    return (false);
  }

  return (true);
}

void Client::addChannel(Channel *channel) { this->_channels.insert(channel); }

void Client::delChannel(Channel *channel) { this->_channels.erase(channel); }
