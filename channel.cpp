/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:09:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/10 06:24:12 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

Channel::Channel(void) {}

Channel::Channel(Server *server) : _server(server) {}

Channel::Channel(Channel const &rhs) :
	_topic(rhs._topic),
	_key(rhs._key),
	_membersList(rhs._membersList),
	_operatorsList(rhs._operatorsList),
	_server(rhs._server) {}

Channel &Channel::operator=(Channel const  &rhs) {
    if (this == &rhs) {
        return *this;
    }

	this->_topic = rhs._topic;
	this->_key = rhs._key;
	this->_membersList = rhs._membersList;
	this->_operatorsList = rhs._operatorsList;
	this->_server = rhs._server;

    return *this;
}

Channel::~Channel(void) {}

/* ************************************************************************** */

void Channel::addUser(Client &user, bool asOperator) {
    if (asOperator || this->_operatorsList.size() == 0) {
		// add to operators list if there's no duplicate and erase it if needed in users list
		if (this->_operatorsList.insert(&user).second) {
			this->_membersList.erase(&user);
		}
	} else {
		if (this->_membersList.insert(&user).second) {
			this->_operatorsList.erase(&user);
		}
	}
}

void Channel::delUser(Client &user) {
   // !!! what happened if there is no more operators on the channel ?
   this->_membersList.erase(&user);
   this->_operatorsList.erase(&user);
}

bool Channel::isUser(Client &user) {
    return this->_membersList.find(&user) != this->_membersList.end();
}

bool Channel::isOperator(Client &user) {
    return this->_operatorsList.find(&user) != this->_operatorsList.end();

}

/* ************************************************************************** */

std::string const &Channel::getTopic(void) {
    return this->_topic;
}

void Channel::setTopic(std::string const &topic) {
    this->_topic = topic;
}

std::string const &Channel::getKey(void) {
    return this->_key;
}

void Channel::setKey(std::string const &key) {
    this->_key = key;
}

int Channel::getUsersNumber(void) {
	return this->_membersList.size() + this->_operatorsList.size();
}

std::string const Channel::getUsersNick(void) {
    std::string userNicks;

    for (std::set<Client *>::iterator it = this->_operatorsList.begin();
         it != this->_operatorsList.end(); ++it) {
        userNicks += "@" + (*it)->getNicknameOrUsername(true) + " ";
    }

    for (std::set<Client *>::iterator it = this->_membersList.begin();
         it != this->_membersList.end(); ++it) {
        userNicks += (*it)->getNicknameOrUsername(true) + " ";
    }

    return userNicks;
}


/* ************************************************************************** */

void Channel::sendMessageToAll(const std::string &message) {
	
	for (std::set<Client *>::iterator it = this->_membersList.begin();
		it != this->_membersList.end(); ++it) {
			this->_server->sendMessage(*(*it), message);
	}
	for (std::set<Client *>::iterator it = this->_operatorsList.begin();
		it != this->_operatorsList.end(); ++it) {
			this->_server->sendMessage(*(*it), message);
	}
}

//!!!real server name to add - Maybe add clean Server reply functions in server class ??
void Channel::RPL_TOPIC(Client &user) {
    if (!this->_topic.empty()) {
        this->_server->sendMessage(user, ":server_name " + 
			user.getNicknameOrUsername(true) + " " + this->_topic);
    }
}

void Channel::RPL_NAMREPLY(Client &user) {
    std::string namReply = ":server_name "  + 
		user.getNicknameOrUsername(true) + " = " + this->_topic + " :";

   this->_server->sendMessage(user, namReply + getUsersNick());
}

void Channel::RPL_ENDOFNAMES(Client &user) {
    this->_server->sendMessage(user, ":server_name " + 
		user.getNicknameOrUsername(true) + " " + this->_topic + " :End of /NAMES list.");
}