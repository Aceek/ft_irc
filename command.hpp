/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/07 09:08:46 by ilinhard         ###   ########.fr       */
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
		Command(std::string const &line, Client &client);
		Command(Command const &rhs);
		Command &operator=(Command const &rhs);
		~Command(void);
	
		void initMap(void);
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

	private:
		std::string					_prefix;
		std::string					_name;
		std::vector<std::string>	_args;
		std::string					_trailor;

		Client	&_client;

		typedef void (*cmdFt)(Command const &cmd);
		static std::map<std::string, cmdFt>	_map;
};

#endif