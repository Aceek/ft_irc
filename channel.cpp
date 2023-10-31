/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:09:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/10/31 04:12:24 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

Channel::Channel(void) {}

Channel::Channel(Channel const &rhs) :
	_topicName(rhs._topicName),
	_usersList(rhs._usersList),
	_operatorsList(rhs._operatorsList) {}

Channel &Channel::operator=(Channel const  &rhs) {
    if (this == &rhs) {
        return *this;
    }

	this->_topicName = rhs._topicName;
	this->_usersList = rhs._usersList;
	this->_operatorsList = rhs._operatorsList;

    return *this;
}

Channel::~Channel(void) {}

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

std::string const &Channel::getTopic(void) {
    return this->_topicName;
}

void Channel::setTopic(std::string const &topicName) {
    this->_topicName = topicName;
}
