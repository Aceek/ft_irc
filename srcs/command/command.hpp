/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/20 22:43:05 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../../include.hpp"

class Command {
	public:
		Command(void);
		Command(std::string const &line, Client &client, Server &server);
		Command(Command const &rhs);
		Command &operator=(Command const &rhs);
		~Command(void);
	
		void initCommandsMap(void);
		int exec(void);

		int INVITE();
		int JOIN();
		int KICK();
		int LIST();
		int MODE();
		int PART();
		int PRIVMSG();
		int TOPIC();
		int USER();
		int	NICK();
		int	PASS();
		int	NAMES();
		int	QUIT();
		int	HELP();
		int	CAP();

		/*command_accessors*/
		std::string const				&getPrefix(void) const;
		std::string const				&getName(void) const;
		std::vector<std::string> const	&getArgs(void) const;
		std::string const				&getTrailor(void) const;
		Client							&getClient(void) const;
    	Server							&getServer(void) const;
		Channel							&getTargetChannel(void) const;
    	Client							&getTargetClient(void) const;
    	std::string const				&getModeSet(void) const;
		std::vector<std::string> const	&getModeArgs(void) const;
		
		/*command_utlis*/
		bool	isValidNickname() const;
		bool	isNicknameOrUsernameAvailable(bool useNickname) const;
		bool	isValidRealName() const;
		bool	isValidPassword() const;
		bool	isValidPassword(std::string const &key) const;
		bool	isValidChannelName(std::string const &channelName) const;
    	bool	isValidChannelKey(Channel const *channel, std::string const &key) const;
    	bool	checkInviteOnlyAndNotInvited(Channel const *channel) const;
    	bool	checkChannelFull(Channel const *channel) const;
    	bool	checkTopicRestriction(Channel const *channel) const;
		void	addUserToChannel(Channel *channel) const;
		Channel	*getOrCreateChannel(std::string const &channelName, std::string const &key);
		bool	isValidMode(const std::string &str);
		
	private:
		std::string					_prefix;
		std::string					_name;
		std::vector<std::string>	_args;
		std::string					_trailor;
		Channel						*_targetChannel;
		Client						*_targetClient;
		std::string					_modeSet;
		std::vector<std::string>	_modeArgs;

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
			~CommandInfo() {}
			
    	};

    	typedef std::map<std::string, CommandInfo> CommandMap;
		CommandMap	_commands;
};

#endif