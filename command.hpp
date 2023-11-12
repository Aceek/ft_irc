/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/12 01:39:31 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "utils.hpp"

class Command {
	public:
		Command(void);
		Command(std::string const &line, Client &client, Server &server);
		Command(Command const &rhs);
		Command &operator=(Command const &rhs);
		~Command(void);
	
		void initCommandsMap(void);
	    void printArgs(void) const;
		int exec(void);

		int INVITE();
		int JOIN();
		int KICK();
		int MODE();
		int OPER();
		int PART();
		int PONG();
		int PRIVMSG();
		int TOPIC();
		int USER();
		int	NICK();
		int	PASS();
		int	NAMES();
		int	QUIT();
		int	HELP();

		// utilitaire
		bool isValidNickname() const;
		bool isNicknameOrUsernameAvailable(bool useNickname) const;
		bool isValidRealName() const;
		bool isValidPassword() const;

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

		typedef int (Command::*cmdFt)();

		struct CommandInfo {
        	cmdFt		func;
        	std::string	params;

			CommandInfo() {}
			CommandInfo(cmdFt func, std::string const &params) : 
				func(func), 
				params(params) {}
    	};

    	typedef std::map<std::string, CommandInfo> CommandMap;
		CommandMap	_commands;
};

#endif