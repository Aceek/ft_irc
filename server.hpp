/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:48 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/09 05:49:21 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "include.hpp"

class Client;
// class Channel;

#define MAX_COMMAND_SIZE 512

class Server {
private:
	int 						_port;
	int							_serverFd;
	struct sockaddr_in			_serverAdress;
	std::vector<struct pollfd>	_fds; // Stockez les FD et les evenements associés
	std::map<const int, Client> _clients;

	std::map<std::string, Channel> _channels;
	
public:
	Server(int port);
	Server(/* args */);
	~Server();

	void	addToPoll(int fd, short events);
	void	routine();
	int		acceptClient();
	void	processComand(const int &clientFd);

	void			joinChannel(std::string const &channelName, Client &client);
	void			leaveChannel(std::string const &channelName, Client &client);
	Channel			*getChannel(std::string const &channelName);
};

#endif // SERVER_HPP
