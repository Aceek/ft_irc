/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:07 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/20 18:58:48 by pbeheyt          ###   ########.fr       */
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
        if (!isValidChannelName(channels[i])) {
            return ERR_BADCHANMASK;
        }
		
        std::string	key = (i < keys.size()) ? keys[i] : "";
        this->_targetChannel = getOrCreateChannel(channels[i], key);
        if (this->_targetChannel->isClientPresent(this->_client)) {
			return ERR_USERONCHANNEL;
		}
		if (!isValidChannelKey(this->_targetChannel, key)) {
            return ERR_BADCHANNELKEY;
        }
        if (checkInviteOnlyAndNotInvited(this->_targetChannel)) {
            return ERR_INVITEONLYCHAN;
        }
        if (checkChannelFull(this->_targetChannel)) {
            return ERR_CHANNELISFULL;
        }

        addUserToChannel(this->_targetChannel);
        
		this->_server.getServerReply()->JOIN(*this, *this->_targetChannel);
		
		//to be rework with formated server response
		// this->_server.RPL_TOPIC(*channel, this->_client);
		// this->_server.RPL_NAMREPLY(*channel, this->_client);
		// this->_server.RPL_ENDOFNAMES(*channel, this->_client);
    }

    return ERR_NONE;
}
