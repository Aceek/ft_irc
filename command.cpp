/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:45 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/07 02:54:35 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

#include <string>
#include <vector>
#include <map>

std::map<std::string, Command::cmdFt> Command::_map;

Command::Command(void) {}

Command::Command(std::string const &line, Client *user) : _client(user) {
	initMap();
	
	std::vector<std::string> tab = ft_split(line, " ");
 	std::vector<std::string>::iterator it = tab.begin();

    if (it != tab.end() && (*it)[0] == ':') {
        this->_prefix = it->substr(1);
        tab.erase(it);
    }

	if (!tab.empty()) {
        this->_name = tab.front();
		toUpperCase(this->_name);
        tab.erase(tab.begin());
    }

	while (!tab.empty()) {
		if ((*it)[0] == ':') {
			this->_trailor = it->substr(1);
			tab.erase(it);
			while (!tab.empty()) {
				this->_trailor += " " + tab.front();
				tab.erase(tab.begin());		
			}
		} else {
			this->_args.push_back(tab.front());
			tab.erase(tab.begin());
		}
	}
}

Command::Command(Command const &rhs) :
	_prefix(rhs._prefix),
	_name(rhs._name),
	_args(rhs._args),
	_trailor(rhs._trailor),
	_client(rhs._client) {}

Command &Command::operator=(Command const &rhs) {
    if (this == &rhs) {
        return *this;
    }

	this->_prefix = rhs._prefix;
	this->_name = rhs._name;
	this->_args = rhs._args;
	this->_trailor = rhs._trailor;
	this->_client = rhs._client;

    return *this;
}

Command::~Command(void) {}

/* ************************************************************************** */

void Command::initMap(void) {
    _map["INVITE"] = Command::INVITE;
    _map["JOIN"] = Command::JOIN;
    _map["KICK"] = Command::KICK;
    _map["MODE"] = Command::MODE;
    _map["NICK"] = Command::NICK;
    _map["OPER"] = Command::OPER;
    _map["PART"] = Command::PART;
    _map["PONG"] = Command::PONG;
    _map["PRIVMSG"] = Command::PRIVMSG;
    _map["TOPIC"] = Command::TOPIC;
}

void Command::printArgs(void) const {
    std::cout << "Prefix: " << this->_prefix << std::endl;
    std::cout << "Name: " << this->_name << std::endl;

    std::cout << "Arguments:";
    for (size_t i = 0; i < this->_args.size(); ++i) {
        std::cout << " " << this->_args[i];
    }
    std::cout << std::endl;

    if (!_trailor.empty()) {
        std::cout << "Trailing: " << this->_trailor << std::endl;
    }
}

void Command::exec(void) {
    std::map<std::string, cmdFt>::iterator it = _map.find(this->_name);

    if (it != _map.end()) {
        it->second(*this);
    } else {
		throw std::runtime_error("Error: Unkown command");
	}
}

/* ************************************************************************** */

void Command::INVITE(Command const &cmd) {
	(void)cmd;
}

void Command::JOIN(Command const &cmd) {
	(void)cmd;
}

void Command::KICK(Command const &cmd) {
	(void)cmd;

}

void Command::MODE(Command const &cmd) {
	(void)cmd;

}

void Command::NICK(Command const &cmd) {
	(void)cmd;

}

void Command::OPER(Command const &cmd) {
	(void)cmd;

}

void Command::PART(Command const &cmd) {
	(void)cmd;

}

void Command::PONG(Command const &cmd) {
	(void)cmd;

}

void Command::PRIVMSG(Command const &cmd) {
	(void)cmd;

}

void Command::TOPIC(Command const &cmd) {
	(void)cmd;
}
