/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:18 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/21 15:05:22 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"
///!!!revoir parsing des modes et parametre???? : atm -> MODE +t +i -k =/= +ti -k
int Command::MODE() {
	/* Parameters: <channel> <+/-modes> [parameters] */
	if (this->_args.size() < 2) {
		return ERR_NEEDMOREPARAMS;
	}

	this->_targetChannel = this->_server.getChannel(this->_args[0]);
	if (!this->_targetChannel) {
		return ERR_NOSUCHCHANNEL;
	}
	if (!this->_targetChannel->isOperator(this->_client)) {
		return ERR_CHANOPRIVSNEEDED;
	}

	this->_modeSet = this->_args[1];
	if (!isValidMode(this->_modeSet)) {
		return ERR_UMODEUNKNOWNFLAG;
	}

	for (std::vector<std::string>::const_iterator it = this->_args.begin() + 2;
		it != this->_args.end(); ++it) {
			this->_modeArgs.push_back(*it);
	}

	size_t	i = 0;
	char	s = this->_modeSet[0];
	for (std::string::const_iterator it = this->_modeSet.begin(); 
		it != this->_modeSet.end(); ++it) {
		
		switch (*it) {
			case '+':
				s = '+';
				break;
			case '-':
				s = '-';
				break;
			case 'i':
				// Set/unset the channel on invitation only
				this->_targetChannel->setInviteOnly(s == '+');
				break;
			case 't':
				// Set/unset restrictions on the TOPIC command for channel operators
				this->_targetChannel->setTopicRestricted(s == '+');
				break;
			case 'k':
				// Set/unset the channel key (password)
				if (s == '+') {
					if (i >= this->_modeArgs.size()) {
						return ERR_NEEDMOREPARAMS;
					} 
					if (!isValidPassword(this->_modeArgs[i])) {
						++i;
						return ERR_PASSFORMAT;
					}
					this->_targetChannel->setKey(this->_modeArgs[i]);
					++i;
				} else {
					this->_targetChannel->setKey("");
				}
				break;
			case 'o': {
				// Give/take operator privilege from a user
				if (i >= this->_modeArgs.size()) {
					return ERR_NEEDMOREPARAMS;
				} 
				this->_targetClient = this->_server.getClientByNickname(this->_modeArgs[i]);
				++i;
				if (!this->_targetClient) {
					return ERR_NOSUCHNICK;
				}
				this->_targetChannel->addUser(*this->_targetClient, s == '+');
				break;
			}
			case 'l':
				// Set/unset the limit of users for the channel
				if (i >= this->_modeArgs.size()) {
					return ERR_NEEDMOREPARAMS;
				} 
				this->_targetChannel->setUserLimit(s == '+' ? 
					atoi(this->_modeArgs[i].c_str()) : -1);
				++i;
				break;
			default:
				return ERR_UNKNOWNMODE;
		}
	}
	
	this->_server.getServerReply()->MODE(*this, *this->_targetChannel);
	
	return ERR_NONE;
}
