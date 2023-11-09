/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/09 05:37:40 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "client.hpp"
#include "server.hpp"
#include "utils.hpp"

#include <string>
#include <vector>

class Command {
	public:
		Command(void);
		Command(std::string const &line, Client &client, Server &server);
		Command(Command const &rhs);
		Command &operator=(Command const &rhs);
		~Command(void);
	
		void initCmdMap(void);
	    void printArgs(void) const;
		void exec(void);

		static void INVITE(Command const &cmd);
		static void JOIN(Command const &cmd);
		static void KICK(Command const &cmd);
		static void MODE(Command const &cmd);
		static void NICK(Command const &cmd);
		static void OPER(Command const &cmd);
		static void PART(Command const &cmd);
		static void PONG(Command const &cmd);
		static void PRIVMSG(Command const &cmd);
		static void TOPIC(Command const &cmd);

		std::string const				&getPrefix(void) const;
		std::string const				&getName(void) const;
		std::vector<std::string> const	&getArgs(void) const;
		std::string const				&getTrailor(void) const;
		Client							&getClient(void) const;
    	Server							&getServer(void) const;

	private:
		std::string					_prefix;
		std::string					_name;
		std::vector<std::string>	_args;
		std::string					_trailor;

		Client	&_client;
		Server	&_server;

		typedef void (*cmdFt)(Command const &cmd);
		static std::map<std::string, cmdFt>	_map;
};

#endif