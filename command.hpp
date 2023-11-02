/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/02 05:29:24 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "client.hpp"
#include "utils.hpp"

#include <string>
#include <vector>

class Command {
	public:
		Command(void);
		Command(std::string const &line, Client *user);
		Command(Command const &rhs);
		Command &operator=(Command const &rhs);
		~Command(void);
	
	    void printArguments(void) const;
		void Command::exec(std::string const &cmd);

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

	private:
		std::string					_prefix;
		std::string					_name;
		std::vector<std::string>	_args;
		std::string					_trailing;

		Client	*_client;

		typedef void (*cmdFt)(Command const &cmd);
		static std::map<std::string, cmdFt>	_map;

};

#endif