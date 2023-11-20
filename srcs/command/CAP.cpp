/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CAP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:52:22 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/20 21:59:29 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int	Command::CAP() {
	// Server does no handle capability negociation 

	// this->_server.getServerReply()->CAP_RPL(this->_client.getClientFd());
	// this->_server.getServerReply().CAP_RPL(this->_client.getClientFd());
	return (ERR_NONE);
}