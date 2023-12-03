/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utlis.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:21:08 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/12/03 23:51:45 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/server/server.hpp"

bool Server::isChannelPresent(std::string const &channelName) {
  const ChannelMap::iterator it = this->_channels.find(channelName);

  if (it != this->_channels.end()) {
    return true;
  }

  return false;
}

void Server::closingFdClients() {
  ClientMap::iterator it = this->_clients.begin();
  for (; it != this->_clients.end(); it++) {
    if (close(it->second.getClientFd()) == -1) {
      this->_serverReply->displayServerMessage(ERR_OPEN_FD);
    }
  }
}

void Server::removeClient(const int clientFd) {
  // Suppression client dans pollfd
  std::vector<pollfd>::iterator itPoll = this->_fds.begin();
  while (itPoll != _fds.end()) {
    if (itPoll->fd == clientFd) {
      itPoll = this->_fds.erase(itPoll);
    } else {
      itPoll++;
    }
  }

  // Suppression des client dans les channels
  Client &client = this->_clients.find(clientFd)->second;
  ChannelMap::iterator chanIt = getChannels().begin();
  for (; chanIt != getChannels().end(); chanIt++) {
    if (chanIt->second.isClientPresent(&client)) {
      chanIt->second.delUser(&client);
    }
  }

  // Suppression client dans map client
  ClientMap::iterator itClient = this->_clients.find(clientFd);
  if (itClient != this->_clients.end()) {
    this->_clients.erase(clientFd);
  }

  // Suppression des clients dans la liste des messages
  messages &messages = this->_serverReply->getMessageQueue();
  std::map<int, std::deque<std::string> >::iterator itMsg =
      messages.find(clientFd);
  if (itMsg != messages.end()) {
    messages.erase(clientFd);
  }

  shutdown(clientFd, SHUT_WR);  // new
  if (close(clientFd) == -1) {
    this->_serverReply->displayServerMessage(ERR_CLOSE_FD);
  }

  this->_serverReply->displayServerMessage(SERVER_DELCLIENT);
}

void Server::deconectionClients() {
  std::vector<struct pollfd>::iterator fdsIt = this->_fds.begin();
  for (; fdsIt != this->_fds.end(); fdsIt++) {
    if (fdsIt->revents == POLLOUT) {
      this->_serverReply->LOGOUT(this->_clients.find(fdsIt->fd)->second);
    }
  }
}

void Server::addToPoll(int fd, short events) {
  // Push info about fd / event / revent into vector struct fds;
  struct pollfd tmpFd;
  tmpFd.events = events;
  tmpFd.fd = fd;
  tmpFd.revents = 0;
  this->_fds.push_back(tmpFd);
}

void Server::removeClients() {
  for (size_t i = 0; i < this->_clientsToRemove.size(); i++) {
    removeClient(this->_clientsToRemove[i]);
  }
  this->_clientsToRemove.clear();
}

void Server::addChannel(std::string const &channelName) {
  Channel &newChannel = this->_channels[channelName];
  newChannel.init(channelName, this);
}

void Server::delChannel(std::string const &channelName) {
  ChannelMap::iterator it = this->_channels.find(channelName);
  if (it != this->_channels.end()) {
    this->_channels.erase(it);
  }
}

void Server::addClientsToPoll() {
  for (std::vector<int>::iterator it = this->_clientsToAdd.begin();
       it != this->_clientsToAdd.end(); it++) {
    addToPoll(*it, POLLIN | POLLOUT | POLLERR | POLLHUP | POLLNVAL);
  }
  this->_clientsToAdd.clear();
}

void Server::verifyMaxClient(const int clientFdToRemove) {
  std::vector<int>::iterator it = std::find(
      _clientFdToRemove.begin(), _clientFdToRemove.end(), clientFdToRemove);
  if (it != _clientFdToRemove.end()) {
    setClientToRemove(clientFdToRemove);
	this->_clientFdToRemove.erase(it);
  }
}
