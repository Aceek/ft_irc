/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:17:58 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/28 05:48:09 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/channel/channel.hpp"

bool Channel::isUser(Client *client) const {
  return this->_users.find(client) != this->_users.end();
}

bool Channel::isOperator(Client *client) const {
  return this->_operators.find(client) != this->_operators.end();
}

bool Channel::isClientPresent(Client *client) const {
  return isUser(client) || isOperator(client);
}

bool Channel::isClientInvited(Client *client) const {
  return this->_invitedUsers.find(client) != this->_invitedUsers.end();
}

bool Channel::hasModeArgs(const char &c) {
	return c == 'k'  || c == 'l';
}
