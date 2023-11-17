/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SENDFILE.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:46 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/17 09:24:32 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::SENDFILE() {
/*	Parameters: <receiver>{,<receiver>} <file path> */
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string>	receivers = ft_split(this->_args[0], ",");
    std::string					filePath = this->_args[1];

    std::ifstream fileStream(filePath.c_str(), std::ios::binary);
    if (!fileStream.is_open()) {
        return ERR_FILEINVALID;
    }
    fileStream.close();

	for (std::vector<std::string>::iterator it = receivers.begin();
		it != receivers.end(); ++it) {
		std::string const	&receiver = *it;
		std::string sendfileMessage =	":" + this->_client.getNicknameOrUsername(true) +
										" " + this->_name +
										" " + receiver +
										" :" + filePath;
		
		Client *client = this->_server.getClientByNickname(receiver);
		if (!client) {
			return ERR_NOSUCHNICK;
		}
		
		const int	senderFd = this->_client.getClientFd();
		const int	receiverFd = client->getClientFd();
		if (receiverFd != senderFd) {
			this->_server.setMessageQueue(senderFd, sendfileMessage);
		}
		this->_server.setMessageQueue(receiverFd, sendfileMessage);
		
		this->_server.sendFile(client->getClientFd(), filePath);
	}

	return ERR_NONE;
}
