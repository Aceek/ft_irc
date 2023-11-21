/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:27 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/21 04:32:15 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"


int Command::NICK() {
    serverReply* serverReply = this->_server.getServerReply();

    if (this->_args.empty() || this->_args[0].empty()) {
        serverReply->NICK_RPL(ERR_NONICKNAMEGIVEN, *this);
        return (ERR_NONICKNAMEGIVEN);
    } else if (!isValidNicknameorUsername()) {
        serverReply->NICK_RPL(ERR_ERRONEUSNICKNAME, *this);
        return (ERR_ERRONEUSNICKNAME);
    } else if (!isNicknameAvailable(true)) {
        serverReply->NICK_RPL(ERR_NICKNAMEINUSE, *this);
        return (ERR_NICKNAMEINUSE);
    }
	
    std::string oldNickname = this->_client.getNicknameOrUsername(true);

	if (oldNickname.empty()) {
		std::ostringstream ss;
		ss << this->_client.getClientFd();
		oldNickname = ss.str();
	}
    this->_client.setNickname(this->_args[0]);
	serverReply->NICK_SUCCES(this->_client, oldNickname);

	if (!this->_client.isNickRegister() && this->_client.isUserRegister()) {
		serverReply->WELCOME_RPL(this->_client);
	}
	this->_client.setNickRegister();

    return (ERR_NONE);
}
