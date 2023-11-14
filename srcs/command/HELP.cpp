/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HELP.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:46:40 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/14 01:10:29 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::HELP() {
    std::string helpMessage = "Available commands:\r\n";
    for (CommandMap::const_iterator it = _commands.begin(); it != _commands.end(); ++it) {
        helpMessage += it->first + " - Parameters: " + it->second.params + "\r\n";
    }

    this->_server.setMessageQueue(this->_client.getClientFd(), helpMessage);

    return ERR_NONE;
}
