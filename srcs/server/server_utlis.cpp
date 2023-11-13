/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utlis.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:21:08 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/14 00:50:56 by pbeheyt          ###   ########.fr       */
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
