/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CAP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:43:13 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/27 20:08:17 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

int Command::CAP() {
  // Server does not handle capability negociation
  if (this->_args[0] == "LS") {
    this->_server.getServerReply()->CAP_RPL(this->_client.getClientFd());
  }
  return (ERR_NONE);
}
