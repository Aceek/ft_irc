/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_message.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 03:02:36 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/17 09:19:10 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

std::string Server::getErrorMessage(int errorCode) const {
	// need add system add nickname of user .. 
	switch (errorCode) {
    case ERR_NONE:
        return "No error";
    case ERR_REALNAME:
        return "[RealName] 1: Real Name bad format (max 25 char) + alphanumeric characters only";
    case ERR_PASSFORMAT:
        return "[Password] 2: Password bad format (max 25 char) + alphanumeric characters only";
    case ERR_PASSNEEDED:
        return "[Password] 3: Server password required to log in";
    case ERR_PASSWRONG:
        return "[Password] 4: Password does not match with server's password";
    case ERR_FILEINVALID:
        return "[File] 5: Can't open file";
    case ERR_NOSUCHNICK:
        return "[User] 401: No such nick";
    case ERR_NOSUCHCHANNEL:
        return "[Channel] 403: No such channel";
    case ERR_CANNOTSENDTOCHAN:
        return "[Channel] 404: Cannot send to channel";
	case ERR_NOTEXTTOSEND:
        return "[Command] 412: No text to send";
    case ERR_UNKNOWNCOMMAND:
        return "[Command] 421: Unknown command";
    case ERR_NONICKNAMEGIVEN:
        return "[Nick] 431: No nickname given";
    case ERR_ERRONEUSNICKNAME:
        return "[Nick] 432: Erroneous nickname";
    case ERR_NICKNAMEINUSE:
        return "[Nick] 433: Nickname is already in use";
    case ERR_NICKCOLLISION:
        return "[Nick] 436: Nickname collision KILL";
    case ERR_NOTONCHANNEL:
        return "[Channel] 442: You're not on that channel";
    case ERR_USERONCHANNEL:
        return "[Channel] 443: User already on channel";
    case ERR_NEEDMOREPARAMS:
        return "[Command] 461: Not enough parameters";
    case ERR_ALREADYREGISTRED:
        return "[Password] 462: You may not reregister (already done)";
    case ERR_PASSWDMISMATCH:
        return "[Oper] 464: Password incorrect";
    case ERR_CHANNELISFULL:
        return "[Channel] 471: Cannot join channel (+l)";
	case ERR_UNKNOWNMODE:
		return "[Char] 472: is unknown mode char to me";
    case ERR_INVITEONLYCHAN:
        return "[Channel] 473: Cannot join channel (+i)";
    case ERR_BADCHANNELKEY:
        return "[Channel] 475: Bad channel key";
    case ERR_BADCHANMASK:
        return "[Channel] 476: Bad channel mask";
    case ERR_CHANOPRIVSNEEDED:
        return "[Channel] 482: You're not channel operator";
    case ERR_COMMAND_SIZE:
        return "[Command] 507: Command max format 512 char. Reseting command";
	case ERR_BUFFER_SIZE:
		return( "[BUFFER] : 508 : Error BUFFER maxsize max 512 char, can't add buffer to command");
	default:
        return "Unknown error";
    }
}

std::string	Server::getServerMessage(int messageServer) const {
	std::string message;
	switch (messageServer)
	{
	case ERR_SERVER_SENDING:
		return ("[SENDING] 500 : Error sending message to client");

	case ERR_SERVER_RECV:
		return("[RECEVING] : 501 : Error: receving message from client. Deconection");

	case SERVER_CLOSING:
		return("[SERVER] : 502 : Closing Server ...");

	case SERVER_DELCLIENT:
		return("[CLIENT] : 503 : Client supprimé du server");

	case ERR_SERVER_ACCEPTCLIENT:
		return( "[CLIENT] : 504 : Erreur acceptation du client");

	case SERVER_NEWCLIENT:
		return( "[CLIENT] : 505 : new client on server");

	case ERR_NOENDCARACT:
		return( "[COMMAND] : 506 : Commande pas de caractere de fin");

	case ERR_COMMAND_SIZE:
		return( "[COMMAND] : 507 : Error command size max 512 char, reseting command");

	case ERR_BUFFER_SIZE:
		return( "[BUFFER] : 508 : Error BUFFER maxsize max 512 char, can't add buffer to command");
	
	case ERR_INVALIDFILEPATH:
		return( "[FILE] : 509 : Invalid file path");
	
	default:
		return("Unknow error");

	}
}

void Server::RPL_LIST(Client &client) {
	std::string RPL_LIST =	":server " +
							client.getNicknameOrUsername(true) +
							" =\n" + getChannelsNames();
	
	setMessageQueue(client.getClientFd(), RPL_LIST);
}

void Server::RPL_LISTEND(Client &client) {
    std::string RPL_LISTEND =	":server " +
								client.getNicknameOrUsername(true) +
								" :End of /LIST list.";
								
	setMessageQueue(client.getClientFd(), RPL_LISTEND);
}

void Server::RPL_TOPIC(Channel const &channel, Client &client) {
	std::string RPL_TOPIC =	":server " +
							channel.getName() +
							" :" + (!channel.getTopic().empty() ?
							channel.getTopic() : "No topic is set");
							
	setMessageQueue(client.getClientFd(), RPL_TOPIC);
}

void Server::RPL_NAMREPLY(Channel const &channel, Client &client) {
    std::string RPL_NAMREPLY =	":server " + 
								client.getNicknameOrUsername(true) + 
								" = " + channel.getName() +
								" :" + channel.getNicknames();

   setMessageQueue(client.getClientFd(), RPL_NAMREPLY);
}

void Server::RPL_ENDOFNAMES(Channel const &channel, Client &client) {
    std::string RPL_ENDOFNAMES =	":server " +
									client.getNicknameOrUsername(true) +
									" " + channel.getName() +
									" :End of /NAMES list.";
								
	setMessageQueue(client.getClientFd(), RPL_ENDOFNAMES);
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

