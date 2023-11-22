/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:09:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/22 15:50:18 by pbeheyt          ###   ########.fr       */
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
	if (asOperator || (this->_users.empty() && this->_operators.empty())) {
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
	client.addChannel(*this);
}

void Channel::delUser(Client &client) {
   // !!! what happened if there is no more operators on the channel ?
	this->_users.erase(&client);
	this->_operators.erase(&client);
	this->_invitedUsers.erase(&client);
	client.delChannel(*this);
}

void Channel::inviteUser(Client &client) {
	this->_invitedUsers.insert(&client);
}
