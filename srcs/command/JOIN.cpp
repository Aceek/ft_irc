/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:07 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/14 03:43:20 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

static Channel* getOrCreateChannel(Command const &cmd, 
	std::string const &channelName, std::string const &key) {
    Channel *channel = cmd.getServer().getChannel(channelName);
    if (!channel) {
        cmd.getServer().addChannel(channelName);
        channel = cmd.getServer().getChannel(channelName);
        if (!key.empty()) {
            channel->setKey(key);
        }
    }
    return channel;
}

int Command::JOIN() {
/*   Parameters: <channel>{,<channel>} [<key>{,<key>}]	*/
  if (this->_args.size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string> channels = ft_split(this->_args[0], ",");
    std::vector<std::string> keys = (this->_args.size() > 1) ?
		ft_split(this->_args[1], ",") : std::vector<std::string>();

    for (size_t i = 0; i < channels.size(); ++i) {
        std::string const &channelName = channels[i];
        if (!isValidChannelName(channelName)) {
            return ERR_BADCHANMASK;
        }
		
        std::string key = (i < keys.size()) ? keys[i] : "";
        Channel *channel = getOrCreateChannel(*this, channelName, key);
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
		std::string joinMessage = 	":" + this->_client.getNicknameOrUsername(true) +
									" " + this->_name +
									" " + channelName;

		this->_server.sendMessageToChannel(*channel, joinMessage);

		//to be rework with formated server response
		channel->RPL_TOPIC(this->_client);
		channel->RPL_NAMREPLY(this->_client);
		channel->RPL_ENDOFNAMES(this->_client);
    }

    return ERR_NONE;
}
