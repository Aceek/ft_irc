/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utlis.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:21:08 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/16 02:54:44 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

bool Server::isChannelPresent(std::string const &channelName) {
    ChannelMap::iterator it = this->_channels.find(channelName);
    
    if (it != this->_channels.end()) {
        return true;
    }

    return false;
}

void	Server::closingFdClients() {
	ClientMap::iterator it = this->_clients.begin();
	for (; it != this->_clients.end(); it++) {
		if (close (it->second.getClientFd()) == -1) {
			printServerInput(std::string(strerror(errno)));
		}
	}
}