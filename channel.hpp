/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:09:58 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/10 06:13:51 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "server.hpp"

#include <string>
#include <set>

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

class Client;
class Server;

class Channel {
	public:
		Channel(void);
		Channel(Server *server);
		Channel(Channel const &rhs);
		Channel &operator=(Channel const &rhs);
		~Channel(void);
		
		void	addUser(Client &user, bool asOperator);
		void	delUser(Client &user);
		bool	isUser(Client &user);
		bool	isOperator(Client &user);
	
		std::string const	&getTopic(void);
		void				setTopic(std::string const &topic);
		std::string const	&getKey(void);
		void				setKey(std::string const &key);
		int					getUsersNumber(void);
		std::string const	getUsersNick(void);
		
		void	sendMessageToAll(const std::string &message);
   		void	RPL_TOPIC(Client &user);
    	void	RPL_NAMREPLY(Client &user);
    	void	RPL_ENDOFNAMES(Client &user);

	private:
		std::string			_topic;
		std::string			_key;
		std::set<Client *>	_membersList;
		std::set<Client *>	_operatorsList;
		
		Server				*_server;
};


#endif