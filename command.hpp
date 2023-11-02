/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/02 04:47:58 by pbeheyt          ###   ########.fr       */
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

		static void INVITE(const Command& cmd);
		static void JOIN(const Command& cmd);
		static void KICK(const Command& cmd);
		static void MODE(const Command& cmd);
		static void NICK(const Command& cmd);
		static void OPER(const Command& cmd);
		static void PART(const Command& cmd);
		static void PONG(const Command& cmd);
		static void PRIVMSG(const Command& cmd);
		static void TOPIC(const Command& cmd);

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