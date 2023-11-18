/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_accessors.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:22:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/18 11:41:06 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

const std::string	&Server::getPassword() const {
	return (this->_password);
}


serverReply	*Server::getServerReply() const {
	return (this->_serverReply);
}

Client *Server::getClientByNickname(std::string const &nickname) {
	for (std::map<const int, Client>::iterator it = this->_clients.begin();
		it != this->_clients.end(); ++it) {
			if (it->second.getNicknameOrUsername(true) == nickname) {
				return &it->second;
			}
	};
	
	return NULL;
}

const std::map<const int, Client> &Server::getClients() const {
	return (this->_clients);
}

Channel *Server::getChannel(std::string const &channelName) {
    std::map<std::string, Channel>::iterator it = this->_channels.find(channelName);

    if (it != this->_channels.end() && it->first == channelName) {
        return &it->second;
    }

    return NULL;
}

const ChannelMap &Server::getChannels() {
	return this->_channels;
}

std::string Server::getChannelsNames() const {
    std::string allChannelNames;

    for (ChannelMap::const_iterator it = this->_channels.begin(); it != this->_channels.end(); ++it) {
        allChannelNames +=	it->second.getName() + 
							(!it->second.getTopic().empty() ? 
							" : " + it->second.getTopic() : "") +
							"\n";
    }
    if (!allChannelNames.empty()) {
        allChannelNames.erase(allChannelNames.size() - 1);
    }

    return allChannelNames;
}

void	Server::setClientToRemove(const int clientFd) {
	this->_clientsToRemove.push_back(clientFd);
}

void Server::setMessageQueue(const int clientfd, const std::string &message) {
	this->_messageQueue[clientfd].push_back(message);
}

// test function

int	Server::getWaitingMessage(int clientFd) {
	return (this->_messageQueue[clientFd].size());
}
