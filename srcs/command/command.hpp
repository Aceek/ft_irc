/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/28 23:32:35 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRCS_COMMAND_COMMAND_HPP_
#define SRCS_COMMAND_COMMAND_HPP_

#include <map>
#include <string>
#include <vector>

#include "../../include.hpp"

class Command {
 public:
  Command(std::string const &line, Client *client, Server *server);
  Command(Command const &rhs);
  Command &operator=(Command const &rhs);
  ~Command(void);

  void initCommandsMap(void);
  void exec();

  void INVITE();
  void JOIN();
  void KICK();
  void MODE();
  void PART();
  void PRIVMSG();
  void TOPIC();
  void USER();
  void NICK();
  void PASS();
  void QUIT();
  void HELP();
  void CAP();
  void PONG();

  /*command_accessors*/
  std::string const &getPrefix(void) const;
  std::string const &getName(void) const;
  std::vector<std::string> const &getArgs(void) const;
  std::string const &getTrailor(void) const;
  Client &getClient(void) const;
  Server &getServer(void) const;
  Channel *getTargetChannel(void) const;
  Client *getTargetClient(void) const;
  std::string const &getTargetChannelName(void) const;
  std::string const &getNick(void) const;
  std::string const &getTopic(void) const;
  std::string const &getModeStr(void) const;
  std::vector<std::string> const &getModeArgs(void) const;

  /*command_utlis*/
  bool isValidNicknameorUsername() const;
  bool isNicknameAvailable(bool useNickname) const;
  bool isValidPassword() const;
  bool isValidPassword(std::string const &key) const;
  bool isValidChannelName(std::string const &channelName) const;
  bool isValidChannelKey(Channel const *channel, std::string const &key) const;
  bool checkInviteOnlyAndNotInvited(Channel const *channel) const;
  bool checkInviteOnlyAndNotOperator(Channel const *channel) const;
  bool checkChannelFull(Channel const *channel) const;
  bool checkTopicRestriction(Channel const *channel) const;
  void addUserToChannel(Channel *channel) const;
  Channel *getOrCreateChannel(std::string const &channelName,
                              std::string const &key);
  bool isValidMode(const std::string &str);
  bool isRecognizedMode(const std::string &str);

 private:
  std::string _command;
  std::string _prefix;
  std::string _name;
  std::vector<std::string> _args;
  std::string _trailor;
  std::string _nick;
  std::string _topic;
  std::string _modeStr;
  std::vector<std::string> _modeArgs;
  std::string _targetChannelName;
  Channel *_targetChannel;
  Client *_targetClient;
  Client &_client;
  Server &_server;

  typedef void (Command::*cmdFt)();

  struct CommandInfo {
    cmdFt func;
    std::string params;

    CommandInfo() {}
    CommandInfo(cmdFt func, std::string const &params)
        : func(func), params(params) {}
    ~CommandInfo() {}
  };

  typedef std::map<std::string, CommandInfo> CommandMap;
  CommandMap _commands;
};

#endif  // SRCS_COMMAND_COMMAND_HPP_
