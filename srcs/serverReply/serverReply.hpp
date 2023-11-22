/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReply.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:51:21 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/22 09:14:11 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERREPLY_HPP
#define SERVERREPLY_HPP

#include "../../include.hpp"

class Command;

class serverReply
{
private:
	Server	&_server;
public:
	serverReply(Server &server);
	~serverReply();

	// void	RPL_LIST(Client &client);
	// void	RPL_LISTEND(Client &client);
	// void	RPL_TOPIC(Channel const &channel, Client &client);
	// void	RPL_NAMREPLY(Channel const &channel, Client &client);
	// void	RPL_ENDOFNAMES(Channel const &channel, Client &client);

	std::string		buildInviteMessage(Command &cmd);
	std::string		buildJoinMessage(Command &cmd);
	std::string		buildPartMessage(Command &cmd);
	std::string		buildKickMessage(Command &cmd);
	std::string		buildPrivmsgMessage(Command &cmd, bool channel);
	std::string		buildModeMessage(Command &cmd);
	std::string		buildTopicMessage(Command &cmd);
	
	void	INVITE(Command &cmd, Client &receiver);
	void	INVITE(Command &cmd, Channel &receiver);
	void	KICK(Command &cmd, Channel &receiver);
	void	JOIN(Command &cmd, Channel &receiver);
	void	PART(Command &cmd, Client &receiver);
	void	PART(Command &cmd, Channel &receiver);
	void	PRIVMSG(Command &cmd, Client &receiver);
	void	PRIVMSG(Command &cmd, Channel &receiver);
	void	MODE(Command &cmd, Channel &receiver);
	void	TOPIC(Command &cmd, Channel &receiver);

	void	CAP_RPL(const int clientFd);
	void	NICK_RPL(const int errorCode, const Command &command);
	void	NICK_SUCCES(const Client& client, const std::string &oldNick);
	void	WELCOME_RPL(const Client &client);
	void	PONG_RPL(const int errorCode, const Command &command);
	void	PASS_RPL(const int errorCode, const Command &command);
	void	USER_RPL(const int errorCode, const Client &client);


	void	printServerInput(const std::string &message) const;
	void 	displayClientCommand(const std::string& command, const Client& client) const;
	

};

#endif // SERVERREPLY_HPP