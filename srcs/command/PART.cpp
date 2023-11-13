/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:38 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 08:49:24 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::PART() {
/*   Parameters: <channel>{,<channel>}	*/
    if (this->_args.size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string> channels = ft_split(this->_args[0], ",");    
	
    for (size_t i = 0; i < channels.size(); ++i) {
        std::string const &channelName = channels[i];
		
      	Channel *channel = this->_server.getChannel(channelName);
		
		if (!channel) {
        	return ERR_NOSUCHCHANNEL;
        } else if (!channel->isClientPresent(this->_client)) {
        	return ERR_NOTONCHANNEL;
        }

		channel->delUser(this->_client);
		
		if (channel->getCount() < 1) {
			this->_server.delChannel((channelName));
		} else {
			std::string partMessage =	":" + this->_client.getNicknameOrUsername(true) +
										" " + this->_name + 
										" " + channelName;
									
			channel->sendMessageToAll(partMessage);
		}
	}
	
	return ERR_NONE;
}
