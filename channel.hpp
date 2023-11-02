/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:09:58 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/10/31 05:29:36 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <set>

#include "client.hpp"

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

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

		void	addAllBufToCommand(char const *buffer);

	private:
		std::string			_topicName;
		std::set<Client *>	_usersList;
		std::set<Client *>	_operatorsList;
};


#endif