/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:45 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/02 01:15:01 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

Command::Command(void) {}

// Command::Command(std::string const &line, Client *user) {
	
// }


Command::Command(Command const &rhs) :
	_prefix(rhs._prefix),
	_cmdName(rhs._cmdName),
	_cmdArgs(rhs._cmdArgs) {}

Command &Command::operator=(Command const  &rhs) {
    if (this == &rhs) {
        return *this;
    }

	this->_prefix = rhs._prefix;
	this->_cmdName = rhs._cmdName;
	this->_cmdArgs = rhs._cmdArgs;

    return *this;
}

Command::~Command(void) {}