/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReply.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:51:10 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/25 03:16:45 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverReply.hpp"

serverReply::serverReply(Server &server) : _server(server) {}

serverReply::~serverReply() {}

/* ************************************************************************** */

void serverReply::NOSUCHNICK(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &nick = cmd.getNick();
	std::string msg = ":" + server + " 401 " + client + " " + nick + " :No such nick/channel";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::NOSUCHCHANNEL(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &channel = cmd.getTargetChannelName();
	std::string msg = ":" + server + " 403 " + client + " "  + channel + " :No such channel";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::CANNOTSENDTOCHAN(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string msg = ":" + server + " 404 " + client + " " + channel + " :Cannot send to channel";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::NOTEXTTOSEND(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string msg = ":" + server + " 412 " + client + " :No text to send";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::UNKNOWNCOMMAND(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &command = cmd.getName();
	std::string msg = ":" + server + " 421 " + client + " " + command + " :Unknown command";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::USERNOTINCHANNEL(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &nick = cmd.getNick();
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string msg = ":" + server + " 441 " + client + " " + nick + " " + channel + " :They aren't on that channel";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::NOTONCHANNEL(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string msg = ":" + server + " 442 " + client + " " + channel + " :You're not on that channel";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::USERONCHANNEL(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &nick = cmd.getNick();
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string msg = ":" + server + " 443 " + client + " " + nick + " " + channel + " :is already on channel";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::NEEDMOREPARAMS(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &command = cmd.getName();
	std::string msg = ":" + server + " 461 " + client + " " + command + " :Not enough parameters";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::ALREADYREGISTRED(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string msg = ":" + server + " 462 " + client + " :You may not reregister";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::PASSWDMISMATCH(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string msg = ":" + server + " 464 " + client + " :Password incorrect";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::CHANNELISFULL(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string msg = ":" + server + " 471 " + client + " " + channel + " :Cannot join channel (+l)";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::UNKNOWNMODE(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &modechar = cmd.getModeSet();
	std::string msg = ":" + server + " 472 " + client + " " + modechar + " :is an unknown mode char to me";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::INVITEONLYCHAN(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string msg = ":" + server + " 473 " + client + " " + channel + " :Cannot join channel (+i)";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::BADCHANNELKEY(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string msg = ":" + server + " 475 " + client + " " + channel + " :Cannot join channel (+k)";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::BADCHANMASK(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &channel = cmd.getTargetChannelName();
	std::string msg = ":" + server + " 476 " + channel + " :Bad Channel Mask";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::CHANOPRIVSNEEDED(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string msg = ":" + server + " 482 " + client + " " + channel + " :You're not channel operator";
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::UMODEUNKNOWNFLAG(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string msg = ":" + server + " 501 " + client + " :Unknown MODE flag";
	setMessageQueue(receiver.getClientFd(), msg);
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
	
	if (!cmd.getTrailor().empty()) {
		msg += " :" + cmd.getTrailor();
	}

	return msg;
}

std::string serverReply::buildTopicMessage(Command &cmd) {
	std::string msg =	":" + cmd.getClient().getPrefix() +
						" " + cmd.getName() +
						" " + cmd.getTargetChannel()->getName();
	
	if (!cmd.getTopic().empty()) {
		msg += " " + cmd.getTopic();
	}

	return msg;
}

/* ************************************************************************** */

void serverReply::INVITE(Command &cmd, Client &receiver) {
	const std::string& msg = buildInviteMessage(cmd);
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::INVITE(Command &cmd, Channel &receiver) {
	const std::string& msg = buildInviteMessage(cmd);
	this->_server.sendMessageToChannel(cmd.getClient(), receiver, msg);
}

void serverReply::JOIN(Command &cmd, Client &receiver) {
	std::string msg = buildJoinMessage(cmd);
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::JOIN(Command &cmd, Channel &receiver) {
	std::string msg = buildJoinMessage(cmd);
	this->_server.sendMessageToChannel(cmd.getClient(), receiver, msg);
}

void serverReply::PART(Command &cmd, Client &receiver) {
	const std::string& msg = buildPartMessage(cmd);
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::PART(Command &cmd, Channel &receiver) {
	const std::string& msg = buildPartMessage(cmd);
	this->_server.sendMessageToChannel(cmd.getClient(), receiver, msg);
}

void serverReply::KICK(Command &cmd, Client &receiver) {
	const std::string& msg = buildKickMessage(cmd);
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::KICK(Command &cmd, Channel &receiver) {
	const std::string& msg = buildKickMessage(cmd);
	this->_server.sendMessageToChannel(cmd.getClient(), receiver, msg);
}

void serverReply::MODE(Command &cmd, Client &receiver) {
	const std::string& msg = buildModeMessage(cmd);
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::MODE(Command &cmd, Channel &receiver) {
	const std::string& msg = buildModeMessage(cmd);
	this->_server.sendMessageToChannel(cmd.getClient(), receiver, msg);
}

void serverReply::PRIVMSG(Command &cmd, Client &receiver) {
	const std::string& msg = buildPrivmsgMessage(cmd, false);
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::PRIVMSG(Command &cmd, Channel &receiver) {
	const std::string& msg = buildPrivmsgMessage(cmd, true);
	this->_server.sendMessageToChannel(cmd.getClient(), receiver, msg);
}

void serverReply::TOPIC(Command &cmd, Client &receiver) {
	const std::string& msg = buildTopicMessage(cmd);
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::TOPIC(Command &cmd, Channel &receiver) {
	const std::string& msg = buildTopicMessage(cmd);
	this->_server.sendMessageToChannel(cmd.getClient(), receiver, msg);
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