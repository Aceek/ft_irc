/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:24 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 04:07:08 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::NAMES() {
/*	Parameters: [<channel>{,<channel>}]	*/
    if (this->_args.empty()) {
        for (std::map<std::string, Channel>::const_iterator it = this->_server.getChannels().begin();
		 	it != this->_server.getChannels().end(); ++it) {
            Channel const &channel = it->second;

            if (channel.isClientPresent(this->_client)) {
                channel.RPL_NAMREPLY(this->_client);
            }
        }
        return ERR_NONE;
    }

    for (size_t i = 0; i < this->_args.size(); ++i) {
        std::string const &channelName = this->_args[i];
        Channel* channel = this->_server.getChannel(channelName);

        if (!channel) {
            return ERR_NOSUCHCHANNEL;
        }

        if (channel->isClientPresent(this->_client)) {
            channel->RPL_NAMREPLY(this->_client);
        }
    }

    return ERR_NONE;
}
