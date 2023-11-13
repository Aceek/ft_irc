/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:49:03 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 11:11:31 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::USER() {
	bool useNickname = false;
	if (this->_client.isRegister()) {
		return (ERR_ALREADYREGISTRED);
	}
	if (this->_args.empty() || this->_args[0].empty() || this->_trailor.empty()) {
		return (ERR_NEEDMOREPARAMS);
	} else if (!isValidNickname()) {
		return (ERR_ERRONEUSNICKNAME);
	} else if (!isNicknameOrUsernameAvailable(useNickname)) {
		return (ERR_NICKNAMEINUSE);
	} else if (!isValidRealName()) {
		return (ERR_REALNAME);
	}
	this->_client.setRealName(this->_trailor);
	this->_client.setUsername(this->_args[0]);
	this->_client.setRegister();
	this->_server.setMessageQueue(this->_client.getClientFd(),
	"User successfully register: " + this->_args[0]);
	
	return(ERR_NONE);
}
