/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:49:03 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/21 02:31:57 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::USER() {
    serverReply* serverReply = this->_server.getServerReply();

    if (this->_client.isUserRegister()) {
        serverReply->USER_RPL(ERR_ALREADYREGISTRED, this->_client);
        return (ERR_ALREADYREGISTRED);
    }
    if (this->_args.empty() || this->_args[0].empty() || this->_trailor.empty()) {
        serverReply->USER_RPL(ERR_NEEDMOREPARAMS, this->_client);
        return (ERR_NEEDMOREPARAMS);
    } 
	if (!isValidNicknameorUsername()) {
		return (ERR_ERRONEUSNICKNAME);
	}

    this->_client.setRealName(this->_trailor);
    this->_client.setUsername(this->_args[0]);
    this->_client.setUserRegister();

	if (this->_client.isNickRegister() && this->_client.isUserRegister()) {
		serverReply->WELCOME_RPL(this->_client);
	}

    return (ERR_NONE);
}
