/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:48 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/12 00:29:32 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "include.hpp"

class Client;
class Channel;

#define MAX_COMMAND_SIZE 512

extern bool	serverShutdown;
typedef std::map<const int, Client> ClientMap;
typedef std::map<std::string, Channel> ChannelMap;

class Server {
private:
	int 							_port;
	std::string						_password;
	int								_serverFd;
	struct sockaddr_in				_serverAdress;
	std::vector<struct pollfd>		_fds; // Stockez les FD et les evenements associés
	std::map<const int, Client> 	_clients;
	std::vector<int>				_clientsToRemove;
	std::set<int> 					_operatorClients;
	std::map<std::string, Channel>	_channels;
	
public:
						Server(int port, std::string password);
						Server(/* args */);
						~Server();
		
	void				addToPoll(int fd, short events);
	void				routine();
	bool				processCommand(const int &clientFd);
	void				removeClient(const int clientFd);
	void				removeClients();
	int					acceptClient();
	void				sendMessage(const Client &client,
						const std::string &message) const;

	void				setClientToRemove(const int clientFd);

	std::string			getErrorMessage(int errorCode);
	const std::string	&getPassword() const;
	Client 				*getClientByNickname(std::string const &nickname);
	const ClientMap		&getClients() const;
	Channel				*getChannel(std::string const &channelName);
	const ChannelMap	&getChannels();

    void 				grantOperatorStatus(int clientFd);
    void 				revokeOperatorStatus(int clientFd);
    bool 				isOperator(int clientFd) const;

	void				addChannel(std::string const &channelName);
	void				delChannel(std::string const &channelName);
	void 				printAllChannels(void);
};

#endif // SERVER_HPP
