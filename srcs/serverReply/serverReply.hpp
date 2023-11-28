/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReply.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:51:21 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/28 03:23:05 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRCS_SERVERREPLY_SERVERREPLY_HPP_
#define SRCS_SERVERREPLY_SERVERREPLY_HPP_

#include <deque>
#include <map>
#include <string>
#include "../../include.hpp"

class Command;
typedef std::map<int, std::deque<std::string> > messages;

class serverReply {
 private:
  Server &_server;
  messages _messageQueue;

 public:
  explicit serverReply(Server *server);
  ~serverReply();

  void RPL_CHANNELMODEIS(Command const &cmd, const Client &receiver);
  void RPL_NOTOPIC(Command const &cmd, const Client &receiver);
  void RPL_TOPIC(Command const &cmd, const Client &receiver);
  void RPL_INVITING(Command const &cmd, const Client &receiver);
  void RPL_NAMREPLY(Command const &cmd, const Client &receiver);
  void RPL_ENDOFNAMES(Command const &cmd, const Client &receiver);
  void NOSUCHNICK(Command const &cmd, const Client &receiver);
  void NOSUCHCHANNEL(Command const &cmd, const Client &receiver);
  void CANNOTSENDTOCHAN(Command const &cmd, const Client &receiver);
  void NOTEXTTOSEND(Command const &cmd, const Client &receiver);
  void UNKNOWNCOMMAND(Command const &cmd, const Client &receiver);
  void USERNOTINCHANNEL(Command const &cmd, const Client &receiver);
  void NOTONCHANNEL(Command const &cmd, const Client &receiver);
  void USERONCHANNEL(Command const &cmd, const Client &receiver);
  void NEEDMOREPARAMS(Command const &cmd, const Client &receiver);
  void ALREADYREGISTRED(Command const &cmd, const Client &receiver);
  void PASSWDMISMATCH(Command const &cmd, const Client &receiver);
  void CHANNELISFULL(Command const &cmd, const Client &receiver);
  void UNKNOWNMODE(Command const &cmd, const Client &receiver);
  void INVITEONLYCHAN(Command const &cmd, const Client &receiver);
  void BADCHANNELKEY(Command const &cmd, const Client &receiver);
  void BADCHANMASK(Command const &cmd, const Client &receiver);
  void CHANOPRIVSNEEDED(Command const &cmd, const Client &receiver);
  void UMODEUNKNOWNFLAG(Command const &cmd, const Client &receiver);

  std::string buildInviteMessage(const Command &cmd);
  std::string buildJoinMessage(const Command &cmd);
  std::string buildPartMessage(const Command &cmd);
  std::string buildKickMessage(const Command &cmd);
  std::string buildPrivmsgMessage(const Command &cmd, bool channel);
  std::string buildModeMessage(const Command &cmd);
  std::string buildTopicMessage(const Command &cmd);

  void INVITE(const Command &cmd, const Client &receiver);
  void INVITE(const Command &cmd, const Channel &receiver);
  void KICK(const Command &cmd, const Client &receiver);
  void KICK(const Command &cmd, const Channel &receiver);
  void JOIN(const Command &cmd, const Client &receiver);
  void JOIN(const Command &cmd, const Channel &receiver);
  void PART(const Command &cmd, const Client &receiver);
  void PART(const Command &cmd, const Channel &receiver);
  void PRIVMSG(const Command &cmd, const Client &receiver);
  void PRIVMSG(const Command &cmd, const Channel &receiver);
  void MODE(const Command &cmd, const Client &receiver);
  void MODE(const Command &cmd, const Channel &receiver);
  void TOPIC(const Command &cmd, const Client &receiver);
  void TOPIC(const Command &cmd, const Channel &receiver);

  void CAP_RPL(const int clientFd);
  void NICK_RPL(const int errorCode, const Command &command);
  void NICK_SUCCES(const Client &client, const std::string &oldNick);
  void WELCOME_RPL(const Client &client);
  void PONG_RPL(const int errorCode, const Command &command);
  void PASS_RPL(const int errorCode, const Command &command);
  void USER_RPL(const int errorCode, const Client &client);
  void LOGOUT(const Client &client);
  void printServerInput(const std::string &message) const;
  void displayClientCommand(const std::string &command,
                            const Client &client) const;
  void displayServerMessage(messageServer event) const;

  void sendMessage(const int clientFd, const std::string &message) const;
  void sendMessageToChannel(Client const &sender, Channel const &channel,
                            std::string const &message);

  void verifyMessageSend(const int clientFd);
  void setMessageQueue(const int clientfd, const std::string &message);
  messages &getMessageQueue();
};

#endif  // SRCS_SERVERREPLY_SERVERREPLY_HPP_
