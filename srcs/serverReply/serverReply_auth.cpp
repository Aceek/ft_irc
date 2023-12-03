/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReply_auth.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:45:40 by ilinhard          #+#    #+#             */
/*   Updated: 2023/12/04 00:18:58 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/serverReply/serverReply.hpp"

void serverReply::CAP_RPL(const int clientFd) {
  std::string message = ":localhost CAP * LS :";
  setMessageQueue(clientFd, message);
}

void serverReply::NICK_RPL(const int errorCode, const Command &command) {
  Client client = command.getClient();
  std::string replyMessage;
  std::string hostname = "localhost";
  std::string nickAlredyUse = "Unknow";
  if (errorCode != ERR_NONICKNAMEGIVEN) {
    nickAlredyUse = command.getArgs()[0];
  }
  switch (errorCode) {
    case ERR_NONICKNAMEGIVEN:
      replyMessage = ":" + hostname + " 431 * :No nickname given";
      break;
    case ERR_ERRONEUSNICKNAME:
      replyMessage =
          ":" + hostname + " 432 * " + nickAlredyUse + " :Erroneous nickname";
      break;
    case ERR_NICKNAMEINUSE:
      replyMessage = ":" + hostname + " 433 * " + nickAlredyUse +
                     " :Nickname is already in use";
      break;
  }
  setMessageQueue(client.getClientFd(), replyMessage);
}

void serverReply::NICK_SUCCES(const Client &client,
                              const std::string &oldNick) {
  int clientFd = client.getClientFd();
  std::string hostname = "localhost";
  std::string newNickname = client.getNicknameOrUsername(true);

  std::string username = client.getNicknameOrUsername(false);
  if (username.empty()) {
    username = "user";
  }

  std::string message =
      ":" + oldNick + "!" + username + "@" + hostname + " NICK :" + newNickname;

  setMessageQueue(clientFd, message);
}

void serverReply::USER_RPL(const int errorCode, const Client &client) {
  std::string replyMessage;

  switch (errorCode) {
    case ERR_ALREADYREGISTERED:
      replyMessage =
          ":localhost 462 * :Unauthorized command (already registered)";
      break;
    case ERR_NEEDMOREPARAMS:
      replyMessage = ":localhost 461 * USER :Not enough parameters";
      break;
    case ERR_ERRONEUSNICKNAME:
      replyMessage = ":localhost 432 * :Erroneous nickname";
      break;
  }

  setMessageQueue(client.getClientFd(), replyMessage);
}

void serverReply::WELCOME_RPL(const Client &client) {
  std::string serverName = "localhost";
  std::string nick = client.getNicknameOrUsername(true);
  std::string user = client.getNicknameOrUsername(false);

  std::string message = ":" + serverName + " 001 " + nick +
                        " :Welcome to the ft_irc Network, " + nick;

  if (!user.empty() && !serverName.empty()) {
    message += "!" + user + "@" + serverName;
  }

  setMessageQueue(client.getClientFd(), message);
}

void serverReply::MAX_CLIENT(const Client &client) {
  std::string serverName = "localhost";

  std::string message =
      ":" + serverName + "  Can't connect to server : Max user reach";

  setMessageQueue(client.getClientFd(), message);
}

void serverReply::PONG_RPL(const int errorCode, const Command &command) {
  std::string replyMessage;
  std::string nick = command.getClient().getNicknameOrUsername(true);
  if (nick.empty()) {
    nick = "unknow";
  }

  switch (errorCode) {
    case ERR_NEEDMOREPARAMS:
      replyMessage = ":localhost 461 * PING :Not enough parameters";
      break;
    case RPL_PONG:
      replyMessage = ":localhost PONG " + command.getArgs()[0] + " :" + nick;
      break;
  }

  setMessageQueue(command.getClient().getClientFd(), replyMessage);
}

void serverReply::PASS_RPL(const int errorCode, const Command &command) {
  Client client = command.getClient();
  std::string replyMessage;
  std::string hostname = "localhost";

  switch (errorCode) {
    case ERR_NEEDMOREPARAMS:
      replyMessage = ":" + hostname + " 461 * PASS :Not enough parameters";
      break;
    case ERR_ALREADYREGISTERED:
      replyMessage =
          ":" + hostname + " 462 * :Unauthorized command (already registered)";
      break;
    case ERR_PASSWDMISMATCH:
      replyMessage = ":" + hostname + " 464 * :Password incorrect";
      break;
  }

  setMessageQueue(client.getClientFd(), replyMessage);
}

void serverReply::LOGOUT(const Client &client) {
  std::string hostname = "localhost";
  std::string replyMessage = ":" + hostname + " QUIT :Deconection server";

  sendMessage(client.getClientFd(), replyMessage);
}

void serverReply::LOGOUT(const Client &client, std::string msg) {
  std::string hostname = "localhost";
  if (msg.empty()) {
	msg = "Deconection server";
  }
  std::string replyMessage = ":" + hostname + " QUIT :" + msg;

  sendMessage(client.getClientFd(), replyMessage);
}
