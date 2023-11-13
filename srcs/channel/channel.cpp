/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:09:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 04:27:09 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

Channel::Channel(void) {}

Channel::Channel(std::string const &name, Server *server) : 
	_name(name),
	_inviteOnly(false),
	_topicRestricted(false),
	_userLimit(-1),
	_server(server) {}

Channel::Channel(Channel const &rhs) :
	_name(rhs._name),
	_topic(rhs._topic),
	_key(rhs._key),
	_users(rhs._users),
	_operators(rhs._operators),
	_inviteOnly(rhs._inviteOnly),
	_topicRestricted(rhs._topicRestricted),
	_userLimit(rhs._userLimit),
	_server(rhs._server) {}

Channel &Channel::operator=(Channel const  &rhs) {
    if (this == &rhs) {
        return *this;
    }

	this->_name = rhs._name;
	this->_topic = rhs._topic;
	this->_key = rhs._key;
	this->_users = rhs._users;
	this->_operators = rhs._operators;
	this->_inviteOnly = rhs._inviteOnly;
	this->_topicRestricted = rhs._topicRestricted;
	this->_userLimit = rhs._userLimit;
	this->_server = rhs._server;

    return *this;
}

Channel::~Channel(void) {}

/* ************************************************************************** */

void Channel::addUser(Client &client, bool asOperator) {
    if (asOperator || !(this->_users.size() + this->_operators.size())) {
		// add to operators list if there's no duplicate and erase it if needed in users list
		if (this->_operators.insert(&client).second) {
			this->_users.erase(&client);
		}
	} else {
		if (this->_users.insert(&client).second) {
			this->_operators.erase(&client);
		}
	}
	this->_invitedUsers.erase(&client);
}

void Channel::delUser(Client &client) {
   // !!! what happened if there is no more operators on the channel ?
	this->_users.erase(&client);
	this->_operators.erase(&client);
	this->_invitedUsers.erase(&client);

}

void Channel::inviteUser(Client &client) {
	this->_invitedUsers.insert(&client);
}

/* ************************************************************************** */

void Channel::sendMessageToAll(const std::string &message) const {
	
	for (std::set<Client *>::iterator it = this->_users.begin();
		it != this->_users.end(); ++it) {
			this->_server->sendMessage(*(*it), message);
	}
	for (std::set<Client *>::iterator it = this->_operators.begin();
		it != this->_operators.end(); ++it) {
			this->_server->sendMessage(*(*it), message);
	}
}

//!!!real server name to add - Maybe add clean Server reply functions in server class ??
void 	Channel::RPL_NOTOPIC(Client &client) const {
	std::string RPL_NOTOPIC =	":server " +
								this->_name +
							 	" :No topic is set";
							
	this->_server->sendMessage(client, RPL_NOTOPIC);	
}

void Channel::RPL_TOPIC(Client &client) const {
    if (!this->_topic.empty()) { 
		std::string RPL_TOPIC =	":server " +
								this->_name +
								" :" + this->_topic;
								
		this->_server->sendMessage(client, RPL_TOPIC);
	}
}

void Channel::RPL_NAMREPLY(Client &client) const {
    std::string RPL_NAMREPLY =	":server " + 
								client.getNicknameOrUsername(true) + 
								" = " + this->_name +
								" :" + getNicknames();

   this->_server->sendMessage(client, RPL_NAMREPLY);
}

void Channel::RPL_ENDOFNAMES(Client &client) const {
    std::string RPL_ENDOFNAMES =	":server " +
								client.getNicknameOrUsername(true) +
								" " + this->_name +
								" :End of /NAMES list.";
								
	this->_server->sendMessage(client, RPL_ENDOFNAMES);
}