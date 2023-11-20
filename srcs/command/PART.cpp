/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:38 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/20 20:03:29 by pbeheyt          ###   ########.fr       */
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
      this->_targetChannel = this->_server.getChannel(*it);
		if (!this->_targetChannel) {
        	return ERR_NOSUCHCHANNEL;
        }
		if (!this->_targetChannel->isClientPresent(this->_client)) {
        	return ERR_NOTONCHANNEL;
        }
		
		this->_server.getServerReply()->PART(*this, this->_client);

		this->_targetChannel->delUser(this->_client);
		
		if (this->_targetChannel->getCount() < 1) {
			this->_server.delChannel((*it));
		} else {
			this->_server.getServerReply()->PART(*this, *this->_targetChannel);
		}
	}
	
	return ERR_NONE;
}
