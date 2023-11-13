/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_accessors.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:22:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 23:25:09 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

std::string Server::getErrorMessage(int errorCode) {
	// need add system add nickname of user .. 
	switch (errorCode) {
    case ERR_NONE:
        return "No error";
    case ERR_REALNAME:
        return "[RealName] 1: Real Name bad format (max 25 char) + alphanumeric characters only";
    case ERR_PASSFORMAT:
        return "[Password] 2: Password bad format (max 25 char) + alphanumeric characters only";
    case ERR_PASSNEEDED:
        return "[Password] 3: Server password required to log in";
    case ERR_PASSWRONG:
        return "[Password] 4: Password does not match with server's password";
    case ERR_NOSUCHNICK:
        return "[User] 401: No such nick";
    case ERR_NOSUCHCHANNEL:
        return "[Channel] 403: No such channel";
    case ERR_CANNOTSENDTOCHAN:
        return "[Channel] 404: Cannot send to channel";
	case ERR_NOTEXTTOSEND:
        return "[Command] 412: No text to send";
    case ERR_UNKNOWNCOMMAND:
        return "[Command] 421: Unknown command";
    case ERR_NONICKNAMEGIVEN:
        return "[Nick] 431: No nickname given";
    case ERR_ERRONEUSNICKNAME:
        return "[Nick] 432: Erroneous nickname";
    case ERR_NICKNAMEINUSE:
        return "[Nick] 433: Nickname is already in use";
    case ERR_NICKCOLLISION:
        return "[Nick] 436: Nickname collision KILL";
    case ERR_NOTONCHANNEL:
        return "[Channel] 442: You're not on that channel";
    case ERR_USERONCHANNEL:
        return "[Channel] 443: User already on channel";
    case ERR_NEEDMOREPARAMS:
        return "[Command] 461: Not enough parameters";
    case ERR_ALREADYREGISTRED:
        return "[Password] 462: You may not reregister (already done)";
    case ERR_PASSWDMISMATCH:
        return "[Oper] 464: Password incorrect";
    case ERR_CHANNELISFULL:
        return "[Channel] 471: Cannot join channel (+l)";
	case ERR_UNKNOWNMODE:
		return "[Char] 472: is unknown mode char to me";
    case ERR_INVITEONLYCHAN:
        return "[Channel] 473: Cannot join channel (+i)";
    case ERR_BADCHANNELKEY:
        return "[Channel] 475: Bad channel key";
    case ERR_BADCHANMASK:
        return "[Channel] 476: Bad channel mask";
    case ERR_CHANOPRIVSNEEDED:
        return "[Channel] 482: You're not channel operator";
	default:
        return "Unknown error";
    }
}

const std::string	&Server::getPassword() const {
	return (this->_password);
}

Client *Server::getClientByNickname(std::string const &nickname) {
	for (std::map<const int, Client>::iterator it = this->_clients.begin();
		it != this->_clients.end(); ++it) {
			if (it->second.getNicknameOrUsername(true) == nickname) {
				return &it->second;
			}
	};
	
	return NULL;
}

const std::map<const int, Client> &Server::getClients() const {
	return (this->_clients);
}

Channel *Server::getChannel(std::string const &channelName) {
    std::map<std::string, Channel>::iterator it = this->_channels.find(channelName);

    if (it != this->_channels.end() && it->first == channelName) {
        return &it->second;
    }

    return NULL;
}

const ChannelMap &Server::getChannels() {
	return this->_channels;
}

void	Server::setClientToRemove(const int clientFd) {
	this->_clientsToRemove.push_back(clientFd);
}

void Server::setMessageQueue(const int clientfd, const std::string &message) {
	this->_messageQueue[clientfd].push_back(message);
}