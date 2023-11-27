/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:07:51 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/27 20:07:29 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

int Command::QUIT() {
  // message de depart dans le trailor a traiter
  this->_server.setClientToRemove(this->_client.getClientFd());
  return (ERR_NONE);
}
