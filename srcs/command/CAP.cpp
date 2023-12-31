/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CAP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:43:13 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/27 21:11:25 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

void Command::CAP() {
  // Server does not handle capability negociation
  if (this->_args[0] == "LS") {
    this->_server.getServerReply()->CAP_RPL(this->_client.getClientFd());
  }
}
