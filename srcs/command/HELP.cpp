/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HELP.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:46:40 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/25 10:28:55 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::HELP() {
	serverReply *serverReply = this->_server.getServerReply();
	std::string helpMessage = "Available commands:\r\n";
	for (CommandMap::const_iterator it = _commands.begin(); it != _commands.end(); ++it) {
		helpMessage += it->first + " - Parameters: " + it->second.params + "\r\n";
	}

	serverReply->setMessageQueue(this->_client.getClientFd(), helpMessage);

	return ERR_NONE;
}
