/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:09:58 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/09 06:14:34 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

#include <string>
#include <set>

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

class Client;

class Channel {
	public:
		Channel(void);
		Channel(Channel const &rhs);
		Channel &operator=(Channel const &rhs);
		~Channel(void);
		
		void	addUser(Client &user, bool asOperator);
		void	delUser(Client &user);
	
		bool	isUser(Client &user);
		bool	isOperator(Client &user);
	
		std::string const	&getTopic(void);
		void				setTopic(std::string const &topicName);

		int		getUserNumber(void);
		
		void	addAllBufToCommand(char const *buffer);

	private:
		std::string			_topic;
		std::set<Client *>	_usersList;
		std::set<Client *>	_operatorsList;
};


#endif