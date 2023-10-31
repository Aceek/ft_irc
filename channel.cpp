/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:09:58 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/10/31 02:04:04 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <list>

#include "client.hpp"

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

class Channel {
	public:
		Channel(void);
		Channel(Channel const &rhs);
		Channel &operator=(Channel const &rhs);
		~Channel(void);
		
		void	addUser(Client const &user);
		void	delUser(Client const &user);
	
		std::string const	&getTopic(void);
		void				setTopic(std::string const &topicName);

	private:
		std::string			_topic;
		std::list<Client *>	_usersList;
		std::list<Client *>	_operatorsList;
};


#endif