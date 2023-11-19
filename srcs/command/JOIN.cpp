/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:07 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/19 14:14:24 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::JOIN() {
/*   Parameters: <channel>{,<channel>} [<key>{,<key>}]	*/
  if (this->_args.size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string>	channels = ft_split(this->_args[0], ",");
    std::vector<std::string>	keys = (this->_args.size() > 1) ?
		ft_split(this->_args[1], ",") : std::vector<std::string>();

    for (size_t i = 0; i < channels.size(); ++i) {
        std::string const &channelName = channels[i];
        if (!isValidChannelName(channelName)) {
            return ERR_BADCHANMASK;
        }
		
        std::string	key = (i < keys.size()) ? keys[i] : "";
        Channel	*channel = getOrCreateChannel(channelName, key);
        if (channel->isClientPresent(this->_client)) {
			return ERR_USERONCHANNEL;
		}
		if (!isValidChannelKey(channel, key)) {
            return ERR_BADCHANNELKEY;
        }
        if (checkInviteOnlyAndNotInvited(channel)) {
            return ERR_INVITEONLYCHAN;
        }
        if (checkChannelFull(channel)) {
            return ERR_CHANNELISFULL;
        }

        addUserToChannel(channel);
        
		//to be rework with formated server response
		std::string joinMessage = 	":" + this->_client.getPrefix() + 
									" " + this->_name +
									" " + channelName;

		this->_server.sendMessageToChannel(*channel, joinMessage);

		//to be rework with formated server response
		// this->_server.RPL_TOPIC(*channel, this->_client);
		// this->_server.RPL_NAMREPLY(*channel, this->_client);
		// this->_server.RPL_ENDOFNAMES(*channel, this->_client);
    }

    return ERR_NONE;
}
