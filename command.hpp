/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/09 13:52:59 by ilinhard         ###   ########.fr       */
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

		void INVITE();
		void JOIN();
		void KICK();
		void MODE();
		void OPER();
		void PART();
		void PONG();
		void PRIVMSG();
		void TOPIC();
		void NICK();
		


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

		typedef void (Command::*cmdFt)();
		std::map<std::string, cmdFt>	_map;

};

#endif