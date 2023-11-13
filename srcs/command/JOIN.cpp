/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:07 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 04:10:32 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::JOIN() {
/*   Parameters: <channel>{,<channel>} [<key>{,<key>}]	*/
    if (this->_args.size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string> channels = ft_split(this->_args[0], ",");
    std::vector<std::string> keys;

    if (this->_args.size() > 1) {
        keys = ft_split(this->_args[1], ",");
    }

    for (size_t i = 0; i < channels.size(); ++i) {
        std::string const &channelName = channels[i];
        std::string key;

        if (i < keys.size()) {
            key = keys[i];
        }

        if (channelName[0] != '#') {
            return ERR_BADCHANMASK;
        }

        Channel *channel = this->_server.getChannel(channelName);
        if (!channel) {
            this->_server.addChannel(channelName);
            channel = this->_server.getChannel(channelName);

            if (!key.empty()) {
                channel->setKey(key);
            }
        } else if (!key.empty() && key != channel->getKey()) {
        	return ERR_BADCHANNELKEY;
        }

		///!!!logique du mdp a implementer

		if (channel->getInviteOnly() && !channel->isClientInvited(this->_client)) {
			return ERR_INVITEONLYCHAN;
		}

		if (channel->getCount() >= channel->getUserLimit() &&
			channel->getUserLimit() >= 0) {
			return ERR_CHANNELISFULL;
		}
		
		channel->addUser(this->_client, 
			this->_server.isOperator(this->_client.getClientFd()));
		
		
		std::string joinMessage =	":" + this->_client.getNicknameOrUsername(true) +
									" " + this->_name + 
									" " + channelName;
								
		channel->sendMessageToAll(joinMessage);
		
		channel->RPL_TOPIC(this->_client);
		channel->RPL_NAMREPLY(this->_client);
		channel->RPL_ENDOFNAMES(this->_client);
    }
	
	return ERR_NONE;
}
