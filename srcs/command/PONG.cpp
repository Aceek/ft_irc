/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PONG.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:06:41 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/21 15:08:31 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int	Command::PONG() {
	serverReply *serverReply = this->_server.getServerReply();
	if (this->_args.empty() || this->_args[0].empty()) {
		serverReply->PONG_RPL(ERR_NEEDMOREPARAMS, *this);
	} else {
		serverReply->PONG_RPL(RPL_PONG, *this);
	}
	return (ERR_NONE);
}