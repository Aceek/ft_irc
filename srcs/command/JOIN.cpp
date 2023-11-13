/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:07 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 08:40:31 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

static bool isValidParams(Command const &cmd) {
    return cmd.getArgs().size() > 0;
}

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

static void sendJoinMessage(Command const &cmd,
	Channel const *channel, const std::string &channelName) {
    std::string joinMessage = ":" + cmd.getClient().getNicknameOrUsername(true) +
                              " " + cmd.getName() +
                              " " + channelName;

    channel->sendMessageToAll(joinMessage);

	channel->RPL_TOPIC(cmd.getClient());
    channel->RPL_NAMREPLY(cmd.getClient());
    channel->RPL_ENDOFNAMES(cmd.getClient());
}

int Command::JOIN() {
/*   Parameters: <channel>{,<channel>} [<key>{,<key>}]	*/
  if (!isValidParams(*this)) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string> channels = ft_split(this->_args[0], ",");
    std::vector<std::string> keys = (this->_args.size() > 1) ?
		ft_split(this->_args[1], ",") : std::vector<std::string>();

    for (size_t i = 0; i < channels.size(); ++i) {
        std::string const &channelName = channels[i];
        std::string key = (i < keys.size()) ? keys[i] : "";

        if (!isValidChannelName(channelName)) {
            return ERR_BADCHANMASK;
        }

        Channel *channel = getOrCreateChannel(*this, channelName, key);
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
		sendJoinMessage(*this, channel, channelName);
    }

    return ERR_NONE;
}
