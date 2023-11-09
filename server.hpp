/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:48 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/09 09:11:18 by pbeheyt          ###   ########.fr       */
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

	void		addChannel(std::string const &channelName);
	void		delChannel(std::string const &channelName);
	Channel		*getChannel(std::string const &channelName);
	void 		printAllChannels(void);

};

#endif // SERVER_HPP
