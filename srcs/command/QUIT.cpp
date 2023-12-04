/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:07:51 by ilinhard          #+#    #+#             */
/*   Updated: 2023/12/04 04:39:25 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

void Command::QUIT() {
  this->_server.getServerReply()->LOGOUT(this->_client, this->_trailor);
  this->_server.setClientToRemove(this->_client.getClientFd());
}
