/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/22 08:44:18 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int	Command::PASS() {
    serverReply *serverReply = this->_server.getServerReply();

    if (this->_client.isPasswordSetUp()) {
        serverReply->PASS_RPL(ERR_ALREADYREGISTERED, *this);
		QUIT();
        return (ERR_ALREADYREGISTERED);
    }
    if (this->_args.empty() || this->_args[0].empty()) {
        serverReply->PASS_RPL(ERR_NEEDMOREPARAMS, *this);
		QUIT();
        return (ERR_NEEDMOREPARAMS);
    }
    if (!isValidPassword()) {
        serverReply->PASS_RPL(ERR_PASSWDMISMATCH, *this);
		QUIT();
        return (ERR_PASSWDMISMATCH);
    }
    if (this->_args[0] != this->_server.getPassword()) {
        serverReply->PASS_RPL(ERR_PASSWDMISMATCH, *this);
		QUIT();
        return (ERR_PASSWDMISMATCH);
    }
    this->_client.setPassRegister();
    return (ERR_NONE);
}
