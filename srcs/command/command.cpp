/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:45 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/24 15:41:40 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

// Command::Command(void) {} (pas de constructeur par default pour ref client)

Command::Command(std::string const &line, Client &client, Server &server) : 
	_command(line), _prefix(""), _name(""), _args(), _trailor(""),
	_hasTrailor(false), _client(client), _server(server) {
	initCommandsMap();
	
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
			this->_hasTrailor = true;
			arg = arg.substr(1);
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
	_client(rhs._client),
	_server(rhs._server) {}

Command &Command::operator=(Command const &rhs) {
	if (this == &rhs) {
		return *this;
	}

	this->_prefix = rhs._prefix;
	this->_name = rhs._name;
	this->_args = rhs._args;
	this->_trailor = rhs._trailor;
	this->_client = rhs._client;
	this->_server = rhs._server;

	return *this;
}

Command::~Command(void) {}

/* ************************************************************************** */

void Command::initCommandsMap(void) {
	this->_commands["HELP"] = CommandInfo(&Command::HELP, "none");
	this->_commands["INVITE"] = CommandInfo(&Command::INVITE, "<nickname> <channel>");
	this->_commands["JOIN"] = CommandInfo(&Command::JOIN, "<channel>{,<channel>} [<key>{,<key>}]");
	this->_commands["KICK"] = CommandInfo(&Command::KICK, "<channel> <user> [<comment>]");
	this->_commands["LIST"] = CommandInfo(&Command::LIST, "none");
	this->_commands["MODE"] = CommandInfo(&Command::MODE, "<channel> <+/-modes> [parameters]");
	this->_commands["NAMES"] = CommandInfo(&Command::NAMES, "[<channel>{,<channel>}]");
	this->_commands["NICK"] = CommandInfo(&Command::NICK, "<nickname>");
	this->_commands["PART"] = CommandInfo(&Command::PART, "<channel>{,<channel>}");
	this->_commands["PASS"] = CommandInfo(&Command::PASS, "<password>");
	this->_commands["PRIVMSG"] = CommandInfo(&Command::PRIVMSG, "<receiver>{,<receiver>} <text to be sent>");
	this->_commands["TOPIC"] = CommandInfo(&Command::TOPIC, "<channel> [<topic>]");
	this->_commands["USER"] = CommandInfo(&Command::USER, "<username> <hostname> <servername> <realname>");
	this->_commands["QUIT"] = CommandInfo(&Command::QUIT, "none");
	this->_commands["CAP"] = CommandInfo(&Command::CAP, "<subcommand> [:<capabilities>]");
	this->_commands["PING"] = CommandInfo(&Command::PONG, "<token>");
}

void Command::exec(void) {
	serverReply *serverReply = this->_server.getServerReply();
	serverReply->displayClientCommand(this->_command, this->_client);

	CommandMap::iterator it = this->_commands.find(this->_name);
	if ((it != this->_commands.end() &&
	(this->_client.isPasswordSetUp() || it->first == "PASS" || it->first == "CAP"))) {
		(this->*(it->second).func)();
	}
}
