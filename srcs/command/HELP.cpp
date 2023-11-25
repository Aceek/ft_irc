/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HELP.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:46:40 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/25 14:59:53 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

// int Command::HELP() {
// 	serverReply *serverReply = this->_server.getServerReply();
// 	std::string helpMessage = "Available commands:\r\n";
// 	for (CommandMap::const_iterator it = _commands.begin(); it != _commands.end(); ++it) {
// 		helpMessage += it->first + " - Parameters: " + it->second.params + "\n";
// 	}

// 	serverReply->setMessageQueue(this->_client.getClientFd(), helpMessage);

// 	return ERR_NONE;
// }

int Command::HELP() {
    serverReply *serverReply = this->_server.getServerReply();
    std::string clientNick = this->_client.getNicknameOrUsername(true);
    std::string serverName = "localhost"; // Remplacez par le nom réel de votre serveur

    std::string helpMessage;

    // Commencez le message d'aide
    helpMessage += ":" + serverName + " 372 " + clientNick + " :Available commands:\r\n";

    for (CommandMap::const_iterator it = _commands.begin(); it != _commands.end(); ++it) {
        helpMessage += ":" + serverName + " 372 " + clientNick + " :" + it->first + " - Parameters: " + it->second.params + "\r\n";
    }

    // Terminez le message d'aide
    helpMessage += ":" + serverName + " 376 " + clientNick + " :End of HELP\r\n";

    serverReply->setMessageQueue(this->_client.getClientFd(), helpMessage);

    return ERR_NONE;
}
