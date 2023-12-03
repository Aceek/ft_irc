/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HELP.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:46:40 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/12/03 21:49:01 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

void Command::HELP() {
  serverReply *serverReply = this->_server.getServerReply();
  std::string clientNick = this->_client.getNicknameOrUsername(true);
  std::string serverName =
      "localhost";

  std::string helpMessage;

  helpMessage +=
      ":" + serverName + " 372 " + clientNick + " :Available commands:\r\n";

  for (CommandMap::const_iterator it = _commands.begin(); it != _commands.end();
       ++it) {
    helpMessage += ":" + serverName + " 372 " + clientNick + " :" + it->first +
                   " - Parameters: " + it->second.params + "\r\n";
  }

  helpMessage += ":" + serverName + " 376 " + clientNick + " :End of HELP\r\n";

  serverReply->setMessageQueue(this->_client.getClientFd(), helpMessage);
}
