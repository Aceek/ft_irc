/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_accessors.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:26:29 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/26 19:25:32 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

std::string const &Channel::getName(void) const {
	return this->_name;
}

std::string const &Channel::getTopic(void) const {
	return this->_topic;
}

void Channel::setTopic(std::string const &topic) {
	this->_topic = topic;
}

std::string const &Channel::getKey(void) const {
	return this->_key;
}

std::set<Client *> const &Channel::getUsers(void) const {
	return this->_users;
}

std::set<Client *> const &Channel::getOperators(void) const {
	return this->_operators;
}

void Channel::setKey(std::string const &key) {
	this->_key = key;
}

int Channel::getCount(void) const {
	return this->_users.size() + this->_operators.size();
}

std::string const Channel::getNicknames(void) const {
	std::string nicks;

	for (std::set<Client *>::iterator it = this->_operators.begin();
		 it != this->_operators.end(); ++it) {
		nicks += "@" + (*it)->getNicknameOrUsername(true) + " ";
	}
	for (std::set<Client *>::iterator it = this->_users.begin();
		 it != this->_users.end(); ++it) {
		nicks += (*it)->getNicknameOrUsername(true) + " ";
	}
	if (!nicks.empty()) {
		nicks.erase(nicks.size() - 1);
	}

	return nicks;
}

bool Channel::getInviteOnly(void) const {
	return this->_inviteOnly;
}

void Channel::setInviteOnly(bool inviteOnly) {
	this->_inviteOnly = inviteOnly;
}

bool Channel::getTopicRestricted(void) const {
	return this->_topicRestricted;
}

void Channel::setTopicRestricted(bool topicRestricted) {
	this->_topicRestricted = topicRestricted;
}

int Channel::getUserLimit(void) const {
	return this->_userLimit;
}

void Channel::setUserLimit(int userLimit) {
	this->_userLimit = userLimit;
}
