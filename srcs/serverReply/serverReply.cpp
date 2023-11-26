/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReply.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:51:10 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/26 19:59:09 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverReply.hpp"

serverReply::serverReply(Server &server) : _server(server) {}

serverReply::~serverReply() {}

/* ************************************************************************** */

void serverReply::RPL_NOTOPIC(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string msg =	":" + server + " 331 " + client + " " + channel + " :No topic is set";
	
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::RPL_TOPIC(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string const &topic = cmd.getTargetChannel()->getTopic();
	std::string msg =	":" + server + " 332 " + client + " " + channel + " :" + topic;
	
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::RPL_INVITING(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &nick = cmd.getNick();
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string msg =	":" + server + " 341 " + client + " " + nick + " " + channel;
	
	if (!cmd.getTargetChannel()->getTopic().empty()) {
		msg += " :" + cmd.getTargetChannel()->getTopic();
	}
	
	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::RPL_NAMREPLY(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string const &nicks = cmd.getTargetChannel()->getNicknames();
	std::string msg = ":" + server + " 353 " + client + " = " + channel + " :" + nicks;

	setMessageQueue(receiver.getClientFd(), msg);
}

void serverReply::RPL_ENDOFNAMES(Command const &cmd, Client &receiver) {
	std::string const &server = cmd.getClient().getHostname();
	std::string const &client = cmd.getClient().getNicknameOrUsername(true);
	std::string const &channel = cmd.getTargetChannel()->getName();
	std::string msg = ":" + server + " 366 " + client + " " + channel + " :End of /NAMES list";

	setMessageQueue(receiver.getClientFd(), msg);
}

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
	
	if (!cmd.getTrailor().empty()) {
		msg += " " + cmd.getTrailor();
	}

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
	std::string msg =	":" + cmd.getClient().getPrefix() +
						" " + cmd.getName() +
						" " + cmd.getTargetChannel()->getName();

	if (!cmd.getTrailor().empty()) {
		msg += " " + cmd.getTrailor();
	}
	
	return msg;
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
