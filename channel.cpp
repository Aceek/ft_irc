/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:09:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/09 08:12:12 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

Channel::Channel(void) {}

Channel::Channel(Channel const &rhs) :
	_topic(rhs._topic),
	_key(rhs._key),
	_usersList(rhs._usersList),
	_operatorsList(rhs._operatorsList) {}

Channel &Channel::operator=(Channel const  &rhs) {
    if (this == &rhs) {
        return *this;
    }

	this->_topic = rhs._topic;
	this->_key = rhs._key;
	this->_usersList = rhs._usersList;
	this->_operatorsList = rhs._operatorsList;

    return *this;
}

Channel::~Channel(void) {}

/* ************************************************************************** */

void Channel::addUser(Client &user, bool asOperator) {
    if (asOperator || this->_operatorsList.size() == 0) {
		// add to operators list if there's no duplicate and erase it if needed in users list
		if (this->_operatorsList.insert(&user).second) {
			this->_usersList.erase(&user);
		}
	} else {
		if (this->_usersList.insert(&user).second) {
			this->_operatorsList.erase(&user);
		}
	}
}

void Channel::delUser(Client &user) {
   // !!! what happened if there is no more operators on the channel ?
   this->_usersList.erase(&user);
   this->_operatorsList.erase(&user);
}

bool Channel::isUser(Client &user) {
    return this->_usersList.find(&user) != this->_usersList.end();
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

int Channel::getUserNumber(void) {
	return this->_usersList.size() + this->_operatorsList.size();
}

/* ************************************************************************** */

// char * and not string ?
void Channel::addAllBufToCommand(char const *buffer) {
	for (std::set<Client *>::iterator it = this->_usersList.begin();
		it != this->_usersList.end(); ++it) {
			(*it)->addToCommand(buffer);
	}
	for (std::set<Client *>::iterator it = this->_operatorsList.begin();
		it != this->_operatorsList.end(); ++it) {
			(*it)->addToCommand(buffer);
	}
}