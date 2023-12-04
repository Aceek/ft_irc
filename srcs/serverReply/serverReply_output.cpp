/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReply_output.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 08:55:40 by ilinhard          #+#    #+#             */
/*   Updated: 2023/12/04 04:55:56 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/serverReply/serverReply.hpp"

void serverReply::printServerInput(const std::string &message) const {
  std::cout << message << std::endl;
}

void serverReply::displayClientCommand(const std::string &command,
                                       const Client &client) const {
  const std::string RED = "\033[31m";
  const std::string GREEN = "\033[32m";
  const std::string RESET = "\033[0m";
  std::string nickName = client.getNicknameOrUsername(true);
  if (nickName.empty()) {
    std::ostringstream ss;
    ss << client.getClientFd();
    nickName = ss.str();
  }

  std::cout << GREEN << "Command from [" << nickName << "]: " << RED << command
            << RESET << std::endl;
}

void serverReply::setMessageQueue(const int clientfd,
                                  const std::string &message) {
  this->_messageQueue[clientfd].push_back(message);
}

messages &serverReply::getMessageQueue() { return (this->_messageQueue); }

bool serverReply::verifyMessageSend(const int clientFd) {
  std::deque<std::string> &messages = this->_messageQueue[clientFd];
  for (std::deque<std::string>::iterator msgIt = messages.begin();
       msgIt != this->_messageQueue[clientFd].end(); msgIt++) {
    if (!sendMessage(clientFd, *msgIt)) {
      messages.clear();
      return (false);
    }
  }
  messages.clear();
  return (true);
}

bool serverReply::sendMessage(const int clientFd,
                              const std::string &message) const {
  std::string newMessage = message + "\n";
  int bytesSent = send(clientFd, newMessage.c_str(), newMessage.size(), 0);

  if (bytesSent == -1 && errno != EINTR && errno != EAGAIN) {
    displayServerMessage(ERR_SEND);
    return (false);
  }
  return (true);
}

void serverReply::displayServerMessage(messageServer event) const {
  std::string error = strerror(errno);
  switch (event) {
    case SERVER_CLOSING:
      std::cout << "Server is closing." << std::endl;
      break;
    case SERVER_DELCLIENT:
      std::cout << "Client has been removed from the server." << std::endl;
      std::cout << this->_server.getNumbersClients() << " Clients sur le server"
                << std::endl;
      break;
    case ERR_SERVER_ACCEPTCLIENT:
      std::cerr << "Error occurred while accepting a new client." << std::endl;
      break;
    case SERVER_NEWCLIENT:
      std::cout << "A new client has connected to the server." << std::endl;
      std::cout << this->_server.getNumbersClients() << " Clients sur le server"
                << std::endl;
      break;
    case ERR_BIND:
      std::cerr << "Error occurred during binding the socket. Details: " + error
                << std::endl;
      break;
    case ERR_POLL:
      std::cerr << "Poll function failed with an error. Details: " + error
                << std::endl;
      break;
    case ERR_SEND:
      std::cerr << "Failed to send data through the socket. Details: " + error
                << std::endl;
      break;
    case ERR_SOCKET:
      std::cerr << "Failed to create Socket Details: " + error << std::endl;
      break;
    case ERR_LISTEN:
      std::cerr << "Failed to listen Socket Details: " + error << std::endl;
      break;
    case TIMOUT_CLIENT:
      std::cerr << "Client TIMEOUT ... deconection"<< std::endl;
      break;
    case ERR_OPEN_FD:
      std::cerr << "Error occurred while opening the file descriptor for the "
                   "client. Details: " +
                       error
                << std::endl;
      break;
    case ERR_FCNTL:
      std::cerr << "Error using fcntl function. Details: " + error << std::endl;
      break;
    case ERR_CLOSE_FD:
      std::cerr
          << "Error occurred while closing the file descriptor. Details: " +
                 error
          << std::endl;
      break;
    case MAX_CLIENTS:
      std::cout << "Can't accept this client, max number of client already rich"
                << std::endl;
      break;
    default:
      std::cout << "Unknown server event." << std::endl;
  }
}

void serverReply::sendMessageToChannel(Client const &sender,
                                       Channel const &channel,
                                       std::string const &message) {
  if (!this->_server.isChannelPresent(channel.getName()) || message.empty()) {
    return;
  }

  for (std::set<Client *>::iterator it = channel.getUsers().begin();
       it != channel.getUsers().end(); ++it) {
    if (*it != &sender) {
      setMessageQueue((*it)->getClientFd(), message);
    }
  }
  for (std::set<Client *>::iterator it = channel.getOperators().begin();
       it != channel.getOperators().end(); ++it) {
    if (*it != &sender) {
      setMessageQueue((*it)->getClientFd(), message);
    }
  }
}
