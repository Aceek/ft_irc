/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:45 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/09 04:20:22 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

#include <string>
#include <vector>
#include <map>

std::map<std::string, Command::cmdFt> Command::_map;

// Command::Command(void) {} (pas de constructeur par default pour ref client)

Command::Command(std::string const &line, Client &client) : _client(client) {
	initCmdMap();
	
	std::istringstream	iss(line);
	if (line[0] == ':') {
		iss >> this->_prefix; // extract prefix
		this->_prefix = this->_prefix.substr(1);
	}
	iss >> this->_name; // extract command
	toUpperCase(this->_name);


	std::string arg;
	while (iss >> arg) {
		if (!arg.empty() && arg[0] == ':') { // Trailing detected
			std::getline(iss, this->_trailor);
			this->_trailor = arg + this->_trailor;
			break;
		}
		this->_args.push_back(arg);
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

void Command::initCmdMap(void) {
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

    if (!this->_trailor.empty()) {
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

std::string const &Command::getPrefix(void) const {
    return this->_prefix;
}

std::string const &Command::getName(void) const {
    return this->_name;
}

std::vector<std::string> const &Command::getArgs(void) const {
    return this->_args;
}

std::string const &Command::getTrailor(void) const {
    return this->_trailor;
}

/* ************************************************************************** */

void Command::INVITE(Command const &cmd) {
	(void)cmd;
}

void Command::JOIN(Command const &cmd) {
    if (cmd.getArgs().size() < 1) {
        throw std::runtime_error("Error: Not enough arguments");
    }

    std::map<std::string, std::string> channelKeyMap;
    std::vector<std::string> channels = ft_split(cmd.getArgs()[0], ",");    
    std::vector<std::string> keys;
    if (cmd.getArgs().size() > 1) {
        keys = ft_split(cmd.getArgs()[1], ",");
    }

    for (size_t i = 0; i < channels.size(); ++i) {
        std::string const &channel = channels[i];
        std::string key;

        if (i < keys.size()) {
            key = keys[i];
        }

        channelKeyMap[channel] = key;

        std::cout << "Channel: " << channel << " | Key: " << key << std::endl;
    }

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
