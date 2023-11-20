/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReply.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:51:10 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/20 16:55:01 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverReply.hpp"

serverReply::serverReply() {}
serverReply::serverReply(Server *server) : _server(server) {}

serverReply::~serverReply() {}

/* ************************************************************************** */

std::string serverReply::buildInviteMessage(Command &cmd) {
    return ":" + cmd.getClient().getPrefix() +
           " " + cmd.getName() +
           " " + cmd.getTargetClient().getNicknameOrUsername(true) +
           " " + cmd.getTargetChannel().getName();
}

std::string serverReply::buildJoinMessage(Command &cmd) {
    return ":" + cmd.getClient().getPrefix() +
           " " + cmd.getName() +
           " " + cmd.getTargetChannel().getName();
}

std::string serverReply::buildKickMessage(Command &cmd) {
	std::string msg =	":" + cmd.getClient().getPrefix() +
            			" " + cmd.getName() +
						" " + cmd.getTargetChannel().getName() +
						" " + cmd.getTargetClient().getNicknameOrUsername(true);
	
	msg += (!cmd.getTrailor().empty()) ? " :" + cmd.getTrailor() : "";
	
	return msg;
}

std::string serverReply::buildPartMessage(Command &cmd) {
	return	":" + cmd.getClient().getPrefix() +
            " " + cmd.getName() +
			" " + cmd.getTargetChannel().getName();
}

std::string serverReply::buildPrivmsgMessage(Command &cmd, bool channel) {
	std::string msg =	":" + cmd.getClient().getPrefix() +
            			" " + cmd.getName() +
						" ";
	
	msg += (channel) ? cmd.getTargetChannel().getName() : 
		cmd.getTargetClient().getNicknameOrUsername(true);
	
	msg += (!cmd.getTrailor().empty()) ? " :" + cmd.getTrailor() : "";

	return msg;
}

std::string serverReply::buildTopicMessage(Command &cmd) {
	std::string msg =	":" + cmd.getClient().getPrefix() +
            			" " + cmd.getName() +
						" " + cmd.getTargetChannel().getName();
	
	//check if trailor null to clear topic ? see doc command for topic
	msg += (!cmd.getTrailor().empty()) ? " :" + cmd.getTrailor() : "";

	return msg;
}

void serverReply::INVITE(Command &cmd, Client &receiver) {
    const std::string& msg = buildInviteMessage(cmd);
    this->_server->setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::INVITE(Command &cmd, Channel &receiver) {
    const std::string& msg = buildInviteMessage(cmd);
    this->_server->sendMessageToChannel(receiver, msg);
}

void serverReply::JOIN(Command &cmd, Channel &receiver) {
    const std::string& msg = buildInviteMessage(cmd);
    this->_server->sendMessageToChannel(receiver, msg);
}

void serverReply::PART(Command &cmd, Client &receiver) {
    const std::string& msg = buildInviteMessage(cmd);
    this->_server->setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::PART(Command &cmd, Channel &receiver) {
    const std::string& msg = buildInviteMessage(cmd);
    this->_server->sendMessageToChannel(receiver, msg);
}

void serverReply::KICK(Command &cmd, Channel &receiver) {
    const std::string& msg = buildKickMessage(cmd);
    this->_server->sendMessageToChannel(receiver, msg);
}

void serverReply::PRIVMSG(Command &cmd, Client &receiver) {
    const std::string& msg = buildPrivmsgMessage(cmd, true);
    this->_server->setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::PRIVMSG(Command &cmd, Channel &receiver) {
    const std::string& msg = buildPrivmsgMessage(cmd, false);
    this->_server->sendMessageToChannel(receiver, msg);
}

void serverReply::TOPIC(Command &cmd, Channel &receiver) {
    const std::string& msg = buildTopicMessage(cmd);
    this->_server->sendMessageToChannel(receiver, msg);
}

// void Server::RPL_LIST(Client &client) {
	
// 	std::string RPL_LIST =	":server " +
// 							client.getNicknameOrUsername(true) +
// 							" =\n" + getChannelsNames();
	
// 	setMessageQueue(client.getClientFd(),  RPL_LIST);
// }

// void Server::RPL_LISTEND(Client &client) {
//     std::string RPL_LISTEND =	":server " +
// 								client.getNicknameOrUsername(true) +
// 								" :End of /LIST list.";
								
// 	setMessageQueue(client.getClientFd(), RPL_LISTEND);
// }

// void Server::RPL_TOPIC(Channel const &channel, Client &client) {
// 	std::string RPL_TOPIC =	":server " +
// 							channel.getName() +
// 							" :" + (!channel.getTopic().empty() ?
// 							channel.getTopic() : "No topic is set");
							
// 	setMessageQueue(client.getClientFd(), RPL_TOPIC);
// }

// void Server::RPL_NAMREPLY(Channel const &channel, Client &client) {
//     std::string RPL_NAMREPLY =	":server " + 
// 								client.getNicknameOrUsername(true) + 
// 								" = " + channel.getName() +
// 								" :" + channel.getNicknames();

//    setMessageQueue(client.getClientFd(), RPL_NAMREPLY);
// }

// void Server::RPL_ENDOFNAMES(Channel const &channel, Client &client) {
//     std::string RPL_ENDOFNAMES =	":server " +
// 									client.getNicknameOrUsername(true) +
// 									" " + channel.getName() +
// 									" :End of /NAMES list.";
								
// 	setMessageQueue(client.getClientFd(), RPL_ENDOFNAMES);
// }