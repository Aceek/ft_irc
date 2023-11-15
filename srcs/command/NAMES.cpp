/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:24 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/15 06:20:18 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::NAMES() {
/*	Parameters: [<channel>{,<channel>}]	*/
    if (this->_args.empty()) {
        for (ChannelMap::const_iterator it = this->_server.getChannels().begin();
		 	it != this->_server.getChannels().end(); ++it) {
            Channel const &channel = it->second;
            if (channel.isClientPresent(this->_client)) {
                this->_server.RPL_NAMREPLY(channel, this->_client);
        		this->_server.RPL_ENDOFNAMES(channel, this->_client);
            }
        }
		
        return ERR_NONE;
    }
	for (std::vector<std::string>::iterator it = this->_args.begin(); 
		it != this->_args.end(); ++it) {
		Channel	*channel = this->_server.getChannel(*it);
		if (!channel) {
			return ERR_NOSUCHCHANNEL;
		}
		if (channel->isClientPresent(this->_client)) {
			this->_server.RPL_NAMREPLY(*channel, this->_client);
       		this->_server.RPL_ENDOFNAMES(*channel, this->_client);
		}
	}

    return ERR_NONE;
}
