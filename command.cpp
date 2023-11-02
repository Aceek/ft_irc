/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:45 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/02 03:23:17 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

#include <string>
#include <vector>

Command::Command(void) {}

Command::Command(std::string const &line, Client *user) : _client(user) {
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
			this->_trailing = it->substr(1);
			tab.erase(it);
			while (!tab.empty()) {
				this->_trailing += " " + tab.front();
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
	_args(rhs._args) {}

Command &Command::operator=(Command const  &rhs) {
    if (this == &rhs) {
        return *this;
    }

	this->_prefix = rhs._prefix;
	this->_name = rhs._name;
	this->_args = rhs._args;

    return *this;
}

Command::~Command(void) {}

/* ************************************************************************** */

void Command::printArguments(void) const {
    std::cout << "Prefix: " << _prefix << std::endl;
    std::cout << "Name: " << _name << std::endl;

    std::cout << "Arguments:";
    for (size_t i = 0; i < _args.size(); ++i) {
        std::cout << " " << _args[i];
    }
    std::cout << std::endl;

    if (!_trailing.empty()) {
        std::cout << "Trailing: " << _trailing << std::endl;
    }
}
