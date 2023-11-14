/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_message.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 03:02:36 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/14 06:35:45 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

std::string	Server::getServerMessage(int messageServer) const {
	std::string message;
	switch (messageServer)
	{
	case ERR_SERVER_SENDING:
	return ("Error sending message to client");

	case ERR_SERVER_RECV:
	return("Error: receving message from client. Deconection");

	case SERVER_CLOSING:
	return("Closing Server ...");

	case SERVER_DELCLIENT:
	return("Client supprimé du server");

	case ERR_SERVER_ACCEPTCLIENT:
	return( "Erreur acceptation du client");

	case SERVER_NEWCLIENT:
	return( "new client on server");
	
	default:
	return("Unknow error");

	}
}

void	Server::printClientInput(const std::string &message, const Client &client) const {
	
	std::string clientNickname = client.getNicknameOrUsername(true);
	int			clientFd = client.getClientFd();

	std::cout << "[SERVER]: [CLIENT]";
	
	
	if (!clientNickname.empty()) {
		std::cout << "[" << clientNickname << "]: ";
	} else {
		std::cout << "[" << clientFd << "]: ";
	}
	
	std::cout << message << std::endl;
	
}


void	Server::printServerInput(const std::string &message) const {
	std::cout << message << std::endl;
}

