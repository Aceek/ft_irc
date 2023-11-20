/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReply.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:51:21 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/20 15:44:45 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERREPLY_HPP
#define SERVERREPLY_HPP

#include "../../include.hpp"

class Command;

class serverReply
{
private:
	Server	*_server;
public:
	serverReply();
	serverReply(Server *server);
	~serverReply();

	// void	RPL_LIST(Client &client);
	// void	RPL_LISTEND(Client &client);
	// void	RPL_TOPIC(Channel const &channel, Client &client);
	// void	RPL_NAMREPLY(Channel const &channel, Client &client);
	// void	RPL_ENDOFNAMES(Channel const &channel, Client &client);

	std::string		buildInviteMessage(Command &cmd);
	std::string		buildJoinMessage(Command &cmd);
	std::string		buildPartMessage(Command &cmd);
	
	void	INVITE(Command &cmd, Client &receiver);
	void	INVITE(Command &cmd, Channel &receiver);
	void	JOIN(Command &cmd, Channel &receiver);
	void	PART(Command &cmd, Client &receiver);
	void	PART(Command &cmd, Channel &receiver);
};

#endif // SERVERREPLY_HPP