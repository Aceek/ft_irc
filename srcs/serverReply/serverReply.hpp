/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReply.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:51:21 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/24 17:02:22 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERREPLY_HPP
#define SERVERREPLY_HPP

#include "../../include.hpp"


class Command;
typedef  std::map<int, std::deque<std::string> >	messages;

class serverReply
{
private:
	Server		&_server;
	messages	_messageQueue;

public:
	serverReply(Server &server);
	~serverReply();

	// void	RPL_LIST(Client &client);
	// void	RPL_LISTEND(Client &client);
	// void	RPL_TOPIC(Channel const &channel, Client &client);
	// void	RPL_NAMREPLY(Channel const &channel, Client &client);
	// void	RPL_ENDOFNAMES(Channel const &channel, Client &client);
	
    void NOSUCHNICK(Command const &cmd, Client &receiver);
    void NOSUCHCHANNEL(Command const &cmd, Client &receiver);
    void CANNOTSENDTOCHAN(Command const &cmd, Client &receiver);
    void NOTEXTTOSEND(Command const &cmd, Client &receiver);
	void UNKNOWNCOMMAND(Command const &cmd, Client &receiver);
    void USERNOTINCHANNEL(Command const &cmd, Client &receiver);
    void NOTONCHANNEL(Command const &cmd, Client &receiver);
    void USERONCHANNEL(Command const &cmd, Client &receiver);
    void NEEDMOREPARAMS(Command const &cmd, Client &receiver);
    void ALREADYREGISTRED(Command const &cmd, Client &receiver);
    void PASSWDMISMATCH(Command const &cmd, Client &receiver);
    void CHANNELISFULL(Command const &cmd, Client &receiver);
    void UNKNOWNMODE(Command const &cmd, Client &receiver);
    void INVITEONLYCHAN(Command const &cmd, Client &receiver);
    void BADCHANNELKEY(Command const &cmd, Client &receiver);
	void BADCHANMASK(Command const &cmd, Client &receiver);
    void CHANOPRIVSNEEDED(Command const &cmd, Client &receiver);
    void UMODEUNKNOWNFLAG(Command const &cmd, Client &receiver);

	std::string		buildInviteMessage(Command &cmd);
	std::string		buildJoinMessage(Command &cmd);
	std::string		buildPartMessage(Command &cmd);
	std::string		buildKickMessage(Command &cmd);
	std::string		buildPrivmsgMessage(Command &cmd, bool channel);
	std::string		buildModeMessage(Command &cmd);
	std::string		buildTopicMessage(Command &cmd);
	
	void			INVITE(Command &cmd, Client &receiver);
	void			INVITE(Command &cmd, Channel &receiver);
	void			KICK(Command &cmd, Client &receiver);
	void			KICK(Command &cmd, Channel &receiver);
	void			JOIN(Command &cmd, Client &receiver);
	void			JOIN(Command &cmd, Channel &receiver);
	void			PART(Command &cmd, Client &receiver);
	void			PART(Command &cmd, Channel &receiver);
	void			PRIVMSG(Command &cmd, Client &receiver);
	void			PRIVMSG(Command &cmd, Channel &receiver);
	void			MODE(Command &cmd, Client &receiver);
	void			MODE(Command &cmd, Channel &receiver);
	void			TOPIC(Command &cmd, Client &receiver);
	void			TOPIC(Command &cmd, Channel &receiver);

	void			CAP_RPL(const int clientFd);
	void			NICK_RPL(const int errorCode, const Command &command);
	void			NICK_SUCCES(const Client& client, const std::string &oldNick);
	void			WELCOME_RPL(const Client &client);
	void			PONG_RPL(const int errorCode, const Command &command);
	void			PASS_RPL(const int errorCode, const Command &command);
	void			USER_RPL(const int errorCode, const Client &client);	
	void			printServerInput(const std::string &message) const;
	void 			displayClientCommand(const std::string& command, const Client& client) const;
	void			displayServerMessage(messageServer event) const;

	void			sendMessage(const int clientFd, const std::string &message) const;
	void 			verifyMessageSend(const int clientFd);
	void			setMessageQueue(const int clientfd, const std::string &message);
	messages		&getMessageQueue();

	
	

};

#endif // SERVERREPLY_HPP