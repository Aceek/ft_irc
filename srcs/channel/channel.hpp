/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:09:58 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/12/04 06:29:30 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <set>
#include "../../include.hpp"

#ifndef SRCS_CHANNEL_CHANNEL_HPP_
#define SRCS_CHANNEL_CHANNEL_HPP_

class Client;
class Server;
class Bot;

class Channel {
 public:
  Channel(void);
  Channel(Channel const &rhs);
  Channel &operator=(Channel const &rhs);
  ~Channel(void);

  void init(std::string const &channelName, Server *server);
  void addUser(Client *client, bool asOperator);
  void delUser(Client *client);
  void inviteUser(Client *client);
  void updateModeInfo(const std::string &modeStr,
    const std::vector<std::string> &modeArgs);


  /*channel_accessors*/
  std::string const &getName(void) const;
  std::string const &getTopic(void) const;
  void setTopic(std::string const &topic);
  std::string const &getKey(void) const;
  void setKey(std::string const &key);
  int getCount(void) const;
  std::string const getNicknames(void) const;
  bool getInviteOnly(void) const;
  void setInviteOnly(bool inviteOnly);
  bool getTopicRestricted(void) const;
  void setTopicRestricted(bool topicRestricted);
  int getUserLimit(void) const;
  void setUserLimit(int userLimit);
  std::set<Client *> const &getUsers(void) const;
  std::set<Client *> const &getOperators(void) const;
  std::string const &getModeStr() const;
  void setModeStr(std::string const &modeStr);
  std::string const &getModeArgs(void) const;
  void setModeArgs(std::string const &modeArgs);
  Bot *getBot(void) const;

  /*channel_utils*/
  bool isUser(Client *client) const;
  bool isOperator(Client *client) const;
  bool isClientPresent(Client *client) const;
  bool isClientInvited(Client *client) const;
  bool hasModeArgs(const char &c);

 private:
  std::string _name;
  std::string _topic;
  std::string _key;
  bool _inviteOnly;
  bool _topicRestricted;
  int _userLimit;
  std::string _modeStr;
  std::string _modeArgs;
  std::map<char, std::string> _modeInfo;
  std::set<Client *> _users;
  std::set<Client *> _invitedUsers;
  std::set<Client *> _operators;
  Bot *_bot;
  Server *_server;
};

#endif  // SRCS_CHANNEL_CHANNEL_HPP_
