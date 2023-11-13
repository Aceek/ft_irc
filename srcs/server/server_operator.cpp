/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_operator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:51:53 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 04:53:28 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::grantOperatorStatus(int clientFd) {
    this->_operatorClients.insert(clientFd);
}

void Server::revokeOperatorStatus(int clientFd) {
    this->_operatorClients.erase(clientFd);
}

bool Server::isOperator(int clientFd) const {
    return this->_operatorClients.count(clientFd);
}