/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessors.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:24:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 04:24:45 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

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

Client &Command::getClient(void) const {
    return this->_client;
}

Server &Command::getServer(void) const {
    return this->_server;
}