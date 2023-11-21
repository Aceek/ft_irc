/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReply.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:51:10 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/21 21:47:00 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverReply.hpp"

serverReply::serverReply(Server &server) : _server(server) {}

serverReply::~serverReply() {}

/* ************************************************************************** */

void serverReply::NOSUCHNICK(Command const &cmd, std::string const &nick, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
	std::string msg = client + " 401 * " + nick + " :No such nick/channel";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::NOSUCHCHANNEL(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string const &channel = cmd.getTargetChannel()->getName();
    std::string msg = client + " 403 * "  + channel + " :No such channel";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::CANNOTSENDTOCHAN(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string const &channel = cmd.getTargetChannel()->getName();
    std::string msg = client + " 404 * "  + channel + " :Cannot send to channel";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::NOTEXTTOSEND(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string msg = client + " 412 * :No text to send";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::UNKNOWNCOMMAND(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string const &command = cmd.getName();
    std::string msg = client + " 421 * "  + command + " :Unknown command";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::NOTONCHANNEL(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string const &channel = cmd.getTargetChannel()->getName();
    std::string msg = client + " 442 * "  + channel + " :You're not on that channel";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::USERONCHANNEL(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string const &nick = cmd.getClient().getNicknameOrUsername(true);
    std::string const &channel = cmd.getTargetChannel()->getName();
    std::string msg = client + " 443 * "  + nick + " " + channel + " :is already on channel";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::NEEDMOREPARAMS(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string const &command = cmd.getName();
    std::string msg = client + " 461 * "  + command + " :Not enough parameters";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::ALREADYREGISTRED(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string msg = client + " 462 * :You may not reregister";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::PASSWDMISMATCH(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string msg = client + " 464 * :Password incorrect";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::CHANNELISFULL(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string const &channel = cmd.getTargetChannel()->getName();
    std::string msg = client + " 471 * "  + channel + " :Cannot join channel (+l)";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::UNKNOWNMODE(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string const &modechar = cmd.getModeSet();
    std::string msg = client + " 472 * "  + modechar + " :is an unknown mode char to me";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::INVITEONLYCHAN(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string const &channel = cmd.getTargetChannel()->getName();
    std::string msg = client + " 473 * "  + channel + " :Cannot join channel (+i)";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::BADCHANNELKEY(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string const &channel = cmd.getTargetChannel()->getName();
    std::string msg = client + " 475 * "  + channel + " :Cannot join channel (+k)";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::BADCHANMASK(std::string const &channel, Client &receiver) {
    std::string msg = channel + " 476 * :Bad Channel Mask";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::CHANOPRIVSNEEDED(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string const &channel = cmd.getTargetChannel()->getName();
    std::string msg = client + " 482 * "  + channel + " :You're not channel operator";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::UMODEUNKNOWNFLAG(Command const &cmd, Client &receiver) {
    std::string const &client = cmd.getClient().getPrefix();
    std::string msg = client + " 501 * :Unknown MODE flag";
    this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

/* ************************************************************************** */


std::string serverReply::buildInviteMessage(Command &cmd) {
	return ":" + cmd.getClient().getPrefix() +
		   " " + cmd.getName() +
		   " " + cmd.getTargetClient()->getNicknameOrUsername(true) +
		   " " + cmd.getTargetChannel()->getName();
}

std::string serverReply::buildJoinMessage(Command &cmd) {
	return ":" + cmd.getClient().getPrefix() +
		   " " + cmd.getName() +
		   " " + cmd.getTargetChannel()->getName();
}

std::string serverReply::buildKickMessage(Command &cmd) {
	std::string msg =	":" + cmd.getClient().getPrefix() +
						" " + cmd.getName() +
						" " + cmd.getTargetChannel()->getName() +
						" " + cmd.getTargetClient()->getNicknameOrUsername(true);
	
	msg += (!cmd.getTrailor().empty()) ? " :" + cmd.getTrailor() : "";
	
	return msg;
}

std::string serverReply::buildModeMessage(Command &cmd) {
	std::string msg =	":" + cmd.getClient().getPrefix() +
						" " + cmd.getName() +
						" " + cmd.getTargetChannel()->getName() +
						" " + cmd.getModeSet();
	
	for (std::vector<std::string>::const_iterator it = cmd.getModeArgs().begin();
		it != cmd.getModeArgs().end(); ++it) {
		msg += " " + *it;
	}

	return msg;
}

std::string serverReply::buildPartMessage(Command &cmd) {
	return	":" + cmd.getClient().getPrefix() +
			" " + cmd.getName() +
			" " + cmd.getTargetChannel()->getName();
}

std::string serverReply::buildPrivmsgMessage(Command &cmd, bool channel) {
	std::string msg =	":" + cmd.getClient().getPrefix() +
						" " + cmd.getName() +
						" ";
	

	msg += (channel) ? cmd.getTargetChannel()->getName() : 
		cmd.getTargetClient()->getNicknameOrUsername(true); 
	
	msg += (!cmd.getTrailor().empty()) ? " :" + cmd.getTrailor() : "";

	return msg;
}

std::string serverReply::buildTopicMessage(Command &cmd) {
	std::string msg =	":" + cmd.getClient().getPrefix() +
						" " + cmd.getName() +
						" " + cmd.getTargetChannel()->getName();
	
	//check if trailor null to clear topic ? see doc command for topic
	msg += (!cmd.getTrailor().empty()) ? " :" + cmd.getTrailor() : "";

	return msg;
}

/* ************************************************************************** */

void serverReply::INVITE(Command &cmd, Client &receiver) {
	const std::string& msg = buildInviteMessage(cmd);
	this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::INVITE(Command &cmd, Channel &receiver) {
	const std::string& msg = buildInviteMessage(cmd);
	this->_server.sendMessageToChannel(receiver, msg);
}

void serverReply::JOIN(Command &cmd, Channel &receiver) {
	std::string msg = buildJoinMessage(cmd);
	this->_server.sendMessageToChannel(receiver, msg);
}

void serverReply::PART(Command &cmd, Client &receiver) {
	const std::string& msg = buildPartMessage(cmd);
	this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::PART(Command &cmd, Channel &receiver) {
	const std::string& msg = buildPartMessage(cmd);
	this->_server.sendMessageToChannel(receiver, msg);
}

void serverReply::KICK(Command &cmd, Channel &receiver) {
	const std::string& msg = buildKickMessage(cmd);
	this->_server.sendMessageToChannel(receiver, msg);
}

void serverReply::MODE(Command &cmd, Channel &receiver) {
	const std::string& msg = buildModeMessage(cmd);
	this->_server.sendMessageToChannel(receiver, msg);
}

void serverReply::PRIVMSG(Command &cmd, Client &receiver) {
	const std::string& msg = buildPrivmsgMessage(cmd, false);
	this->_server.setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::PRIVMSG(Command &cmd, Channel &receiver) {
	const std::string& msg = buildPrivmsgMessage(cmd, true);
	this->_server.sendMessageToChannel(receiver, msg);
}

void serverReply::TOPIC(Command &cmd, Channel &receiver) {
	const std::string& msg = buildTopicMessage(cmd);
	this->_server.sendMessageToChannel(receiver, msg);
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