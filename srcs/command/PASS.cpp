/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/27 21:08:50 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

void Command::PASS() {
  serverReply *serverReply = this->_server.getServerReply();

  if (this->_client.isPasswordSetUp()) {
    serverReply->PASS_RPL(ERR_ALREADYREGISTERED, *this);
    QUIT();
    return;
  }
  if (this->_args.empty() || this->_args[0].empty()) {
    serverReply->PASS_RPL(ERR_NEEDMOREPARAMS, *this);
    QUIT();
    return;
  }
  if (!isValidPassword()) {
    serverReply->PASS_RPL(ERR_PASSWDMISMATCH, *this);
    QUIT();
    return;
  }
  if (this->_args[0] != this->_server.getPassword()) {
    serverReply->PASS_RPL(ERR_PASSWDMISMATCH, *this);
    QUIT();
    return;
  }
  this->_client.setPassRegister();
}
