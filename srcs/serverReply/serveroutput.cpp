/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveroutput.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 08:55:40 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/26 04:26:30 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverReply.hpp"


void	serverReply::printServerInput(const std::string &message) const {
	std::cout << message << std::endl;
}


void serverReply::displayClientCommand(const std::string& command, const Client& client) const {
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string RESET = "\033[0m";
	std::string nickName = client.getNicknameOrUsername(true);
	if (nickName.empty()) {
		std::ostringstream ss;
		ss << client.getClientFd();
		nickName = ss.str();
	}

    std::cout << GREEN << "Command from [" << nickName << "]: " 
              << RED << command << RESET << std::endl;
}

void serverReply::setMessageQueue(const int clientfd, const std::string &message) {
	this->_messageQueue[clientfd].push_back(message);
}

messages &serverReply::getMessageQueue() {
	return (this->_messageQueue);
}

void serverReply::verifyMessageSend(const int clientFd) {
	
	std::deque<std::string>& messages = this->_messageQueue[clientFd];
	for (std::deque<std::string>::iterator msgIt = messages.begin();
	msgIt != this->_messageQueue[clientFd].end(); msgIt++) {
		sendMessage(clientFd, *msgIt);
	}
	messages.clear();
}

void serverReply::sendMessage(const int clientFd, const std::string &message) const {
	std::string newMessage = message + "\n";
	int bytesSent = send(clientFd, newMessage.c_str(), newMessage.size(), 0);

	if (bytesSent == -1) {
		displayServerMessage(ERR_SEND);

	}
}

void serverReply::displayServerMessage(messageServer event) const {
	std::string error = strerror(errno);
    switch (event) {
        case SERVER_CLOSING:
            std::cout << "Server is closing." << std::endl;
            break;
        case SERVER_DELCLIENT:
            std::cout << "Client has been removed from the server." << std::endl;
            break;
        case ERR_SERVER_ACCEPTCLIENT:
            std::cerr << "Error occurred while accepting a new client." << std::endl;
            break;
        case SERVER_NEWCLIENT:
            std::cout << "A new client has connected to the server." << std::endl;
            break;
      case ERR_BIND:
            std::cerr << "Error occurred during binding the socket. Details: " + error << std::endl;
            break;
        case ERR_POLL:
            std::cerr << "Poll function failed with an error. Details: " + error << std::endl;
            break;
        case ERR_SEND:
            std::cerr << "Failed to send data through the socket. Details: " + error << std::endl;
            break;
    case ERR_OPEN_FD:
        std::cout << "Error occurred while opening the file descriptor for the client. Details: " + error << std::endl;
        break;
        default:
            std::cout << "Unknown server event." << std::endl;
    }
}
