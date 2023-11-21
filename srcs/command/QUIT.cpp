/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:07:51 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/21 15:08:37 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int	Command::QUIT() {
	// message de depart dans le trailor a traiter
	this->_server.setClientToRemove(this->_client.getClientFd());
	return (ERR_NONE);
}