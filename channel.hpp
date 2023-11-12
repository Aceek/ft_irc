/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:09:58 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/12 05:57:57 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.hpp"

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

class Client;
class Server;

class Channel {
	public:
		Channel(void);
		Channel(std::string const &name, Server *server);
		Channel(Channel const &rhs);
		Channel &operator=(Channel const &rhs);
		~Channel(void);
		
		void	addUser(Client &client, bool asOperator);
		void	delUser(Client &client);
		void	inviteUser(Client &client);
		
		bool	isUser(Client &client) const;
		bool	isOperator(Client &client) const;
		bool	isClientPresent(Client &client) const;
		bool	isClientInvited(Client &client) const;
	
		std::string const	&getTopic(void) const;
		void				setTopic(std::string const &topic);
		std::string const	&getKey(void) const;
		void				setKey(std::string const &key);
		int					getCount(void) const;
		std::string const	getNicknames(void) const;
		bool 				getInviteOnly(void) const;
		void 				setInviteOnly(bool inviteOnly);
		
		void	sendMessageToAll(const std::string &message) const;
   		void 	RPL_NOTOPIC(Client &client) const;
		void	RPL_TOPIC(Client &client) const;
    	void	RPL_NAMREPLY(Client &client) const;
    	void	RPL_ENDOFNAMES(Client &client) const;

	private:
		std::string			_name;
		std::string			_topic;
		std::string			_key;
		std::set<Client *>	_users;
		std::set<Client *>	_invitedUsers;
		std::set<Client *>	_operators;
		bool 				_inviteOnly;
		Server				*_server;
};


#endif