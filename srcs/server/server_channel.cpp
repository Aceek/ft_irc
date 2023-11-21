/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_channel.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:51:53 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/21 15:09:12 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void	Server::addChannel(std::string const &channelName) {
	this->_channels[channelName] = Channel(channelName, this);
}

void	Server::delChannel(std::string const &channelName) {
	ChannelMap::iterator it = this->_channels.find(channelName);
	
	if (it != this->_channels.end()) {
			this->_channels.erase(it);	
	}
}

void Server::sendMessageToChannel(Channel const &channel, std::string const &message) {
	
	if (!isChannelPresent(channel.getName()) || message.empty()) {
		return;
	}
	
	for (std::set<Client *>::iterator it = channel.getUsers().begin();
		it != channel.getUsers().end(); ++it) {
			setMessageQueue((*it)->getClientFd(), message);
	}
	for (std::set<Client *>::iterator it = channel.getOperators().begin();
		it != channel.getOperators().end(); ++it) {
			setMessageQueue((*it)->getClientFd(), message);
	}
}
