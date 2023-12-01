/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_accessors.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:24:10 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/12/01 22:58:28 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

std::string const &Command::getPrefix(void) const { return this->_prefix; }

std::string const &Command::getName(void) const { return this->_name; }

std::vector<std::string> const &Command::getArgs(void) const {
  return this->_args;
}

std::string const &Command::getTrailor(void) const { return this->_trailor; }

Client &Command::getClient(void) const { return this->_client; }

Server &Command::getServer(void) const { return this->_server; }

Channel *Command::getTargetChannel(void) const { return this->_targetChannel; }

Client *Command::getTargetClient(void) const { return this->_targetClient; }

std::string const &Command::getTargetChannelName(void) const {
  return this->_targetChannelName;
}

std::string const &Command::getNick(void) const { return this->_nick; }

std::string const &Command::getTopic(void) const { return this->_topic; }

std::string const &Command::getBadWord(void) const { return this->_badWord; }

std::string const &Command::getModeStr(void) const { return this->_modeStr; }

std::vector<std::string> const &Command::getModeArgs(void) const {
  return this->_modeArgs;
}

void Command::setTargetClient(Client *client) {
	this->_targetClient = client;
}

void Command::setBadWord(std::string const &badWord) {
	this->_badWord = badWord;
}