/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/11 16:29:48 by ilinhard         ###   ########.fr       */
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
		std::map<std::string, cmdFt>	_map;
};

#endif