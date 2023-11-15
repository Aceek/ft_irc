/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:38 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/15 06:53:10 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::PART() {
/*   Parameters: <channel>{,<channel>}	*/
    if (this->_args.size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string> channels = ft_split(this->_args[0], ",");    
    for (std::vector<std::string>::const_iterator it = channels.begin();
		it != channels.end(); ++it) {
        std::string const	&channelName = *it;
      	Channel				*channel = this->_server.getChannel(channelName);
		if (!channel) {
        	return ERR_NOSUCHCHANNEL;
        }
		if (!channel->isClientPresent(this->_client)) {
        	return ERR_NOTONCHANNEL;
        }

		//to be rework with formated server response
		std::string partMessage =	":" + this->_client.getNicknameOrUsername(true) +
									" " + this->_name + 
									" " + channelName;
		
		this->_server.sendMessage(this->_client.getClientFd(),partMessage);

		channel->delUser(this->_client);
		
		if (channel->getCount() < 1) {
			this->_server.delChannel((channelName));
		} else {
			this->_server.sendMessageToChannel(*channel, partMessage);					
		}
	}
	
	return ERR_NONE;
}
