/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReply_ilan.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:45:40 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/21 01:01:51 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverReply.hpp"

void	serverReply::CAP_RPL(const int clientFd) {
	std::string message = ":localhost CAP * LS :\r\n";
	this->_server.setMessageQueue(clientFd, message);
}


void serverReply::NICK_RPL(const int errorCode, const Client &client) {
    std::string replyMessage;
    std::string hostname = "localhost";

    switch (errorCode) {
        case ERR_NONICKNAMEGIVEN:
            replyMessage = ":" + hostname + " 431 * :No nickname given";
            break;
        case ERR_ERRONEUSNICKNAME:
            replyMessage = ":" + hostname + " 432 * :Erroneous nickname";
            break;
        case ERR_NICKNAMEINUSE:
            replyMessage = ":" + hostname + " 433 * :Nickname is already in use";
            break;
    }
    _server.setMessageQueue(client.getClientFd(), replyMessage);
}


void serverReply::NICK_SUCCES(const Client& client, const std::string &oldNick) {
	int clientFdWhoChange = client.getClientFd();
    std::string hostname = "localhost";
    std::string newNickname = client.getNicknameOrUsername(true);

	std::string username = client.getNicknameOrUsername(false);
	if (username.empty()) {
		username = "user";
	}
	
    std::string message = ":" + oldNick + "!" + 
	username + "@" + hostname + " NICK :" + newNickname;

    std::map<const int, Client> clients = this->_server.getClients();

    std::map<const int, Client>::const_iterator it;
    for (it = clients.begin(); it != clients.end(); ++it) {
        const int clientFd = it->first;

        if (clientFdWhoChange != clientFd) {
            this->_server.setMessageQueue(clientFd, message);
        }
    }
}


void serverReply::USER_RPL(const int errorCode, const Client &client) {
    std::string replyMessage;

    switch (errorCode) {
        case ERR_ALREADYREGISTRED:
            replyMessage = ":localhost 462 * :Unauthorized command (already registered)";
            break;
        case ERR_NEEDMOREPARAMS:
            replyMessage = ":localhost 461 * USER :Not enough parameters";
            break;
        case ERR_ERRONEUSNICKNAME:
            replyMessage = ":localhost 432 * :Erroneous nickname";
            break;
    }

    _server.setMessageQueue(client.getClientFd(), replyMessage);
}
