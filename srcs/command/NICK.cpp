/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:27 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 11:11:57 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int	Command::NICK() {
	bool useNickname = true;
	if (this->_args.empty() || this->_args[0].empty()) {
		return (ERR_NONICKNAMEGIVEN);
	} else if (!isValidNickname()) {
		return (ERR_ERRONEUSNICKNAME);
	} else if (!isNicknameOrUsernameAvailable(useNickname)) {
		return (ERR_NICKNAMEINUSE);
	}
	this->_client.setNickname(this->_args[0]);
	this->_server.setMessageQueue(this->_client.getClientFd(),
	"NICK updated successfully: " + this->_args[0]);
	return(ERR_NONE);
}
