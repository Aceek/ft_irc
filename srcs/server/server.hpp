/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:48 by ilinhard          #+#    #+#             */
/*   Updated: 2023/12/04 00:55:11 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRCS_SERVER_SERVER_HPP_
#define SRCS_SERVER_SERVER_HPP_

#include <deque>
#include <map>
#include <string>
#include <vector>

#include "../../include.hpp"

class Client;
class Channel;
class serverReply;

#define MAX_COMMAND_SIZE 512
#define MAX_CLIENTS_NUMBER 15

extern bool serverShutdown;
typedef std::map<const int, Client> ClientMap;
typedef std::map<std::string, Channel> ChannelMap;
typedef std::map<int, std::deque<std::string> > messages;

class Server {
 public:
  Server(int port, std::string password);
  ~Server();

  /*server_process*/
  void routine();
  void routinePOLLIN(const std::vector<struct pollfd>::iterator &pollfdIt);
  int acceptClient();
  void tryCommand(Client *client);
  bool processCommand(const int &clientFd);

  /*server utils*/
  bool isChannelPresent(std::string const &channelName);
  void closingFdClients();
  void verifyMaxClient(const int clientFdToRemove);
  void removeClient(const int clientFd);
  void deconectionClients();
  void addToPoll(int fd, short events);
  void removeClients();
  void addClientsToPoll();
  void addChannel(std::string const &channelName);
  void delChannel(std::string const &channelName);
  void cleanup(messageServer errorEvent);

  /*server_accessors*/
  const std::string &getPassword() const;
  int getNumbersClients();
  serverReply *getServerReply() const;
  Client *getClientByNickname(std::string const &nickname);
  const ClientMap &getClients() const;
  Channel *getChannel(std::string const &channelName);
  ChannelMap &getChannels();
  std::string getChannelsNames() const;
  void setClientToRemove(const int clientFd);

 private:
  std::vector<int> _clientFdToRemove;
  int _port;
  std::string _password;
  int _serverFd;
  struct sockaddr_in _serverAdress;
  std::vector<struct pollfd> _fds;
  std::map<const int, Client> _clients;
  std::vector<int> _clientsToRemove;
  std::vector<int> _clientsToAdd;
  std::map<std::string, Channel> _channels;
  serverReply *_serverReply;
};

#endif  // SRCS_SERVER_SERVER_HPP_
