/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:48:24 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/15 06:18:10 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int Command::LIST() {
	this->_server.RPL_LIST(this->_client);
	this->_server.RPL_LISTEND(this->_client);

    return ERR_NONE;
}